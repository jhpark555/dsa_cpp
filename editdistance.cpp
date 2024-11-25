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

int main()
{
    char *str1 = "sunday";
    char *str2 = "saturday";

    int distance = editDistance(str1, str2);
    printf("Edit distance: %d\n", distance);

    return 0;
}