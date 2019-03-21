#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "Fibonacci.h"

int powerfunction(int i);

HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
    int largerlength, smallerlength, i, k, j=0, l;
    HugeInteger *newhugeint = malloc(sizeof(HugeInteger)*1000);

    if(p->length > q->length)
    {
        largerlength = p->length;
        smallerlength = q->length;
        k = 0;
    }

    else if(p->length < q->length)
    {
        largerlength = q->length;
        smallerlength = p->length;
        k = 1;
    }
    else
    {
        largerlength = q->length;
        smallerlength = q->length;
        k = 2;
    }

    newhugeint->digits = malloc(sizeof(int)*(largerlength + smallerlength));

    for(i=0; i<smallerlength; i++)
    {

        if(p->digits[i] + q->digits[i] + j >= 10)
        {
            newhugeint->digits[i] = p->digits[i] + q->digits[i] + j - 10;
            j = 1;
        }
        else
        {
            newhugeint->digits[i] = p->digits[i] + q->digits[i] + j;
            j = 0;
        }

    }

    for(l = smallerlength; l <= largerlength; l++)
    {
        if(k==0)
        {
            newhugeint->digits[l] = p->digits[l];

            if(j==1)
            {
                newhugeint->digits[l]++;
                j=0;
            }
        }
        else if(k==1)
        {
            newhugeint->digits[l] = q->digits[l];

            if(j==1)
            {
                newhugeint->digits[l]++;
                j=0;
            }

        }
        else
        {
            if(j==1)
            {
                newhugeint->digits[largerlength++] = 1;
                break;
            }

        }

    }
    newhugeint->length = largerlength;

    return newhugeint;
}

HugeInteger *hugeDestroyer(HugeInteger *p)
{
    if(p == NULL)
        return NULL;

    free(p->digits);
    free(p);
    p = NULL;

    return NULL;
}

HugeInteger *parseString(char *str)
{
    int i;
    HugeInteger *newhugeint;

    if(str == NULL)
        return NULL;

    newhugeint = malloc(sizeof(HugeInteger));
    newhugeint->digits = malloc(sizeof(int)*strlen(str));

    if(strlen(str) == 0)
    {
        newhugeint->digits[0] = 0;
        newhugeint->length = 1;
    }
    else
    {
        for(i=0; i < strlen(str); i++)
            newhugeint->digits[strlen(str)-1-i] = str[i]-'0';
        newhugeint->length = strlen(str);
    }

    if(newhugeint->digits == NULL || newhugeint == NULL)
        return NULL;

    return newhugeint;
}

HugeInteger *parseInt(unsigned int n)
{
    int i=0, k;

    HugeInteger *newhugeint = malloc(sizeof(HugeInteger)*1000);
    newhugeint->digits = malloc(sizeof(int)*(1000));

    if(n == 0)
    {
        newhugeint->digits[0] = 0;
        newhugeint->length = 1;
        return newhugeint;
    }

    while(n > 0)
    {
        k = n%10;
        newhugeint->digits[i] = k;
        n /= 10;
        i++;
    }

    newhugeint->length = i;

    if(newhugeint->digits == NULL || newhugeint == NULL)
        return NULL;

    return newhugeint;
}
int powerfunction(int i)
{
    int k, power = 1;

    for(k=0; k<i; k++)
        power *= 10;

    return power;
}

unsigned int *toUnsignedInt(HugeInteger *p)
{
    int i;
    unsigned int converting = 0, *returninguint = malloc(sizeof(int));

    if(p == NULL || p->digits == NULL || p->length > 10 || p->digits[p->length - 1] > 4)
        return NULL;

    for(i=0; i < p->length; i++)
    {
        if(i==0)
            converting += p->digits[i];
        else
            converting += (p->digits[i]*powerfunction(i));
    }

    *returninguint = converting;

    return returninguint;
}

HugeInteger *fib(int n)
{
    int i;

    HugeInteger *first = NULL, *second = NULL, *add = NULL;

    //add = malloc(sizeof(HugeInteger)*1000);
    first = parseInt(0);
    second = parseInt(1);

    if(n==0)
        return first;
    if(n==1)
        return second;

    for(i=2; i<= n; i++)
    {
        add = hugeAdd(first, second);
        //hugeDestroyer(first);
        //first = malloc(sizeof(HugeInteger));

        first = second;
       // hugeDestroyer(first);
       // first = malloc(sizeof(HugeInteger));

        second = add;

    }
    return add;
}

double difficultyRating(void)
{
    return 3.0;
}

double hoursSpent(void)
{
    //1+3+3+3
    return 10.0;
}
