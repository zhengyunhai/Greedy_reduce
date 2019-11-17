#include<NTL/ZZ.h>
#include<iostream>
#include<fstream>
#include<NTL/matrix.h> 
#include<NTL/mat_ZZ.h>
#include<NTL/vec_ZZ.h>
#include<NTL/vector.h>
#include<NTL/LLL.h>
#include<NTL/tools.h>
#include<NTL/RR.h>
#include <NTL/xdouble.h>
#include <NTL/quad_float.h>
#include<NTL/mat_RR.h>
#include<NTL/vec_RR.h>
#include<cstdlib>
#include<time.h>
using namespace std;
NTL_CLIENT
int order_all(mat_ZZ& B);
void ig_reduce(mat_ZZ &B);
//void ig_reduce_(mat_ZZ &B);
//计数 
int main(void)
{
	ifstream inf;
	ofstream outf;
	mat_ZZ L,L_,L_o;
	//mat_RR B;
	ZZ det,seed;
	seed=time(0);
	SetSeed(seed);
	int i,j,l,m;
	vec_ZZ norm_test,norm_test_;
	m=3;
	L.SetDims(m,m);
	L_.SetDims(m,m);
	L_o.SetDims(m,m);
/*	ifstream inf;
	inf.open("L.txt");
	inf>>L;
	inf.close();
	m=L.NumRows();
*/
	int count=1000;
	int k;
	int tageq=0;
	int tagle=0;
	int taggr=0;
	norm_test.SetLength(m);
	norm_test_.SetLength(m);
	for(k=0;k<count;k++)
	{
		clear(norm_test);
		clear(norm_test_);
	for(i=1;i<=m;i++)
	{
		for(j=1;j<=m;j++)
		{
			RandomLen(L(i,j),160);
		}
		VectorCopy(L_(i),L(i),m);
		VectorCopy(L_o(i),L(i),m);
	 }
	
	//cout<<"L orignal="<<endl<<L<<endl;
	
	ig_reduce(L);
	LLL(det,L_,0);
	order_all(L_);
	//cout<<"L -ig reduced="<<endl<<L<<endl;
	for(i=1;i<=m;i++)
{
	for(l=1;l<=m;l++)
	{
		norm_test[i-1]=operator+(norm_test[i-1],sqr(L(i,l)));
		norm_test_[i-1]=operator+(norm_test_[i-1],sqr(L_(i,l)));
	 } 
	 //cout<<norm_test[i-1]<<endl;
	 if(operator>(norm_test[i-1],norm_test_[i-1]))
	 {
	 	taggr++;
		outf.open("reducecompare.txt",ios::app);
	 	outf<<"L_o="<<endl<<L_o<<endl<<"i(greater)="<<i<<endl<<"ig_reduce="<<endl<<L<<endl<<"lll_reduce="<<L_<<endl<<"L["<<i<<"]="<<endl<<norm_test[i-1]<<endl<<" greater than L_["<<i<<"]="<<endl<<norm_test_[i-1]<<endl;
	 	outf.close();
	 }
	 if(operator<(norm_test[i-1],norm_test_[i-1]))
	 {
	 	tagle++;
	 	outf.open("reducecompare.txt",ios::app);
	 	outf<<"L_o="<<endl<<L_o<<endl<<"i(less)="<<i<<endl<<"ig_reduce="<<endl<<L<<endl<<"lll_reduce="<<endl<<L_<<endl<<"L["<<i<<"]="<<endl<<norm_test[i-1]<<endl<<" less than L_["<<i<<"]="<<endl<<norm_test_[i-1]<<endl;
	 	outf.close();
	 	
	 }
		
}
}
cout<<"大于LLL结果的有"<<taggr<<",小于的有"<<tagle<<endl;


 } 
