/*
* dirtravers.c
*
* Traverses directories.
*/
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "dirtravers.h"
#include "getoption.h"
#include "worklist.h"


/** searches the directory for files with names
 * matching the given name and adds every directory
 * to the work pool
 */
void searchForName(char * path,struct Flags * options){
    DIR * dir;
    struct dirent * entry;
    struct stat statbuf;

    if((dir = opendir(path)) == NULL){
        fprintf(stderr, "Cannot read dir "); 
        perror (path);
        return;
    }
    
    /** while the directory contains files */
    while((entry = readdir(dir)) != NULL){
        char * adress = mergePath(path,entry->d_name);
        if(lstat(adress, &statbuf) == -1){
            fprintf(stderr,"could not lstat ");
            perror(adress);
            free(adress);
            exit (-1);
        } else if(S_ISDIR(statbuf.st_mode)){
            /** if the link is a directory */
            /** we do not want to go upwards in dirtree */
            if(strcmp(".",entry->d_name) == 0 ||
                    strcmp("..",entry->d_name) == 0){
                free(adress);
                continue;
            }

            /** if the directory name matches searchname */
            if(options->dflag && strstr(entry->d_name,options->searchName) != NULL){
                printf("%s\n", adress);
            }              
             
            /** add the directory adress to the work pool */
            add_work(adress);
        } else { 
            /**if not a directory*/
            if(strcmp(entry->d_name,options->searchName) == 0){
                if(options->fflag && S_ISREG(statbuf.st_mode)){
                    printf("%s\n", adress);
                } else if (options->lflag && S_ISLNK(statbuf.st_mode)){
                    printf("%s\n", adress);
                }
            }
            free(adress);
        }
    }
    closedir(dir);
}

/** 
 * merge the path with the name of the link 
 */
char* mergePath(char * path, char * name){
    char * adress = malloc(sizeof(char)*PATH_MAX);
    strcpy(adress, path);
    
    if(path[strlen(path)-1] != '/')
        strcat(adress, "/");

    strcat(adress, name);
    return adress;
}
