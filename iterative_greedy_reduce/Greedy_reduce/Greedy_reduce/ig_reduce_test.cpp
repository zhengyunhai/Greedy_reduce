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

int main(void)
{
	mat_ZZ L,L_;
	//mat_RR B;
	ZZ det;

	int i,j,l,m;
	vec_ZZ norm_test;
	

	ifstream inf;
	inf.open("L.txt");
	inf>>L;
	inf.close();
	m=L.NumRows();
	norm_test.SetLength(m);
	
	cout<<"L orignal="<<endl<<L<<endl;
	
	ig_reduce(L);
//	cout<<"L -ig reduced="<<endl<<L<<endl;
	for(i=1;i<=m;i++)
{
	for(l=1;l<=m;l++)
	{
		norm_test[i-1]=operator+(norm_test[i-1],sqr(L(i,l)));
	 } 
	 cout<<norm_test[i-1]<<endl;
		
}


	inf.open("L.txt");
	inf>>L_;
	inf.close();
	order_all(L_);
	
	LLL(det,L_,0);
	
	cout<<"L -L3 reduced="<<endl<<L_<<endl;
	
	clear(norm_test);
	for(i=1;i<=m;i++)
{
	for(l=1;l<=m;l++)
	{
		norm_test[i-1]=operator+(norm_test[i-1],sqr(L_(i,l)));
	 } 
	 cout<<norm_test[i-1]<<endl; 
	
}
 } 
