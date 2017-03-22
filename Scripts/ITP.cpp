/*
 * ITP.cpp
 *
 *  Created on: Aug 21, 2016
 *      Author: maomoke
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define N 3200 // number of atom
#define blen 2.13
#define NN 4000  //array size
#define yp 45.9
#define zp 59.2

using namespace std;

char s[1000],st[3][1000], name[NN][10],atp[NN][10];
float x[NN],y[NN],z[NN];

double dis(int a, int b){
	return (sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b])+(z[a]-z[b])*(z[a]-z[b])));
}

bool bond(int a, int b){
	x[0]=x[b];y[0]=y[b];z[0]=z[b];
	if (dis(0,a)<blen) return true;

	y[0]=y[b]-yp;
	if (dis(0,a)<blen) return true;
	y[0]=y[b]+yp;
	if (dis(0,a)<blen) return true;
	y[0]=y[b];

	z[0]=z[b]-zp;
	if (dis(0,a)<blen) return true;
	z[0]=z[b]+zp;
	if (dis(0,a)<blen) return true;

	return false;
}

int main() {
	float charge, mass;
	char atomtype[20];

	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
//POSITION

	for (int i=1;i<=N;++i)
	{
		scanf("%s %s %s %s %s %s %f %f %f %s %s %s",&s,&s,&name[i], &s,&s,&s,&x[i],&y[i],&z[i],&s,&s,&s);
		if (strcmp(name[i],"TIA")==0)
		{
			charge=1.8365;
			mass=204.38;
			strcpy(atp[i],"Ti5");
		}

		if (strcmp(name[i],"TIB")==0)
		{
			charge=1.433;
			mass=204.38;
			strcpy(atp[i],"Ti6");
		}
		if (strcmp(name[i],"OA")==0)
		{
			charge=-1.12;
			mass=16.00;
			strcpy(atp[i],"OT2");
			strcpy(name[i]," OA");
		}
		if (strcmp(name[i],"OB")==0)
		{
			charge=-0.7165;
			mass=16.00;
			strcpy(atp[i],"OT3");
			strcpy(name[i]," OB");
		}
		if (strcmp(name[i],"HT")==0)
		{
			charge = 0.417;
			mass = 1.008;
			strcpy(atp[i]," HT");
			strcpy(name[i]," HT");
		}
		 printf("  %4d   %s   1    TIO   %s  %4d     %7.4f   %9.5f\n",i,atp[i],name[i],i,charge,mass);
	}
//bonds
	printf("[ bonds ]\n");
	printf(";   ai     aj funct   r             k\n");
	for (int i=1;i<N;++i)
	{
		for (int j=i+1;j<=N;++j)
			if (bond(i,j))
			{
				if (j<=3000) printf("  %4d   %4d   1    1.95983e-01    2.11270e+05 ;\n",i,j);
				else printf("  %4d   %4d   1    9.57200e-02    5.02416e+05 ;\n",i,j);
			}
	}


/*	int cnt;
	for (int i=1;i<=N;++i){
		cnt=0;
		for (int j=1;j<=N;++j)
		{
			if (i==j) continue;
			if (bond(i,j)) {
				++cnt;
				if (cnt%4==1)printf("\nCONECT%5d",i);
				printf("%5d",j);
			}
		}
	}*/
	return 0;
}






