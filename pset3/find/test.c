/**
 * test.c
 * 
 * Amy Bruderer
 * amy.bruderer@gmail.com
 *
 * Tests functions found in helpers.h
 */

#include <stdio.h>

#include "helpers.h"

// prototypes
void printValues(int values[], int n);
bool arraysEqual(int values1[], int n1, int values2[], int n2);
void testSearch();
void testSwap();
void testBubbleSort();
void testSelectionSort();
void testInsertionSort();

int main(void)
{
    testSearch();
    testSwap();
    testBubbleSort();
    testSelectionSort();
    testInsertionSort();

    return 0;
}

/**
 * Prints the contents of values to the screen.
 */
void printValues(int values[], int n)
{
    printf("{ ");
    for (int i = 0; i < n; ++i)
    {
        if (i)
        {
            printf(", ");
        }

        printf("%i", values[i]);
    }
    printf(" }");
}

/**
 * Checks two arrays and returns true if their contents at each index is the same.
 * Returns false otherwise.
 */
bool arraysEqual(int values1[], int n1, int values2[], int n2)
{
    if (n1 != n2)
    {
        return false;
    }

    for (int i = 0; i < n1; ++i)
    {
        if (values1[i] != values2[i])
        {
            return false;
        }
    }

    return true;
}

void testSearch()
{
    int values[] = { 13, 7, 42, 6, 12 };
    const int ARRAY_SIZE = sizeof(values) / sizeof(values[0]);

    // make sure 7 is found
    if (search(7, values, ARRAY_SIZE))
    {
        printf("testSearch() passed: 7 found in ");
        printValues(values, ARRAY_SIZE);
        printf(".\n");
    }
    else
    {
        printf("testSearch() failed: 7 not found in ");
        printValues(values, ARRAY_SIZE);
        printf(".\n");
    }

    // make sure 17 is not found
    if (search(17, values, ARRAY_SIZE))
    {
        printf("testSearch() failed: 17 found in ");
        printValues(values, ARRAY_SIZE);
        printf(".\n");
    }
    else
    {
        printf("testSearch() passed: 17 not found in ");
        printValues(values, ARRAY_SIZE);
        printf(".\n");
    }
}

void testSwap()
{
    int a = 1;
    int b = 2;

    swap(&a, &b);

    // make sure the values are swapped
    if ((a == 2) && (b == 1))
    {
        printf("swap() passed.\n");
    }
    else
    {
        printf("swap() failed.\n");
    }
}

void testBubbleSort()
{
    int values[] = { 13, 7, 42, 6, 12 };
    const int ARRAY_SIZE = sizeof(values) / sizeof(values[0]);

    int expected[] = { 6, 7, 12, 13, 42 };

    bubbleSort(values, ARRAY_SIZE);

    // verify values is sorted
    if (arraysEqual(values, ARRAY_SIZE, expected, ARRAY_SIZE))
    {
        printf("testBubbleSort() passed.\n");
    }
    else
    {
        printf("testBubbleSort() failed: ");
        printValues(values, ARRAY_SIZE);
        printf(" is not sorted.\n");
    }
}

void testSelectionSort()
{
    int values[] = { 13, 7, 42, 6, 12 };
    const int ARRAY_SIZE = sizeof(values) / sizeof(values[0]);

    int expected[] = { 6, 7, 12, 13, 42 };

    selectionSort(values, ARRAY_SIZE);

    // verify values is sorted
    if (arraysEqual(values, ARRAY_SIZE, expected, ARRAY_SIZE))
    {
        printf("testSelectionSort() passed.\n");
    }
    else
    {
        printf("testSelectionSort() failed: ");
        printValues(values, ARRAY_SIZE);
        printf(" is not sorted.\n");
    }
}

void testInsertionSort()
{
    int values[] = { 13, 7, 42, 6, 12 };
    const int ARRAY_SIZE = sizeof(values) / sizeof(values[0]);

    int expected[] = { 6, 7, 12, 13, 42 };

    insertionSort(values, ARRAY_SIZE);

    // verify values is sorted
    if (arraysEqual(values, ARRAY_SIZE, expected, ARRAY_SIZE))
    {
        printf("testInsertionSort() passed.\n");
    }
    else
    {
        printf("testInsertionSort() failed: ");
        printValues(values, ARRAY_SIZE);
        printf(" is not sorted.\n");
    }
}
