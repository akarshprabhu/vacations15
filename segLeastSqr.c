//Program to implemented segemented Least square. i/p file is segIP 
// this takes x,y points as i/p and gives you the segments formed as output taking into account the cost 
//segments are nothing but the staright lines fitting the points 

#include<stdio.h>
#include<stdlib.h>

struct P
{
	int x,y;
};

typedef struct P p;


p pt[100];
int n,c=3;//cost

float error(int i,int j){
	int k;
	int x,y,xy,x2;
	float a,b,e;
	x=y=x2=xy=0;
	for(k=0;k<i;k++){
		x+=pt[k].x;
		y+=pt[k].y;
		xy+=pt[k].x*pt[k].y;
		x2+=pt[k].x*pt[k].x;
	}
	a = 0.0;
	b = 0.0;
	e = 0.0;
	a=((n*xy-x*y)*1.0)/((n*x2-x*x)*1.0);
	b=((y-a*x)*1.0)/(n*1.0);
	for(k=0;k<j;k++)
	{
		e+=(pt[k].y-a*pt[k].x-b)*(pt[k].y-a*pt[k].x-b)*1.0;
	}
	return e;
}

float m[100];

void sls(int n)
{
	int i,j,mini,minj;
	m[0]=0;
	float min=9999.9,min1;
	float val;
	
	for(j=1;j<=n;j++)
	{
		min1=9999.9;
		for(i=1;i<=j;i++)
		{
			val=error(i,j)+c+m[i-1];
			if(min1>val)
			{
				min1=val;
			}
		}
		m[j]=min1;
	}
	return;
}

void segment(int j)
{
	if(j!=0)
	{
		int i;
		float min , mini , val;
		min = 999999999.0;
		for(i=1 ; i<= j; i++)
		{
			val = error(i,j)+c+m[i-1];
			if(val<min)
			{
				min = val;
				mini = i;
			}
		}
		for(i = mini ; i<=j ; i++)
		{

			printf("%d, %d\t" , pt[i-1].x , pt[i-1].y);
		}
		printf("\n");
		segment(mini-1);
	}
}



void main(int argc,int argv[])
{
	int i,j;
	
	scanf("%d",&n);
	for(j=0;j<n;j++)
	{
		scanf("%d %d",&pt[j].x,&pt[j].y);
	}
	sls(n);
	segment(n);
}	

	
	

