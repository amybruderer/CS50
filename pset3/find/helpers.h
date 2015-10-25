/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);

/**
 * Swaps the value of two numbers
 */
void swap(int* a, int* b);

/**
 * Sorts array of n values using bubble sort.
 */
void bubbleSort(int values [], int n);

/**
 * Sorts array of n values using selection sort.
 */
void selectionSort(int values [], int n);

/**
 * Sorts array of n values using insertion sort.
 */
void insertionSort(int values [], int n);

/**
 * Performs linear search for value.
 * Returns true if value is in array of n values, else false.
 */
bool linearSearch(int value, int values[], int n);

/**
 * Performs binary search for value.
 * Returns true if value is in array of n values, else false.
 */
bool binarySearch(int value, int values[], int n);
