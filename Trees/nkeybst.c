//Program to generate all possible BSTs when n keys are given

#include<stdio.h>
#include<stdlib.h>
struct node {
	int data;
	struct node *llink,*rlink,*pptr;
};

int val;
static int gName=0;
typedef struct node *node;

node root=NULL;

node  getnode() {
	node x;
	x=(node)malloc(sizeof(struct node));
	if(x==NULL) {
		printf("Out of memory\n");
		exit(0);
	}
	return x;
}

//BST insertion
node insert(int item,node root) {
	node temp,cur,prev;
	temp=getnode();
	temp->data=item;
	temp->llink=temp->rlink=NULL;
	temp->pptr=NULL;
	if(root == NULL )
		return temp;
	prev=NULL;
	cur=root;
	while(cur != NULL) {
		prev=cur;
		//unique nodes
		if(item==cur->data) {
			val++;
			return root;
		}
		if(item<cur->data)
			cur=cur->llink;
		else
			cur=cur->rlink;
	}
	if(item < prev->data)
		prev->llink=temp;
	else
		prev->rlink=temp;
	temp->pptr=prev;
	return root;
}

void swap (int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void preorderDotDump (node root, FILE* outputFile)
{
	if (root != NULL) 
	{
		fprintf (outputFile, "%d [label=%d,color=black];\n",root->data, root->data);
		if (root->llink != NULL) 
		         fprintf (outputFile, "%d -> %d ;\n", root->data, (root->llink)->data);
		
        	if (root->rlink != NULL)
            		fprintf (outputFile, "%d -> %d;\n", root->data, root->rlink->data);
        	preorderDotDump (root->rlink, outputFile);
        	preorderDotDump (root->llink, outputFile);
    	}
}
void dotDump(node root, FILE *outFile)
{
	gName++;
	fprintf (outFile, "digraph BST {\n",gName);
	preorderDotDump (root, outFile);
    	fprintf (outFile, "}\n");
}
FILE *output;

void maketree(int *a,int n) {
	int i;
	for(i=0;i<=n;i++)	
		root=insert(a[i],root);
	output=fopen("bstpermute.dot","a");
	if(output != NULL) {
		dotDump(root,output);
	}
	fclose(output);	
	free(root);
}

//function to generate permuted array and make the corresponding trees simultaneously with help from above function
void permute(int *a, int i, int n) 
{
int j;
	if(i==n) {
		maketree(a,n);
	}
else {
        for (j = i; j <= n; j++)
       {
          swap((a+i), (a+j));
          permute(a, i+1, n);
          swap((a+i), (a+j)); //backtrack
       }
   }
}
void main() {
	FILE *pipe;
	int a[]={1,3,2,4};	
	int n=4;
	output=fopen("bstpermute.dot","w");
	fclose(output);
	permute(a,0,n-1);
	// all the generated trees are shown with dotty
	pipe=popen("dot -Tps bstpermute.dot -o bstpermute.ps","w");
	pclose(pipe);	
	pipe=popen("evince bstpermute.ps","r"); 
	pclose(pipe);
}
