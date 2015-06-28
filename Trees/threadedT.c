//Program to make a inorder successor Threaded tree using given i/p nodes
//redirect input nodes from file "threadIP" while running

#include <stdio.h>
#include <stdlib.h>

struct node
{
         struct node *left;
         int data;
         struct node *right;
		 struct node *thread;
         int th;
};

typedef struct node * NODE;

NODE a[50];
int i=0;

void addnew( struct node ** , int );

NODE getnode()
{
         return ( struct node *) malloc( sizeof( struct node ));
}

void inorder( struct node *q )
{
        if( q!= NULL )
        {
                 inorder( q->left );
                 a[i++] = q;
                 inorder( q->right);
        }
}

//creates threads to the corresponding inorder successor
void CreateThread( NODE r)
{
        if(r == NULL)
                return;
        if(r->left)
              CreateThread(r->left);
        i++;
        if(r->right)
                CreateThread(r->right);
        else
        {
                r->thread = a[i] ;
                
                r->th = 1;
        }
}

//function to get the leftmost child
NODE left( NODE  t)
{
  	if(t == NULL)
        return NULL;
   	while(t->left)
  		      t = t->left;
   	return t;
}


void print(NODE root)
{
        NODE t;
        t = left(root);

        while(t)
        {
                printf("%d\t" , t->data);
                if(t->th)
                        t = t->thread;
                else
                        t = left(t->right);
        }
}
static int gName=0;
void preorderDotDump (NODE root, FILE* outputFile)
{
	if (root != NULL) 
	{
		if (root->left != NULL) 
		         fprintf (outputFile, "%d -> %d ;\n", root->data, (root->left)->data);
		
		
		if (root->thread != NULL) 
		         fprintf (outputFile, "%d -> %d[style=dashed];\n", root->data, (root->thread)->data);
		
        if (root->right != NULL)
           		fprintf (outputFile, "%d -> %d;\n", root->data, root->right->data);
            	
      	preorderDotDump (root->right, outputFile);
        	
      	preorderDotDump (root->left, outputFile);
    }
}

void dotDump(NODE root, FILE *outFile)
{
	gName++;
	fprintf (outFile, "digraph thread{\n",gName);
	
	preorderDotDump (root, outFile);
    fprintf (outFile, "}\n");
}
FILE *outputFile;





void main( )
{
		FILE *pipe;
        struct node *R;
        int n , j , data;
        R = NULL;
        printf("Enter number of nodes to create \n");
        scanf("%d", &n);
		outputFile = fopen ("thread.dot", "a");
        for(j=0; j<n ;j++)
        {
                printf("Enter the %d element\n",j+1);
                scanf("%d", &data );
                addnew( &R , data );
        }
		
        inorder( R); //traverses the BST created in inorder and stores the address of nodes in an array
        i = 0;
        
        CreateThread(R); //creates the threads to the generated BST
        dotDump (R,  outputFile);fclose (outputFile);
        printf("\nInorder Traversal of the tree is\n");	
        print(R);  //traverses the tree in inorder using the threads created and prints the data in the nodes
        
        pipe=popen("dot -Tps thread.dot -o thread.ps","w");
		pclose(pipe);	
		pipe=popen("evince thread.ps","r"); 
		pclose(pipe);

}


void addnew( struct node **q,int data )
{
        if( *q == NULL )
        {
           	*q = getnode( );
           	(*q)->left = NULL;
           	(*q)->right =NULL;
           	(*q)->data = data;
           	(*q)->thread=NULL;
           	return;
        }

        if( (*q)->data > data )
         	addnew( &(*q)->left , data );
        else
         	addnew( &(*q)->right , data );
}              
