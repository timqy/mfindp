#ifndef GETOPTION_H
#define GETOPTION_H

/*
* getoption.c 
* Tim Hedberg
* Laboration 3 systemnära 
*  
*/

typedef int bool;
#define true 1
#define false 0

struct Flags {
    bool dflag;
    bool fflag;
    bool lflag;
    int nrthr;
    char * searchName;
};

struct Flags * getOptions(int argc, char * argv[]);

#endif


