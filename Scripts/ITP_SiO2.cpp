/*
 * ITP_SiO2.cpp
 *
 *  Created on: Jan 8, 2017
 *      Author: maomoke
 */


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define N  1848 // number of atom
#define blen 2.13 // length of bonds
#define NN 10000   // array size
#define xp 34.426 // x dimension size
#define yp 34.426 // y dimension size
#define SC4  1
#define OC23 2
#define OC24 3
#define HOY  4
#define NA+  5

//OC24 silanal z<1.8 or z>15.8
//OC23 bulk		1.8<z<15.8

using namespace std;

char s[1000],st[3][1000], name[NN][10],type[NN][10];
float x[NN],y[NN],z[NN],charge[NN],mass[NN],b0,k0,t0;
int n;


double dis(int a, int b){
	return (sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b])+(z[a]-z[b])*(z[a]-z[b])));
}

bool bond(int a, int b){
	x[0]=x[b];y[0]=y[b];z[0]=z[b];
	if (dis(0,a)<blen) return true;

	x[0]=x[b]-xp;
	if (dis(0,a)<blen) return true;
	x[0]=x[b]+xp;
	if (dis(0,a)<blen) return true;
	x[0]=x[b];

	y[0]=y[b]-yp;
	if (dis(0,a)<blen) return true;
	y[0]=y[b]+yp;
	if (dis(0,a)<blen) return true;

	return false;
}

int set_bond_para(int a, int b){
	char ss[10],s1[10],s2[10];
	strcpy(s1,type[a]);
	strcpy(s2,type[b]);
	if (strcmp(s1,"SC4")==0||strcmp(s2,"SC4")==0){
		b0 = 0.168;
		k0 = 238488;
	}
	if (strcmp(s1,"HOY")==0||strcmp(s2,"HOY")==0){
		b0 = 0.0945;
		k0 = 414216;
	}
	return 0;
}

int set_angle_para(int a, int b, int c){
	char ss[10],s1[10],s2[10],s3[10];
	strcpy(s1,type[a]);
	strcpy(s2,type[b]);
	strcpy(s3,type[c]);
	if (strcmp(s2,"SC4")==0){
			t0 = 109.5;
			k0 = 836.8;
	}
	if (strcmp(s1,"SC4")==0){
			t0 = 149;
			k0 = 836.8;
	}
	if (strcmp(s1,"HOY")==0){
			t0 = 115;
			k0 = 418.4;
	}
	return 0;
}


int main() {

	int d,n;
	n = N;

	freopen("qua.itp","r",stdin);
	freopen("silica","w",stdout);

	//moleculetype
	printf("[ moleculetype ]\n;name            nrexcl\n QUA             1\n\n");

	//POSITION
	printf("[ atoms ]\n;   nr  type  resi  res  atom  cgnr     charge      mass       ; qtot   bond_type\n");
	getchar();

	for (int i=1;i<=N;++i)
	{
		scanf("%d %s %d %s %s %d %f %f",&d,&type[i],&d,&s,&name[i],&d,&charge[i],&mass[i]);
		//printf("%4d     %4s  1 QUA    %4s  %4d      %9f  %9f\n",i,type[i],name[i],i,charge[i],&mass[i]);
	}

	for (int k=1;k<=3;++k)
		for (int i=1;i<=N;++i)
		{
			printf("%4d     %4s  1 QUA    %4s  %4d      %9f  %9f\n",i+N*k,type[i],name[i],i+N*k,charge[i],&mass[i]);
		}
	//read position
	freopen("silica.pdb","r",stdin);
	for (int i=1;i<=n;++i)
	{
		scanf("%s %s %s %s %s %s %f %f %f %s %s %s",&s,&s,&s,&s,&s,&s,&x[i],&y[i],&z[i],&s,&s,&s);
	}

	printf("x %f %f %f\n y %f %f %f\n dis = %f",x[1],y[1],z[1],x[7],y[7],z[7],dis(1,7));


	//bonds
	printf("[ bonds ]\n");
	printf(";   ai     aj funct   r             k\n");
	for (int i=1;i<N;++i)
	{
		for (int j=i+1;j<=N;++j)
			if (bond(i,j))
			{
				set_bond_para(i,j);
				printf("  %4d   %4d   1    %.4f    %.1f \n",i,j,b0,k0);
			}
	}
	//angles
	printf("[ angles ]\n");
	for (int i=1;i<=N;++i)
	{
		for (int j=1;j<N;++j)
		{
			if (j==i) continue;
			for (int k=j+1;k<=N;++k){
				if (i==k) continue;
				if (bond(i,j) && bond(i,k))
				{
					set_angle_para(j,i,k);
					//printf("     %4d     %4d     %4d      1       %.4f    %.1f  0.0  0.0\n",j,i,k,t0,k0);
				}
			}
		}
	}

	printf("x %f %f %f y %f %f %f z %f %f %f\ndis 1-2 %f dis2-3\n %f",x[1],y[1],z[1],x[9],y[9],z[9],x[356],y[356],z[356],dis(1,9),dis(9,365));
	if (bond(9,365)) printf("yes\n");
	else printf("no\n");

	return 0;
}









