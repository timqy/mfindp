
/*
* getoption.c 
* 
* sorts the flags from the arguments.
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#include "getoption.h"

struct Flags * getOptions(int argc, char * argv[]){
    struct Flags * retVal = (struct Flags *)malloc (sizeof(struct Flags));
    retVal->dflag = false;
    retVal->fflag = false;
    retVal->lflag = false;
    retVal->nrthr = 0;

    int c;
    while ((c = getopt(argc,argv,"t:p:")) != -1){
        switch(c){
            case 't':
                switch(*optarg){
                    case 'd':
                        retVal->dflag = true;
                    break;
                    case 'f':
                        retVal->fflag = true;
                    break;
                    case 'l':
                        retVal->lflag = true;
                    break;
                    default:
                    fprintf(stderr,"Error unknown argument for t");
                    fprintf(stderr,"-t [ d | f | l ]");
                    exit(-1);
                }
            break;
            case 'p':
                retVal->nrthr = atoi(optarg);
                if(retVal->nrthr <= 0){
                    fprintf(stderr,"-p must contain an integer");
                    exit(-1);
                }
                break;
            case '?':
                if(optopt == 't'){
                    fprintf(stderr,"option %c needs an argument\n", optopt);
                    exit(-1);
                } else if (isprint(optopt)){
                    fprintf(stderr,"unknown option for %c\n",optopt);
                    exit(-1);
                }
            break;
        }   
    }
    
    if(!retVal->dflag && !retVal->fflag && !retVal->lflag){
    retVal->dflag = true;
    retVal->fflag = true;
    retVal->lflag = true;
    }

    if(retVal->nrthr <= 0)
        retVal->nrthr = 1;

return retVal;
}

