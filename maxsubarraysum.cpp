#include <stdio.h>

int maxSubArraySum( int *arr, int n)
{

    int maxSum=0;
    int tempSum=0;

    for (int i=0; i< n;i++)
    {
        tempSum=arr[i];

        for(int j=i+1;j <n; j++)
        {
            tempSum += arr[j];
            if ( tempSum > maxSum)
                maxSum=tempSum;
        }
    }
    return maxSum;
}

int main()
{
    int arr[]={-2,-3,4,-1,-2,1,5,-3};
    int n=sizeof(arr)/ sizeof(int);

    int ret= maxSubArraySum(arr,n);
    printf("ret=%d \n",ret);
}