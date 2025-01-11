#include <iostream>
#include <cstring>

int isInterleaving(char *A,char *B,char *C)
{
    if(!(*A) && !(*B) && !(*C))
        return true;

    if( *C =='\0')
        return false;
    
    if(*A =='\0' && *B =='\0')
        return false;

    int first = false;
    int second = false;

    if(*A==*C)
        first = isInterleaving(A+1,B,C+1);
    if(*B ==*C)
        second = isInterleaving(A,B+1,C+1);

    return (first || second);
    
}

bool isInterleaved(const char* A,const char *B, const char *C)
{
    int M=strlen(A);
    int N=strlen(B);

    if(strlen(C) !=M+N)
        return false;

    bool MAT[M+1][N+1];
    MAT[0][0]=true;

    for(int i=1; i<=M ;i++)
    {
        if(A[i-1] !=C[i-1])
            MAT[i][0]=false;
        else
            MAT[i][0]=MAT[i-1][0];
    }
    for (int j=1; j<=N; j++)
    {
        if(B[j-1] !=C[j-1])
            MAT[0][j]=false;
        else
            MAT[0][j]=MAT[0][j-1];
    }
    for(int i=0;i <=M; i++)
    {
        for(int j=1; j <=N; j++)
        {
            if(A[i-1] ==C[i+j-1] && B[j-1]!= C[i+j-1])
                MAT[i][j]=MAT[i-1][j];
            else if (A[i-1] !=C[i+j-1] && B[j-1]==C[i+j-1])
                MAT[i][j]=MAT[i][j-1];
            else if (A[i-1]==C[i+j-1] && B[j-1]==C[i+j-1])
                MAT[i][j]=(MAT[i-1][j] || MAT[i][j-1]);
            else 
                MAT[i][j]=false;
        }
    }
    return MAT[M][N];
}
int main()
{
    char *a="xyz";
    char *b="abcd";
    char *c="xabyczd";

    bool ret= isInterleaved(a,b,c) ;// isInterleaving(a,b,c);

    printf("%d ",ret);

}