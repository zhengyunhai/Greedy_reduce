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
#include<sys/time.h>
using namespace std;
NTL_CLIENT
int order_all(mat_ZZ& B);
void ig_reduce(mat_ZZ &B);
//void ig_reduce_(mat_ZZ &B);
//测试约化大整数格的时间 ,生成随机的4*4大整数格，测试约化的时间 
int main(void)
{
	mat_ZZ L,L_;
	//mat_RR B;
	ZZ det,seed;
	struct timeval tstart1,tend1,tstart2,tend2;
	float time1,time2;
	seed=time(0);
	SetSeed(seed);
	
	int i,j,l,m;
	m=4;
	vec_ZZ norm_test;
	norm_test.SetLength(m);
	L.SetDims(m,m);
	L_.SetDims(m,m);
	for(i=1;i<=m;i++)
	{
		for(j=1;j<=m;j++)
		{
			RandomLen(L(i,j),1024);
		}
		VectorCopy(L_(i),L(i),m);
	 }
	 
	


	
	cout<<"L orignal="<<endl<<L<<endl;
	gettimeofday(&tstart1,NULL);
	ig_reduce(L);
	gettimeofday(&tend1,NULL);
	time1=1000*(tend1.tv_sec-tstart1.tv_sec)+(tend1.tv_usec-tstart1.tv_usec)/1000;
	cout<<"L -ig reduced="<<endl<<L<<endl;
	cout<<"norm"<<endl;
	for(i=1;i<=m;i++)
{
	for(l=1;l<=m;l++)
	{
		norm_test[i-1]=operator+(norm_test[i-1],sqr(L(i,l)));
	 } 
	 cout<<norm_test[i-1]<<endl;
		
}


/*	inf.open("L.txt");
	inf>>L_;
	inf.close();
	order_all(L_);
*/	
	gettimeofday(&tstart2,NULL);
	LLL(det,L_,0);

	
	gettimeofday(&tend2,NULL);
	time2=1000*(tend2.tv_sec-tstart2.tv_sec)+(tend2.tv_usec-tstart2.tv_usec)/1000;
	
	cout<<"L -L3 reduced="<<endl<<L_<<endl;
	clear(norm_test);
	cout<<"norm"<<endl;
	for(i=1;i<=m;i++)
{
	for(l=1;l<=m;l++)
	{
		norm_test[i-1]=operator+(norm_test[i-1],sqr(L_(i,l)));
	 } 
	 cout<<norm_test[i-1]<<endl; 
	
}

cout<<"time="<<time1<<" "<<time2<<endl;
 } 
