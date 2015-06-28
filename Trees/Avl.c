//Program implementing AVL tree insertions 
//redirect i/p from file "avlIP"

#include<stdio.h>
#include<stdlib.h>
struct node
{
	int key;
	char BI;
	struct node *left,*right;
};
typedef struct node *NODE;

int lvl,mark,i;
char dir[20],D;
NODE T,X,Y,Z,F,P;
NODE path[20];//has address of all nodes in the tree

NODE Create_Leaf(int key,NODE N)
{
	N=(NODE)malloc(sizeof(struct node));
	if(N==NULL)
	{
		printf("\n No memory ");
		exit(0);
	}
	N->left=N->right=NULL;
	N->BI='B';
	N->key=key;
	return N;
}



NODE insert(int key,NODE H)
{
	NODE NN;
	if(H->left==H)
	{
		NN=Create_Leaf(key,NN);
		H->left=NN;
		return H;
	}
	lvl=0;
	dir[lvl]='L';
	path[lvl]=H;
	T=H->left;
	while(1)
	{
		if(key<T->key)
		{
			if(T->left!=NULL)
			{
				lvl=lvl+1;
				path[lvl]=T;
				dir[lvl]='L';
				T=T->left;
			}
			else
			{
				NN=Create_Leaf(key,NN);
				T->left=NN;
				lvl=lvl+1;
				path[lvl]=T;
				dir[lvl]='L';
				break;
			}
		}
		else if(key>T->key)
		{
			if(T->right!=NULL)
			{
				lvl=lvl+1;
				path[lvl]=T;
				dir[lvl]='R';
				T=T->right;
			}
			else
			{
				NN=Create_Leaf(key,NN);
				T->right=NN;
				lvl=lvl+1;
				path[lvl]=T;
				dir[lvl]='R';
				break;
			}
		}
		else
		{
			printf("\n Key already exists ");
			return H;
		}
	}	
	mark=0;
	for(i=lvl;i>=1;i--)
	{
		P=path[i];
		if(P->BI!='B')
		{
			mark=i;
			break;
		}
	}
	for(i=mark+1;i<=lvl;i++)
	{
		if(key<path[i]->key)
		{
			path[i]->BI='L';
		}
		else path[i]->BI='R';
	}
	if(mark==0)
	{
		return H;
	}
	D=dir[mark];
	X=path[mark];
	Y=path[mark+1];
	if(X->BI!=D)
	{
		X->BI='B';
		return H;
	}
	//rebalancing 1
	if(Y->BI==D)
	{
		if(D=='L')
		{
			X->left=Y->right;
			Y->right=X;
		}
		else
		{
			X->right=Y->left;
			Y->left=X;
		}
		X->BI=Y->BI='B';
		F=path[mark-1];
		if(X==F->left)
		{
			F->left=Y;
		}
		else F->right=Y;
		return H;
	}
	//rebalancing 2
	//changing structure link
	if(D=='L')
	{
		Z=Y->right;
		Y->right=Z->left;
		Z->left=Y;
		X->left=Z->right;
		Z->right=X;
	}
	else
	{
		Z=Y->left;
		Y->left=Z->right;
		Z->right=Y;
		X->right=Z->left;
		Z->left=X;
	}
	F=path[mark-1];
	if(X==F->left)
	{
		F->left=Z;
	}
	else F->right=Z;
	
	//changing balance indicators
	if(Z->BI==D)
	{
		Y->BI=Z->BI='B';
		if(D=='L')
		{
			X->BI='R';
		}
		else X->BI='L';
	}
	else if(Z->BI=='B')
	{
		X->BI=Y->BI=Z->BI='B';
	}
	else
	{
		X->BI=Z->BI='B';
		Y->BI=D;
	}
	return H;
}
static int gName=0;

void preorderDotDump (NODE R, FILE* outputFile)
{
	if (R != NULL) 
	{
		fprintf (outputFile, "%d [label=%d,color=black];\n",R->key, R->key);
		if (R->left != NULL) 
		         fprintf (outputFile, "%d -> %d ;\n", R->key, (R->left)->key);
		
        	if (R->right != NULL)
            		fprintf (outputFile, "%d -> %d;\n", R->key, (R->right)->key);
        	preorderDotDump (R->right, outputFile);
        	preorderDotDump (R->left, outputFile);
    	}
}
void dotDump(NODE R, FILE *outFile)
{
	gName++;
	fprintf (outFile, "digraph BST {\n",gName);
	preorderDotDump (R, outFile);
    	fprintf (outFile, "}\n");
}



FILE *OutputFile;
void main()
{
	FILE *pipe;
	NODE H=NULL;
	int n,k,j;
    int m=0;
        
	H=Create_Leaf(0,H);
	H->left=H->right=H;
	
	
	printf("\n Enter number of nodes ");
	scanf("%d",&n);
    OutputFile = fopen ("avltree.dot", "w");
    fclose (OutputFile);
        
        
	for(j=0;j<n;j++)
	{
		printf("Enter element");
		scanf("%d",&k); //redirect from file "avlIP"
		H=insert(k,H);
	}
      
	OutputFile=fopen("avltree.dot","a");
	if(OutputFile != NULL) 
    {
        if(H->left!=NULL)
			dotDump(H->left,OutputFile);
        else dotDump(H->right,OutputFile);
	}
	
	
	fclose(OutputFile);
        pipe=popen("dot -Tps avltree.dot -o avltree.ps","w");
	pclose(pipe);	
	pipe=popen("evince avltree.ps","r"); 
	pclose(pipe);
}
