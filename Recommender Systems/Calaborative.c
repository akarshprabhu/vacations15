//Recommender system using Jacard's Similarity
//Using C


#include <stdio.h>
#include <stdlib.h>

int rat[943][1682];
int inter[1682];
int r[943][1682];

int uni[1682];
int m=555;
int n =943;
int o = 1682;
float sim[943];
int m1 , m2;
int count[943];

void form()
{
	int i , j;
	for(i=0;i<n;i++)
	{
		if(i==m)
			continue;
		for(j=0;j<o;j++)
		{
			if((rat[m][j]-rat[i][j])<2 && rat[m][j] != 0 && rat[i][j]!= 0) //constraints to take users as similar, can be modified
				inter[i]++;
			if(!(r[m][j] == 0&&r[i][j]==0))
				uni[i]++;
		}
		sim[i] = (inter[i]*1.0)/(uni[i]*1.0);
	}
}

void reco()
{
	int i , j;
	i = 0;
	float max1 , max2;
	if(sim[0] > sim[1] && sim[i]!=0)
	{
		max1 = sim[0];
		m1 = 0;
		max2 = sim[1];
		m2 = 1;
	}	
	else 
	{
		if(sim[i]!=0)
		{
			max1 = sim[1];
			m1 = 1;
			max2 = sim[0];
			m2 = 0;
		}
	}
	for(i = 0 ; i<o ; i++)
	{
		if(sim[i] >max1 && sim[i]!=0) 
		{
			max2 = max1;
			m2 = m1;
			max1 = sim[i];
			m1 = i;
		}
		if(sim[i] <= max1 && sim[i]>=max2 && sim[i]!=0)
		{
			max2 = sim[i];
			m2 = i;
		}
	}
	for(i = 0; i<o;i++)
	{
		if(rat[m][i] == 0)
		print(i);
	}
	
}

void max(){
	float mm=sim[0];
	int i,m1=0;
	for(i=0;i<n;i++){
		if(sim[i]>=mm){
			m1=i;mm==sim[i];
		}
	}
	count[m1]++;
}

void print(int ind)
{
	if(m1==0 && m2==0)
	{
		printf("You havent watched any movie\n Therefore we recommend the 9th movie which has been rated the highest\n");
		exit(0);
	}
	if((rat[m1][ind] > rat[m2][ind])&&rat[m1][ind]>2) 
		printf("We Recommend you to watch movie %d it has been rated %d by similar people \n " , ind+1 , rat[m1][ind] , m1);
	else 
	{
		if(rat[m2][ind] > 2)
		printf("We Recommend you to watch movie %d it has been rated %d by similar people \n" , ind+1 , rat[m2][ind] , m2);
		
	}
}	

main()
{
	int i , j;
	int mm,nn,ra,q;
	for(i=0;i<n;i++)
	for(j=0;j<o;j++){
		scanf("%d\t%d\t%d\t%d",&mm,&nn,&ra,&q);
		rat[mm-1][nn-1]=ra;
	}

	for(i = 0 ; i<n ; i++)
	{
		for(j=0;j<o;j++)
		{	
			if(rat[i][j]>0)
				r[i][j] = 1;
			
		}	
	}

		
		form();
		max();
		reco();
		
	
}












				
