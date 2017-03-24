#pragma once

void Array_print(int sourceArray[], int length)
{
    int i;
    for(i=0;i<length;i++)
    {
//		iprintf("Array[%i]= %i\n",i,sourceArray[i]);
    }
    return;
}


void Array_cloneInt(int sourceArray[], int clonedArray[], int length)
{
    int i;
    for(i=0;i<length;i++)
    {
        clonedArray[i] = sourceArray[i];
    }
    
    return;
}

int Array_getMin(int Array[], int length)
{
    int i;
    int min = Array[0];
    for (i = 1; i < length; i++)
    {
        if (min > Array[i])
            min = Array[i];
    }
    return min;
}

int Array_getMax(int Array[], int length)
{
    int i;
    int max = Array[0];
    for (i = 1; i < length; i++)
    {
        if (max < Array[i])
            max = Array[i];
    }
    return max;
}

bool Array_IsInArray(int value, int Array[], int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        if (value == Array[i])
            return true;
    }
    return false;
}
