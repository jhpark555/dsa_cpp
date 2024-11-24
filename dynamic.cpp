#include <stdio.h>
#include <string.h>

#define N 10
using namespace std;


int cost[4][4]={
    {0,10,75,94}
    ,{-1,0,35,50}
    ,{-1,1,0,80}
    ,{-1,-1,-1,0}};

int memo[N]={0};

int memom[4][4]={0};

#if 1
int calculateMinCost(int s , int d){
    if(s==d ||s==d-1) 
        return cost[s][d];

    if (memom[s][d]==0){
        int minCost = cost[s][d];

        for(int i=s+1; i<d; i++){
            int temp=calculateMinCost(s,i)+
                calculateMinCost(i,d);
            if(temp< minCost)
                minCost= temp;
        }
        memom[s][d]=minCost;
    }
    return memom[s][d];
}

#else
int calculateMinCost(int s,int d){
    if(s==d || s ==d-1)
        return cost[s][d];

    int minCost=cost[s][d];

    for( int i=s+1; i<d; i++){
        int temp= calculateMinCost(s,i) + calculateMinCost(i,d);
        if(temp < minCost)
            minCost=temp;
    }
    return minCost;
}
#endif

int calculateMinCost1(int cost[][4])
{
    int minCost[4];
    
    minCost[0]=0;
    minCost[1]=cost[0][1];

    for (int i=2; i< 4; i++)
    {
        minCost[i]=cost[0][i];

        for( int j=1; j<i; j++)
        {
            if(minCost[i] > minCost[j]+ cost[i][j])
                minCost[i]= minCost[j] + cost[i][j];

        }
        
    }
    return minCost[4-1];
}


#if 1

int fib(int n)
{
    int arr[N];
    
    arr[1]=1; arr[2]=1;
    
    for( int i=3 ; i<=n ; i++)
        arr[i] = arr[i-1] + arr[i-2];
    
    return arr[n];
}

#else
int fib(int n){
    if (memo[n] !=0) {
        return memo[n];
    }

    if( n==1 || n==2) 
        return memo[n]=1;
    else
        return memo[n]=fib(n-1)+fib(n-2);
}
#endif


int maxSubStringLength(char *str)
{

   int n= strlen(str);
   int maxLen=0;

   for ( int i=0; i< n; i++)
   {
    for( int j=i+1; j< n; j +=2 )
    {
        int len =j-i+1;
        if (maxLen>=len) continue;

        int lSum=0, rSum=0;
        for( int k=0; k<len/2; k++)
        {
            lSum += str[i+k]-'0';
            rSum +=str[i+k+len/2]-'0';
        }
        if(rSum==lSum)
            maxLen=len;
    }
   }
    return maxLen;
   
}

int sum[7][7];

int maxSubStringLengthDP(char *str)
{
    int n= strlen(str);
    int maxLen=0;

    for(int i=0;i< n; i++)
        sum[i][i]=str[i]-'0';

    for (int len=2; len<=n; len++)
    {
        for( int i=0; i< n-len+1; i++)
        {
            int j=i+len-1;
            int k=len/2;
            sum[i][j]=sum[i][j-k] +sum[j-k+1][j];
            if(len%2==0 && sum[i][j-k]==sum[j-k+1][j]
                && len> maxLen)
                maxLen=len;
        }
    }
    return maxLen;

}

int main(int argc,char *argv[])
{
    
    int ret= calculateMinCost(0,3);
    printf("result=%d \n",ret);

    ret= fib(3);
    printf("fin= %d \n",ret);

    ret= calculateMinCost1(cost);
    printf("mincost=%d \n",ret);

    ret= maxSubStringLength("9430723");
    printf("max len=%d \n",ret);

    ret= maxSubStringLengthDP("9430723");
    printf("max len=%d \n",ret);

    return 0;
}