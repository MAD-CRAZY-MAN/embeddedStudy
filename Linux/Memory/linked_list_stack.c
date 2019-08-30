#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

struct node *top;

void Push(int data);
void Pop();
void Print_stack();

int main(void)
{
	top = NULL;

	Push(1);
	Push(2);
	Push(4);

	Print_stack();

	Pop();

	Print_stack();

	exit(0);
}

void Push(int data)
{
	struct node *ptr;

	ptr = (struct node*)malloc(sizeof(struct node));
	ptr->data = data;
	ptr->next = NULL;

	if (top == NULL)
	{
		top = ptr;
	}
	else
	{
		ptr->next = top;
		top = ptr;
	}
}

void Pop()
{
	struct node *ptr;
	ptr = (struct node*)malloc(sizeof(struct node));

	if (top == NULL)
	{
		printf("%s", "STACK IS EMPTY");
	}
	else
	{
		ptr = top;
		printf("pop data: %d\n\n", top->data);

		top = ptr->next;

		free(ptr);
	}
}

void Print_stack()
{
	struct node *temp;
	printf("Stack list\n");
	
	for (temp = top; temp->next != NULL; temp = temp->next)
	{
		printf("%d\n", temp->data);
	}
	printf("%d\n\n", temp->data);
}
