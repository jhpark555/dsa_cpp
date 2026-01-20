#include <iostream>

int main()
{
    char arr[]={1,4,5,6,7,9,9,10};
    int n=sizeof(arr);
    char *a,*b,*c;
    int sum=10;
    
    a=&arr[0]; b=&arr[n-1];
    
    while(a<b){
       // printf("%d %d \n",*a,*b);
        if(*a+*b > sum) b--;
        else if(*a+*b<sum) a++;
        else if(*a+*b==sum) {
            printf("yes, %d %d \n",*a,*b);
            break;
        }
       
    }
    
    a=&arr[0]; b=&arr[1]; c=&arr[2];
    
    while(a<&arr[n-1]){
        
        if(*b + *c >sum-*a) c--;
        else if(*b +*c < sum-*a) b++;
        else if(*b +*c ==sum-*a) {
            printf("yes %d %d %d \n",*a,*b,*c);
            break;
        }
        a++;
        
    }
    
   

    return 0;
}