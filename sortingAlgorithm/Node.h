#pragma once
#include "Source.h"
class Node 
{
public:

	double data;
	Node* next;
};


void deleteNode(Node** node)
{
	Node* nextNode = *node;
	while ((*node)->next != NULL)
	{
		nextNode = (*node)->next;
		delete* node;
		*node = nextNode;
	}
	delete nextNode;
}

Node* SortedMerge(Node* a, Node* b)
{
	Node* result = NULL;
	Node* temp = NULL;
	Node* next = NULL;
	while (a != NULL || b != NULL)
	{
		/* Base cases */
		if (b == NULL)
		{
			next = a;
			a = a->next;
		}
		else
			if (a == NULL)
			{
				next = b;
				b = b->next;
			}
			else
				if (a->data <= b->data)
				{
					next = a;
					a = a->next;
				}
				else
				{
					next = b;
					b = b->next;
				}
		if (!result) {
			result = next;
		}
		else {
			temp->next = next;
		}
		temp = next; //////////?????????
	}
	return (result);

}

void FrontBackSplit(Node* source, Node** frontRef, Node** backRef)
{
	Node* fast;
	Node* slow;
	slow = source;
	fast = source->next;

	/* Advance 'fast' two nodes, and advance 'slow' one node */
	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	/* 'slow' is before the midpoint in the list, so split it in two
	at that point. */
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

void push(Node** head_ref, double new_data)
{
	/* allocate node */
	Node* new_node = new Node();

	/* put in the data */
	new_node->data = new_data;

	/* link the old list off the new node */
	new_node->next = (*head_ref);

	/* move the head to point to the new node */
	(*head_ref) = new_node;
}

void createChunks(Node** node, fstream& fin)
{
	double g;
	for (int i = 0; i < M; i++)
	{
		fin >> g;
		push(node, g);
	}
}bool makeDir()
{
	const char dir[] = "temp1";
	error_code ec;
	if (is_directory("temp1"))
		return is_directory(status(dir));
	else
		return create_directories(dir, ec);
}

void MergeSort(Node** headRef) {
	Node* head = *headRef;
	Node* a;
	Node* b;

	/* Base case -- length 0 or 1 */
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}

	/* Split head into 'a' and 'b' sublists */
	FrontBackSplit(head, &a, &b);

	/* Recursively sort the sublists */
	MergeSort(&a);
	MergeSort(&b);

	/* answer = merge the two sorted lists together */
	*headRef = SortedMerge(a, b);
}

void printListToFile(Node* node, int i)
{
	string s = "temp1\\" + to_string(i);
	fstream fout(s.c_str(), fstream::out);
	while (node != NULL)
	{
		fout << node->data << " ";
		node = node->next;
	}
}

void printList(Node* node)
{
	while (node != NULL) {
		cout << node->data << " ";
		node = node->next;
	}
}