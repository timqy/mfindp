/*
* Main.c 
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <string.h>
#include "dirtravers.h"
#include "getoption.h"
#include "threading.h"
#include "worklist.h"

void doWork(struct Flags * options);

int main(int argc, char *argv[]){
    if(argc < 3){
           fprintf(stderr,"Wrong input, should be:");
           fprintf(stderr,"mfind flags folder name\n");
           exit(-1);
    }
  
    /** get the needed variables */ 
    struct Flags *options = getOptions(argc,argv);
    options->searchName = strdup(argv[argc-1]);
    pthread_t thread[options->nrthr];

    /** create as many nrthr as stated */
    for(int i = 0; i < options->nrthr - 1;i++){
        if(pthread_create(&thread[i],NULL,worker,options) != 0){
            options->nrthr = i;
            fprintf(stderr,"Maximum number of threads reached : %d",options->nrthr);
        }
        setWaiting(true);
    }


    /** search for files in each path given */
    for ( int index = optind; index < argc-1 ; index++){
        if(argv[index][strlen(argv[index])-1] != '/') {
            add_work(strdup(strcat(argv[index],"/")));
        }else{
            add_work(strdup(argv[index]));    
        }
    }
 
    setWaiting(true);  
    doWork(options);
    isDone();   

    /** wait for all nrthr to finish */
    void * status;
    for(int i = 0; i < options->nrthr -1 ;i++){
        pthread_join(thread[i],&status);
        fprintf(stdout,"[%d]Thread : %lu  | Search count : %d\n",i+1,thread[i], *(int*)status);
        free(status);
    }

    free(options);
    return 0;
}

/** Main nrthr work function
 */
void doWork(struct Flags *options){
    bool isDone = false;
    int searchCount = 0;
    while(!isDone){
        while(!work_queue_empty()){
            setWaiting(false); 
            char * path = get_work();
            if(path != NULL){
                searchForName(path,options);
                free(path);
                searchCount++;
            }
            setWaiting(true);
        }
        /** if all nrthr are waiting everything is done */
        if(getWaiting() == options->nrthr)
            isDone = true;
    }
    fprintf(stdout,"\n[0]Main Search Count : %d\n",searchCount);
}
