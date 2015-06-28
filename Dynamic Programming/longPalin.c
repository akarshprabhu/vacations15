//Program to find the longest palindrome subsequence using Dyanamic programming

#include<stdio.h>
#include<string.h>
 

int max (int x, int y) 
{
 return (x > y)? x : y; 
}
 

int gentable(char *str)
{
   int n = strlen(str);
   int i, j, ln;
   int table[n][n];  
 
 
   //initialize table as a letter alone is palindrome of length 1
   for (i = 0; i < n; i++)
      table[i][i] = 1;
 
   
    for (ln=2; ln<=n; ln++)
    {
        for (i=0; i<n-ln+1; i++)
        {
            j = i+ln-1;
            if (str[i] == str[j] && cl == 2)
               table[i][j] = 2;
               
            else if (str[i] == str[j])
               table[i][j] = table[i+1][j-1] + 2;
               
            else
               table[i][j] = max(table[i][j-1], table[i+1][j]);
               
        }
    }
 
    return table[0][n-1];
}
 

void main()
{
    char seq[] = "ama is malayalam";
 
    printf ("The length of the longest palindrome is %d \n", gentable(seq));
    
}
