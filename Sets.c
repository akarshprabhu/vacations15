//Program to implement non-dense sets using bit representaion and their operations.

#include<stdio.h>
#include<stdlib.h>
struct node {
	int ind;
	int a;
	struct node *next;
};
typedef struct node *node;


node insert(int key,node head) {
	node temp=(node)malloc(sizeof(node));
	node p;
	int k_ind;
	if(head==NULL) {
		temp->ind=(key/32)*32;
		temp->a = 1 << (key % 32);
		temp->next=NULL;
		head=temp;
		return head;
	}
	k_ind=(key/32)*32;
	p=head;
	while(p != NULL) {
		if(k_ind > p->ind) {
			p=p->next;
			continue;
		}
		if( k_ind == p->ind) {
			p->a |= 1 << (key%32);//sets the corresponding bit to 1
			return head;
		}
		else {
			node q;
			q=head;
			if(p==head) {
				temp->ind=(key/32)*32;
				temp->a = 1 << (key%32);
				temp->next=p;
				head=temp;
				return head;
			}
			while(q->next != p) {
				q=q->next;
			}
			temp->ind=(key/32)*32;
			temp->a |= 1 << (key%32);
			temp->next=p;
			q->next=temp;
			return head;
		}
	}
	p=head;
	while(p->next != NULL)
		p=p->next;
	temp->ind=(key/32)*32;
	temp->a |= 1 << (key%32);
	temp->next=NULL;
	p->next=temp;
	return head;
}
void display(node head) {
	node p;
	int i,y,x,b;
	p=head;
	while (p != NULL) {
		x=p->ind;
		y=0;
		for(i=x;i<x+32;i++) {
			b=p->a;
			if( (b >> y) & 0x1) //is true only if the corresponding cell is set to 1, meaning the number is in the set.
				printf("%d\t",i);
			y++;
		}
		p=p->next;
	}
	printf("\n");
}
node uni(node p,node q,node H3) {
	int i,y,x,b;
	while (p != NULL) {
		x=p->ind;
		y=0;
		for(i=x;i<x+32;i++) {
			b=p->a;
			if( (b >> y) & 0x1) 
				H3=insert(i,H3);
			y++;
		}
		p=p->next;
	}
	while (q != NULL) {
		x=q->ind;
		y=0;
		for(i=x;i<x+32;i++) {
			b=q->a;
			if( (b >> y) & 0x1) 
				H3=insert(i,H3);
			y++;
		}
		q=q->next;
	}
	return H3;
}
node inter(node h1,node h2,node H3) {
	node p,q;
	p=h1;
	q=h2;
	int b,x,y,z,d,c,i;
	while(p != NULL && q != NULL) {
		if(p->ind == q->ind) {		
			x=p->ind;
			z=0;
			for(i=x;i<x+32;i++) {
				b=p->a;
				c=q->a;
				d=b & c;			
				if( (d >> z) & 0x1) 
					H3=insert(i,H3);
				z++;
			}
			q=q->next;
			p=p->next;
		}
		else if(p->ind < q->ind)
			p=p->next;
		else
			q=q->next;
	} 
	return H3;
}

node AmB(node h1,node h2,node H3) {
	node p,q;
	p=h1;
	q=h2;
	int x,d,z,i;
	while( p != NULL && q != NULL) {
		if(p->ind == q->ind) {
			x=p->ind;
			z=0;
			for(i=x;i<x+32;i++) {
				d=(p->a ^ q->a) & p->a;
				if( (d>>z) & 0x1)
					H3=insert(i,H3);
				z++;
			}
			q=q->next;
			p=p->next;
		}
		else if(p->ind < q->ind) {
			x=p->ind;
			z=0;
			for(i=x;i<x+32;i++) {
				d=p->a ;
				if( (d>>z) & 0x1)
					H3=insert(i,H3);
				z++;
			}
			p=p->next;
		}
		else
			q=q->next;
	}
	return H3;
}
void main() {
	node H1=NULL;
	node H2=NULL;
	node H3=NULL;
	int n1,n2,j,xx,ch;
	int choice;
	printf("Enter the number of elements in set 1\n");
	scanf("%d",&n1);
	for(j=0;j<n1;j++) {
		xx=rand()%50;
		
		H1=insert(xx,H1);
	}
	printf("\nEnter the number of elements in set 2\n");
	scanf("%d",&n2);
	for(j=0;j<n2;j++) {
		xx=rand()%50;
		
		H2=insert(xx,H2);
	}
	printf("\nSET 1 is:\t");
	display(H1);
	printf("\nSET 2 is:\t");
	display(H2);
	do {
		printf("\nEnter choice\n 1.Union\n 2.Intersection\n 3.A-B\n 4.B-A\n 5.Exit\n");
		scanf("%d",&ch);
		switch(ch) {
			
			case 1: H3=uni(H1,H2,H3);				
					display(H3);
					H3=NULL;
					break;
			case 2: H3=inter(H1,H2,H3);
					display(H3);
					H3=NULL;
					break;
			case 3: H3=AmB(H1,H2,H3);
					display(H3);
					H3=NULL;
					break;
			case 4: H3=AmB(H2,H1,H3);
					display(H3);
					break;
			default: exit(0);
					
		}
		
	}while(1);
}
