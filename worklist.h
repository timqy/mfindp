#ifndef WORKLIST_H
#define WORKLIST_H

/** for bool */
#include "getoption.h"

struct node {
	char* directory;
	struct node *next;

};

char * get_work();
void add_work(char * directory);
bool work_queue_empty();
void freeList();

#endif
