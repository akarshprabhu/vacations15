//Program to find the minimum cost to transform one string to another by Dyanmic programming 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define cost 1

int Min(int a,int b){
	return (a < b ? a : b);
}

int min(int a,int b,int c){
return Min(Min(a, b), c);
}

//generates table and prints
int table(char s1[],char s2[]){
	int i,j,m,n,t[100][100];
	m=strlen(s1)+1;
	n=strlen(s2)+1;
	int v,x;
	int left,top,corner;
	
	//initializes the whole table
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			t[i][j]=-1;
			
	for(i=0;i<m;i++)
		t[i][0]=i;
			
	
	for(j=0;j<n;j++)
		t[0][j]=j;
	
	//uses the formula and fills up the table using previous values	
	for(i=1;i<m;i++){
		for(j=1;j<n;j++){
			left=t[i][j-1]+cost;
			top=t[i-1][j]+cost;
			
			if(s1[i-1]==s2[j-1])
				v=0;
			else
				v=2*cost;
			corner=t[i-1][j-1]+v;
			t[i][j]=min(left,top,corner);
			}
		}
		
	for(i=0;i<m;i++){
		for(j=0;j<n;j++)
			printf("%d\t",t[i][j]);
			printf("\n");			
	}
	
	//the last value filled is te minimum cost which is printed	
	printf("Min Cost is %d\n",t[m-1][n-1]);
	
}

void main(){

	char s1[10],s2[10];
	int a;
	printf("enter string 1 ");
	scanf("%s",s1);
	printf("Enter string 2 ");
	scanf("%s",s2);
	printf("\n");
	a=table(s1,s2);
	
}
