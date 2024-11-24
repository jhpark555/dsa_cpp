#include <stdio.h>


int waysToScoreRe(int n)
{
    if (n<0) return 0;
    if(n==0) return 1;

    return waysToScoreRe(n-10) +waysToScoreRe(n-5) +waysToScoreRe(n-3) ;
}

int waysToScore(int n){

    int arr[n+1]={0},i;

    arr[0]=1;

    for(i =1; i<=n ;i++)
    {
        if(i-3>=0) arr[i] += arr[i-3];
        if(i-5 >=0) arr[i] +=arr[i-5];
        if(i-10 >=0) arr[i] +=arr[i-10];
    }
    return arr[n];

}
int main()
{

    int ret= waysToScore(13);
    printf("ret=%d \n",ret);
    return 0;
}