#include "LinkedList.h"
using namespace std;

LinkedList::LinkedList() {
	front = back = NULL;
}

LinkedList::~LinkedList() {
	destroyList();
}

void LinkedList::appendNodeBack (Task data) {
	Node *newNode = new Node (data);
	if (back == NULL) {
		front = back = newNode;
	} else {
		back->next = newNode;
		newNode->prev = back;
		back  = newNode;
	}
}

void LinkedList::appendNodeFront (Task data) {
	Node *newNode = new Node (data);
	if (front == NULL) {
		front = back = newNode;
	} else {
		newNode->next = front;
		front->prev = newNode;
		front  = newNode;
	}
}

void LinkedList::displayNodes() {
	cout << "NODES:" << endl;

	Node *current = front;
	while (current != NULL) {
		cout << "TITLE :: " << current->data.title << " | DESCRIPTION :: " << current->data.description << endl;
		current = current->next;
	}


}

void LinkedList::destroyList() {
	cout << "DESTROYING LIST ... \n" << endl;

	Node *current = back;
	while (current != NULL) {
		current = current->prev;
		delete current->next;
	}

	front = back = NULL;
}