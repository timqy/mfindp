#ifndef THREADING_H
#define THREADING_H

#include "getoption.h"
void *worker(void *arg);
void setWaiting(bool waiting);
int getWaiting();

void isDone();
bool getIsNotDone();

#endif
