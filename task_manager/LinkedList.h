#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>

class LinkedList {	

public:
	NODE *front, *back;
	LinkedList();
	~LinkedList();
	void appendNodeFront(Task);
	void appendNodeBack(Task);
	void displayNodes();
	void destroyList();
};

#endif