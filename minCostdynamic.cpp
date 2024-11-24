//#include <stdio.h>
#include <iostream>

using namespace std;

#define M 3
#define N 4

int MEM[M][N]={0};

int cost[M][N]={
    {1,3,5,8},
    {4,2,1,7},
    {4,3,2,3},
};

int getMin(int a,int b)
{
    return a<b? a:b;
}

int minPathCost(int cost[M][N], int m, int n)
{
    if(MEM[M][N]!=0 ) 
        return MEM[M][N];

    if( m==0 && n==0)
        MEM[m][n]= cost[0][0];

    else if(m==0)
       // return minPathCost(cost,m,n-1) +cost[0][n];
       MEM[m][n]= minPathCost(cost,m,n-1) +cost[0][n];
    
    else if (n==0)
       // return minPathCost(cost,m-1,n) + cost[m][0];
       MEM[m][n]= minPathCost(cost,m-1,n) + cost[m][0];

    else{
        int x = minPathCost(cost,m-1,n) ;
        int y = minPathCost(cost,m,n-1) ;
        //return (getMin(x,y) + cost[m][n]);
        MEM[m][n]= (getMin(x,y) + cost[m][n]);
    }
    return MEM[m][n];
}

int minPathCostDP(int cost[M][N],int m, int n)
{
    MEM[0][0]=cost[0][0];
    
    for(int j=1; j <N ; j++)
        MEM[0][j]=MEM[0][j-1]+cost[0][j];
    for(int i=1; i< M; i++ )
        MEM[i][0]= MEM[i-1][0]+cost[i][0];

    for(int i=1; i< M;i++)
        for( int j=1; j<N; j++)
            MEM[i][j]= getMin(MEM[i-1][j], MEM[i][j-1]) +
                cost[i][j];
    return MEM[M-1][N-1];

}

int  main()
{
    //int ret= minPathCost(cost,M,N);
    int ret =minPathCostDP(cost,M,N);
   // printf("ret=%d \n",ret);
   cout<<ret<<endl;

    return 0;
}
