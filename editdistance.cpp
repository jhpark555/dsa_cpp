#include <stdio.h>
#include <string.h>
#include <algorithm> // for std::min

int getMinimum(int d, int u, int i)
{
    return std::min(std::min(d, u), i);
}

int editDistance(char *str1, char *str2)
{
    if (str1 == NULL || *str1 == '\0')
    { // str1 is empty
        return strlen(str2);
    }
    if (str2 == NULL || *str2 == '\0')
    {
        return strlen(str1);
    }
    if (*str1 == *str2)
    {
        return editDistance(str1 + 1, str2 + 1);
    }

    int d = editDistance(str1 + 1, str2);     // Deletion
    int u = editDistance(str1, str2 + 1);     // Insertion
    int i = editDistance(str1 + 1, str2 + 1); // Substitution

    return getMinimum(d, u, i) + 1;
}

int editDistDP(char *s1,char *s2, int m,int n)
{
    int EditD[m+1][n+1];

    for(int j=0;j <=m ;j++)   //top row
        EditD[0][j]= j;
    for (int i=0; i<=n; i++)  //left col
        EditD[i][0]=i;

    for( int i=1; i<=m ;i++)
        for(int j=1;j<=n; j++)
        {
            if(s1[i-1]==s2[j-1])
                EditD[i][j] =EditD[i-1][j-1];
            else
                EditD[i][j]= getMinimum(
                    EditD[i][j-1] ,EditD[i-1][j],EditD[i-1][j-1]
                ) +1;
        }
        return EditD[m][n];
}



int main()
{
    char *str1 = "sunday";
    char *str2 = "saturday";

    //int distance = editDistance(str1, str2);
    int distance = editDistDP(str1, str2,strlen(str1),strlen(str2));
    printf("Edit distance: %d\n", distance);

    return 0;
}