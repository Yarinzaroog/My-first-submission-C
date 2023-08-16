// Course: Advanced C programming
// exercise 1, question 3
// file name: ex1_q3.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>

// --------------------------- //
//
//	Assigned by:
//		Student1_Yarin_Zaroog #322516857
//		Student2_Gal_Mizrachi #322622879
//
// --------------------------- //

// structs and function declarations section:
typedef struct rectangle {
	int xTopSmall;
	int yTopSmall;
	int xButtomRight;
	int yButtomRight;
}rectangle;

typedef struct recElement {
	rectangle Rect;
	struct recElement* next;
}recElement;

int validateRectangle(rectangle* rec);
rectangle scanRectangle();
recElement* createElement();
recElement* createRectList();
rectangle findSmallest(recElement* head);
void printRectangle(rectangle* rec);
void printList(recElement* head);
void freeList(recElement* head);

// --------------------------- //

int main()
{
	rectangle rec;
	recElement* head = NULL;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	head = createRectList();

	printf("\n\nRectangle list:\n");
	printList(head);

	rec = findSmallest(head);

	printf("\n\nFilling rectangle:\n");
	printRectangle(&rec);

	freeList(head);
	head = NULL;

	printf("\n\n");

	return 0;
}
// --------------------------- //


/// <summary>
/// Function gets an address of a rectangle and check validity.
/// </summary>
/// <param>Address of rectangle</param>
/// <returns>0- if rectangle is not valid, 1-if rectangle is a valid, 2-if rectangle is a point</returns>
int validateRectangle(rectangle* rec)
{
	// your code:
	if (rec->xTopSmall<rec->xButtomRight && rec->yTopSmall>rec->yButtomRight)
		return 1;
	if (rec->xTopSmall == rec->xButtomRight && rec->yTopSmall == rec->yButtomRight)
		return 2;
	else
		return 0;
}
// --------------------------- //



/// <summary>
/// Function scan a rectangle in the plane,
/// Used as auxiliary function for createElement.
/// </summary>
/// <param>None</param>
/// <returns>a newly scanned rectangle</returns>
rectangle scanRectangle()
{
	// your code:
	rectangle new_rec;
	printf("enter 1 top POINT parameter:\n");
	scanf_s("%d", &(new_rec.xTopSmall));
	scanf_s("%d", &(new_rec.yTopSmall));
	printf("enter 1 buttom POINT parameter:\n");
	scanf_s("%d", &(new_rec.xButtomRight));
	scanf_s("%d", &(new_rec.yButtomRight));
	while (validateRectangle(&new_rec) == 0)
	{
		printf("enter 1 top POINT parameter:\n");
		scanf_s("%d", &(new_rec.xTopSmall));
		scanf_s("%d", &(new_rec.yTopSmall));
		printf("enter 1 buttom POINT parameter:\n");
		scanf_s("%d", &(new_rec.xButtomRight));
		scanf_s("%d", &(new_rec.yButtomRight));
	}
	return new_rec;
}
// --------------------------- //


/// <summary>
/// Function allocate a new recElement.
/// Calls scanRectangle during the process. 
/// if the scanned rectangle is a point, returns NULL.
/// </summary>
/// <returns>New allocated recElement or NULL if rectangle is a point</returns>
recElement* createElement()
{
	// your code:
	recElement* new_element = (recElement*)malloc(sizeof(recElement));
	new_element->Rect = scanRectangle();
	if (new_element == NULL)
		return NULL;
	if (validateRectangle(&(new_element->Rect)) == 2)
	{
		free(new_element);
		new_element = NULL;
		return NULL;
	}
	return new_element;
}
// --------------------------- //


/// <summary>
/// Function creates a list of rectangles.
/// Calls function createElement in a loop.
/// Scan stops when createElement returns null.
/// </summary>
/// <param>None</param>
/// <returns>The Euclidean distance between p1 and p2</returns>
recElement* createRectList()
{
	// your code:
	recElement* head = createElement();
	recElement* temp = head;
	while (temp)
	{
		temp->next = createElement();
		temp = temp->next;
	}
	return head;
}
// --------------------------- //


/// <summary>
/// Function gets a list and returns the filling rectangle
/// </summary>
/// <param>recElement* head - the list of rectangles</param>
/// <returns>The filling rectangle. if the list is empty return rectangle with (0,0,0,0)</returns>
rectangle findSmallest(recElement* head)
{
	// your code:
	rectangle* answer = (rectangle*)malloc(sizeof(rectangle));
	recElement* current = head;
	if (&(head->next) == NULL)
	{
		answer->xTopSmall = 0;
		answer->xButtomRight = 0;
		answer->yButtomRight = 0;
		answer->yTopSmall = 0;
	}
	if (current->Rect.xTopSmall < current->next->Rect.xTopSmall)
		answer->xTopSmall = current->Rect.xTopSmall;
	else
		answer->xTopSmall = current->next->Rect.xTopSmall;
	if (current->Rect.yTopSmall > current->next->Rect.yTopSmall)
		answer->yTopSmall = current->Rect.yTopSmall;
	else
		answer->yTopSmall = current->next->Rect.yTopSmall;
	if (current->Rect.xButtomRight > current->next->Rect.xButtomRight)
		answer->xButtomRight = current->Rect.xButtomRight;
	else
		answer->xButtomRight = current->next->Rect.xButtomRight;
	if (current->Rect.yButtomRight < current->next->Rect.yButtomRight)
		answer->yButtomRight = current->Rect.yButtomRight;
	else
		answer->yButtomRight = current->next->Rect.yButtomRight;
	current = current->next;
	while (current->next)
	{
		if (answer->xTopSmall > current->next->Rect.xTopSmall)
			answer->xTopSmall = current->next->Rect.xTopSmall;
		if (answer->yTopSmall < current->next->Rect.yTopSmall)
			answer->yTopSmall = current->next->Rect.yTopSmall;
		if (answer->xButtomRight < current->next->Rect.xButtomRight)
			answer->xButtomRight = current->next->Rect.xButtomRight;
		if (current->Rect.yButtomRight > current->next->Rect.yButtomRight)
			answer->yButtomRight = current->next->Rect.yButtomRight;
		current = current->next;
	}
	return *answer;
}
// --------------------------- //


/// <summary>
/// Function print rectangle cordinates on screen. (not drawing the rectangle!)
/// </summary>
/// <param>rectangle* rec - pointer to rectangle</param>
/// <returns>None</returns>
void printRectangle(rectangle* rec)
{
	// your code:
	printf("[(%d,%d)(%d,%d)]", rec->xTopSmall, rec->yTopSmall, rec->xButtomRight, rec->yButtomRight);
}
// --------------------------- //


/// <summary>
/// Function print list on screen.
/// </summary>
/// <param>recElement* head - list address</param>
/// <returns>None</returns>
void printList(recElement* head)
{
	// your code:
	while (head)
	{
		printRectangle(&(head->Rect));
		head = head->next;
	}
}
// --------------------------- //


/// <summary>
/// Function free alocated memory of list 
/// </summary>
/// <param>recElement* head - pointer to head of the list</param>
/// <returns>None</returns>
void freeList(recElement* head)
{
	// your code:
	recElement* temp = head;
	while (temp)
	{
		head = head->next;
		free(temp);
		temp = head;
	}
}
// --------------------------- //