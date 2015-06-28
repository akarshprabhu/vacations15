//Implements Apriori algorithm using sets. Set representation is the bit representation and a linked list consisting of sets is used.
//works satisfactorily but not for all cases as pruning couldnt be implemnted properly using this approach.
//redirect testcase from file "apri"

#include<stdio.h>
#include<stdlib.h>
struct node
{
	int i;
	int s;
	struct node *next;
};

typedef struct node * NODE;

struct link 
{
	struct node * p;
	struct link *link;
};

typedef struct link * LINK;

int sup1[5];
int sup2[10];
int sup3[20];
int min_sup = 2;

struct node* insert(struct node *h,int data)
{
	int index=(int)((data/32)*32);
	struct node *H;

	if(h==NULL)
	{
		h=(struct node*)malloc(sizeof(struct node));
		h->i=index;
		h->s|=1<<(data%32);
		h->next=NULL;
		return h;
	}
	struct node *p;
	p=h;
	H=h;
	while(h!=NULL)
	{
		if(h->i==index)
		{
			h->s|=1<<(data%32);
			return H;
		}

		else if(h->i >index)
		{
			struct node *temp;
			temp=(struct node*)malloc(sizeof(struct node));
			temp->i=index;
			temp->s|=1<<(data%32);
			p->next=temp;
			temp->next=h;
			return H;
		}
		else if(h->i < index)
		{
			p=h;
			int l;
			l=h->i;
			h=h->next;
		}
		else
		{
			struct node *temp;
			temp=(struct node*)malloc(sizeof(struct node));
			temp->i=index;
			temp->s|=1<<(data%32);
			p->next=temp;
			temp->next=NULL;
			return H;
		}
	}
	struct node *temp;
	temp=(struct node*)malloc(sizeof(struct node));
	temp->i=index;
	temp->s|=1<<(data%32);
	p->next=temp;
	temp->next=NULL;
	return H;
}


void display(struct node *h)
{
	int i,a;
	printf("Set {");
	while(h!=NULL)
	{
		int x=0;
		a=h->s;
		for(i=x;i<x+32;i++)
		{
			if(a>>i & 0x1)
			{
				printf("'%d',",i);
			}
		}
		h=h->next;
	}
	printf("}\n");
}




struct node* uni(struct node *A,struct node *B,struct node *C)
{
	int a,x,i;
	while(A!=NULL)
	{
		a=A->s;
		x=A->i;
		for(i=x;i<x+32;i++)
		{
			if(a>>i & 0x1)
			{
				C=insert(C,i);
			}
		}
		A=A->next;
	}
	while(B!=NULL)
	{
		a=B->s;
		x=B->i;
		for(i=x;i<x+32;i++)
		{
			if(a>>i & 0x1)
			{
				C=insert(C,i);
			}
		}
		B=B->next;
	}
	return C;
}


struct node* inter(struct node *A,struct node *B,struct node *C)
{
	int a,x,i;
	while(A!=NULL && B!=NULL)
	{
		if(A->i==B->i)
		{
			int o,p;
			o=A->s;
			p=B->s;
			a= o & p;
			x=A->i;
			for(i=x;i<x+32;i++)
			{
				if(a>>i & 0x1)
				{

					C=insert(C,i);
				}
			}
			A=A->next;
			B=B->next;
			continue;
		}

		else if(A->i<B->i){A=A->next;continue;}
		else
		{
			A=A->next;
			B=B->next;
		}
	}
	return C;

}



struct node* Set(struct node *a){
a=insert(a,0);
a->s=a->s&0x0;
return a;
}

LINK insert_link(LINK tmp , NODE p)
{
	 LINK T;	

	 if( tmp == NULL )

	 {

	  tmp = (LINK)malloc(sizeof(struct link));

	  T = tmp;

	 } 

	 else

	 {

	   T = tmp;

	   	while( T->link != NULL)	

			T = T->link;



	   T->link = (LINK)malloc(sizeof(struct link));

	   T = T->link;

	 }

	 T -> p = p;
	 T->link = NULL;

	

	 return tmp;
}

void dispL(LINK T)
{
	while( T!=NULL )

	{

	  display(T->p);

	  T = T->link;
	}
}

void displ(LINK T)
{
	

	  display(T->p);

	  T = T->link;
	  
	  display(T->p);
	
}

//checks if 2 item sets are same
int equal( NODE r1 , NODE r2)
{
	while( r1 != NULL && r2 != NULL)
	{
		if( r1->i == r2->i)
		{
			if( r1->s == r2->s)
			{
				r1 = r1->next;
				r2 = r2->next;
			}else 
			return 0;
		}
		else 
			return 0;
	}
	if( r1 == NULL && r2 == NULL)
		return 1;
	else 
		return 0;
}
//Calculates min support counter for each item set
void calsup( LINK D , LINK c , int sup[])
{	
	int count=0 , i = 0;
	LINK t;
	NODE b = NULL;
	while(c)
	{ 
		t = D;
		count = 0;
		while(t)
		{	
			if(equal(inter(t->p, c->p,b) , c->p))
			{
				count++;
			}
			t = t->link;
		}
		c = c->link;
		sup[i++] = count;
	}
}
//Generates L using C w.r.t min support counter		
LINK makeL( LINK c , int sup[])
{
	LINK t;
	t = NULL;
	int i ;
	for( i = 0 ; c != NULL ; i++)
	{
		if(sup[i] >= min_sup)
		{
			t = insert_link(t , c->p);
		}
		c = c->link;
	}
	return t;
}

//forms subsets for the bits approach of sets
LINK subset(LINK C){
	LINK T,P;T=C;
	LINK S=NULL;NODE SS=NULL;
	while(T!=NULL){
		P=T->link;
			while(P){SS=NULL;
				SS=uni(T->p,P->p,SS);
				S=insert_link(S,SS);
				P=P->link;
			}T=T->link;
	}return S;
}	


void main()
{
/*
*/
	int i, j , n , item;
	int d = 9;
	int arr[5] = { 1 , 2, 3, 4, 5};
	NODE a;
	LINK D ;
	LINK l[10] , c[10];
	c[0] = NULL;
	a = NULL;
	D = NULL;
	int k = 0;
	int h = 0;

	for(i =  0 ; i < d ; i++)
	{
		a = NULL;
	 	scanf("%d" , &n);
		for( j = 0 ; j<n ; j++)
		{
			scanf("%d" , &item); 
			a = insert(a , item);
		}
		D = insert_link(D , a);
		
	}
	
	printf("\nSet of of all Transactions\n");
	dispL(D);
	for(i =  0 ; i < 5 ; i++)
        {
                a = NULL;
                for( j = 0 ; j<1 ; j++)
                {
                        a = insert(a , arr[i]);
                }
                c[0] = insert_link(c[0] , a);

        }
    printf("\n Set C1\n");
	dispL(c[0]);
	calsup(D , c[0], sup1);
	
	printf("Support counter for C1\n");
	for( i = 0 ; i<5 ; i++)
		printf("%d  ",sup1[i]);


	printf("\n Item sets of size 1 frequently bought \n");
	l[0] = makeL(c[0] , sup1);
	dispL(l[0]);
	
	c[1]=subset(l[0]);
	printf("\n Set C2\n");
	dispL(c[1]);
	
	calsup(D , c[1], sup2);
	printf("Support counter for C2\n");
	for( i = 0 ; i<10 ; i++)
		printf("%d  ",sup2[i]);
	
	printf("\n Item sets of size 2 frequently bought \n");	
	l[1] = makeL(c[1] , sup2);
	dispL(l[1]);
	
	
	c[2]=subset(l[1]);
	printf("\n Set C3\n");
	dispL(c[2]);
	
	calsup(D , c[2], sup3);
	printf("Support counter for C3\n");
	for( i = 0 ; i<15 ; i++)
		printf("%d  ",sup3[i]);
	LINK ll=NULL;
	printf("\n Item sets of size 3 frequently bought \n");	
	l[2] = makeL(c[2] , sup3);

	displ(l[2]);
	
	
}
