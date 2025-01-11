#include<iostream>

int isSumsetSum(int *arr,int n,int X)
{
    if( X==0)
        return true;
    
    if(n==0)
        return false;
    
    if(arr[0]> X) 
        return isSumsetSum(arr+1,n-1,X);
    return isSumsetSum(arr+1,n-1,X) || isSumsetSum(arr+1, n-1, X-arr[0]);

}

int isSubarrSum(int arr[], int n, int X)
{
    int MAT[X+1][n+1];

    for(int i=0; i<=n; i++)
        MAT[0][i]=true;
    for (int i=1; i<=X; i++)
        MAT[i][0]= false;

    for(int i=1; i<= X; i++)
    {
        for(int j=1; j<=n ;j++)
        {
            MAT[i][j] = MAT[i][j-1];
            if( i>=arr[j-1])
                MAT[i][j] = MAT[i][j] || MAT[i-arr[j-1]][j-1];
        }
    }
    return MAT[X][n];

}
int main()
{
    int arr[]={3,2,7,1};
    int n=sizeof(arr)/4;

    printf("%d \n",isSumsetSum(arr,n,6));
    printf("%d \n",isSubarrSum(arr,n,8));

}