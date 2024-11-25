#include <stdio.h>


int numOfPaths(int m,int n)
{
    if(m==0 && n==0) return 0;  //cell(0,0)
    if(m==0 || n==0) return 1;   //first row/col

    return numOfPaths(m-1,n) + numOfPaths(m,n-1);

}

int numOfPathsDP(int m,int n)
{
    int cache[m][n];

    for(int i=0; i< m;i++)    //1st row
        cache[i][0]=1;
    for( int j=0; j<n ;j++)
        cache[0][j]=1;      //1st col

    for(int i=1; i<m;i++)
        for(int j=1;j<n;j++)
         {
            cache[i][j]=cache[i-1][j]+cache[i][j-1];
         }   
    return cache[m-1][n-1];
}

int main()
{
   // int ret= numOfPaths(3,4);

    int ret= numOfPathsDP(3,4);

    printf("ret=%d \n",ret);

}