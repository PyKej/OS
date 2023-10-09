#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"



#define MAX_SIZE_OF_FILE 256


// compare 2 string
int compareStr(char file1[MAX_SIZE_OF_FILE], char file2[MAX_SIZE_OF_FILE]){
    while(1){
        if(*file1 != *file2){
            return 0;
        }
        if(*file1 == '\0' || *file2 == '\0'){ // if file end
            break;
        }
        file1++;
        file2++;
    }
    return 1;
}


int main(int argc, char *argv[]){
    if (argc != 3){
        fprintf(2, "Invalid usage! Usage: compare <file1> <file2>\n");
        exit(1);
    }

    int to_parent[2];
    pipe(to_parent);

    int pid = fork();

    if(pid > 0){
        //parent
        char file1[MAX_SIZE_OF_FILE];
        char file2[MAX_SIZE_OF_FILE];

        int fd = open(argv[1], O_RDONLY);
        if(fd<0){
            fprintf(2, "Cannot open file: %s\n", argv[1]);
            exit(1);
        }


        if(read(fd, file1, MAX_SIZE_OF_FILE) < 0){
            fprintf(2, "Read failed! File: %s\n", argv[1]);
            exit(1);
        }

        if(read(to_parent[0], file2, MAX_SIZE_OF_FILE) < 0){
            fprintf(2, "Read failed! File: %s\n", argv[2]);
            exit(1);
        }

        int result = compareStr(file1, file2);

        if(result == 1){
            printf("OK\n");
        }
        else{
            printf("FALSE\n");
        }
    }
    else if(pid == 0){
        //child

        int fd = open(argv[2], O_RDONLY);
        if(fd<0){
            fprintf(2, "Cannot open file: %s\n", argv[2]);
            exit(1);
        }

        char buffer[MAX_SIZE_OF_FILE];

        if( read(fd, buffer, MAX_SIZE_OF_FILE) < 0){
            fprintf(2, "Read failed! File: %s\n", argv[2]);
            exit(1);
        }

 
        if(write(to_parent[1], buffer, MAX_SIZE_OF_FILE) < 0){
            fprintf(2, "Write error\n");
            exit(1);
        }
    }
    else{
        fprintf(2, "Fork crashed!\n");
        exit(1);
    }
    

    exit(0);
}