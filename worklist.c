/**
 * Linkedlist.c
 * Date : 2015-09-07
 * 
 * A linkedlist with simple functions:
 * createNode - creates a new entry in the list
 * printlist - prints the list
 * sortList -sorts the list using bubblesort
 * freeList - frees allocated memory in the list.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "worklist.h"
#include "getoption.h"

static struct node * root;
pthread_mutex_t listlock = PTHREAD_MUTEX_INITIALIZER;

/**
 * creates a new node with data and inserts it at the root.
 */
char * get_work(void){
    pthread_mutex_lock(&listlock);
	char * dirr = NULL;
    if(root != NULL){
            if(root->next != NULL){
                dirr = root->directory;
                struct node * tempNode = root;
                root = root->next;
                free(tempNode);
                tempNode = NULL;
            } else {
                dirr = root->directory;
                free(root);
                root = NULL;
            }
    }
    pthread_mutex_unlock(&listlock);
    return dirr;
}


/** 
 * adds work to the work pool
 * ( a path to an directory )
 */
void add_work(char * directory){
    if(directory == NULL || strlen(directory) == 0)
        return;

    pthread_mutex_lock(&listlock);
    if(root == NULL){
        root = (struct node *) malloc(sizeof(struct node));
	    root->directory = directory;
	    root->next = NULL;
    } else {
	    struct node * tempNode;
	    tempNode = (struct node *) malloc(sizeof(struct node));
	    tempNode->next = root;
	    tempNode->directory = directory;
	    root = tempNode;
    }
    pthread_mutex_unlock(&listlock);
}

/** 
 * if the queue contains work to be done 
 */
bool work_queue_empty(){
    pthread_mutex_lock(&listlock);
    if(root == NULL){
        pthread_mutex_unlock(&listlock);
        return true;
    }
    pthread_mutex_unlock(&listlock);
    return false;
}

/**
 * goes through the list to free allocated memory.
 */
void freeList(){
	if(root != NULL){
	
	struct node * linkedList;
	struct node * tempNode;

	linkedList = root;
	while(linkedList->next != NULL){
		tempNode = linkedList->next;
		free(linkedList->directory);
		free(linkedList);
		linkedList = tempNode;
	}
	free(linkedList->directory);
	free(linkedList);

	}
}
		
