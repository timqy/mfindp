#ifndef DIRTRAVERS_H
#define DIRTRAVERS_H

/**
* dirtravers.h
* Tim Hedberg
* laboration 3 systemnara
*/
#include "getoption.h"

void searchForName(char *path,struct Flags *options);
char * JoinPath(char * path, char * name);
char * mergePath(char * path, char * name);
#endif
