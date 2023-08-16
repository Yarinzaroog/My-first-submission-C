// Course: Advanced C programming
// exercise 1, question 1
// file name: ex1_q1.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------- //
//
//	Assigned by:
//		Student1_Yarin_Zaroog #322516857
//		Student2_Gal_Mizrachi #322622879
//
// --------------------------- //

// function declarations section:
int* scanArray(int*);
void printArray(int*, int);
int arrangeArray(int**, int);

// --------------------------- //

// main section:
// DO NOT CHANGE the following function:
int main()
{
	int* arr, n, k;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	arr = scanArray(&n);
	k = arrangeArray(&arr, n);

	// write output:
	printf("Output:\n");
	printf("Size of k: %d\n", k);
	printf("Sorted array:\n");
	printArray(arr, n);
	free(arr);

	return 0;
}
// --------------------------- //


// DO NOT CHANGE the following function:
int* scanArray(int* n)
{
	int i;
	int* arr;

	printf("Enter array size: ");
	scanf("%d", n);

	arr = (int*)malloc(sizeof(int) * (*n));
	for (i = 0; i < *n; ++i)
	{
		printf("Enter value #%d: ", i + 1);
		scanf("%d", arr + i);
	}

	return arr;
}
// --------------------------- //


// DO NOT CHANGE the following function:
void printArray(int* arr, int n)
{
	int i;
	printf("{");
	for (i = 0; i < n; ++i)
		printf("%d%s", arr[i], i == n - 1 ? "" : ", ");
	printf("}\n");
}
// --------------------------- //

/// <summary>
/// Combine the two groups using realloc and memcpy only. 
/// </summary>
/// <param>int **arr - Address of the array pointer</param>
/// <param>int n - Size of the array</param>
/// <returns>Size of the first group</returns>
int arrangeArray(int** arr, int n)
{
	// your code:
	int i, k=0, j = 0, new_size;
	for (i = 0; i < n - 1; i++)
	{
		if ((*arr)[i] > (*arr)[i + 1])
			k = i + 1;
	}
	new_size = n + k;
	*arr = (int*)realloc((*arr), new_size * sizeof(int));
	if (*arr) {
		for (i = n; i < new_size; i++)
		{
			(*arr)[i] = (*arr)[i - n];
		}
		memcpy(*arr, *arr + k, n * sizeof(int));
		*arr = (int*)realloc(*arr, n * sizeof(int));
		if (*arr) {
			return k;
		}
	}
	return 0;
}
// --------------------------- //