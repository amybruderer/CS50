/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Swaps the value of two numbers
 */
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // linearly search for value
    for (int i = 0; i < n; ++i)
    {
        if (value == values[i])
        {
            return true;
        }
    }

    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    bubbleSort(values, n);
    return;
}

/**
 * Sorts array of n values using bubble sort.
 */
void bubbleSort(int values [], int n)
{
    for (int i = 0, outerLimit = n - 1; i < outerLimit; ++i)
    {
        bool didSwap = false;
        for (int j = 0, k = j + 1, innerLimit = outerLimit - i; j < innerLimit; ++j, ++k)
        {
            if (values[j] > values[k])
            {
                swap(&(values[j]), &(values[k]));
                didSwap = true;
            }
        }

        if (!didSwap)
        {
            break;
        }
    }
    return;
}

/**
 * Sorts array of n values using selection sort.
 */
void selectionSort(int values [], int n)
{
    for (int i = 0, limit = n - 1; i < limit; ++i)
    {
        // find smallest unsorted element
        int min = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (values[j] < values[min])
            {
                min = j;
            }
        }

        // move it to the sorted portion of the list
        if (min != i)
        {
            swap(&values[i], &values[min]);
        }
    }
    return;
}

/**
 * Sorts array of n values using insertion sort.
 */
void insertionSort(int values [], int n)
{
    for (int i = 1, limit = n - 1; i < limit; ++i)
    {
        for (int j = i + 1, k = i; j > 0; --j, --k)
        {
            if (values[j] < values[k])
            {
                swap(&values[j], &values[k]);
            }
        }
    }
    return;
}
