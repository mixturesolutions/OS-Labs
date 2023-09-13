//Purpose: replicates the behavior of the ls command
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h> 

//initiate prototypes
void print(char *dirName, int count);
int checkDir(char *loca);

int main(int arg, char **args){
    //take in arguments with no argument being current directory and others the entered directory
    if (arg == 1){
        struct dirent **name;
        int n;
        n = scandir(".",&name,NULL,alphasort);
        if (n == -1) {
            perror("Error");
            exit(EXIT_FAILURE);
        }
        while (n--){
            printf("%s\n",name[n]->d_name);
            free(name[n]);
        }
    } else {
        print(args[1], 0); //0 being the number of spaces before levels of directories
    }

}

//print out all directories and files using recursion
void print(char *dirName, int count){ 

    //copied from scandir function given from the lab
    struct dirent **name;
    int n = scandir(dirName, &name, NULL, alphasort);
    if (n == -1) {
        perror("Error");
        exit(1);
    }
    while (n--){
        //disregard files starting with '.' or '..'
        if (strcmp(name[n]->d_name, ".") != 0 && strcmp(name[n]->d_name, "..") != 0) {
            //count for spaces beforehand
            for (int i = 0; i < count; i ++){
                printf("  ");
            }
            printf("%s\n",name[n] -> d_name);

            //store the path locations with opening of each directory
            char loc[1000] = "";
            strcpy(loc, dirName);
            strcat(loc, "/");
            strcat(loc, name[n]->d_name);
            
            //if it is a directory, start recursion
            if (checkDir(loc) == 1){
                print(loc, ++count);
            }
            free(name[n]);

        } else {
            free(name[n]);
            n--;
        }    
    }
}
int checkDir(char *loca){
    //creates a directory stream that opens a supposed "directory"
    DIR* di = opendir(loca);
    //returns 1 if it is a directory, 0 if it is not a directory, error if it's error
    if (di != NULL){
        closedir(di);
        return 1;
    } else if (errno == ENOTDIR){
        return 0;
    } else {
        perror("Error"); //outputs the specific error and terminates
        exit(1);
    }
}


