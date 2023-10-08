#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"



#define MAX_SIZE_OF_FILE 256



int main(int argc, char *argv[]){
    if (!(argc == 2 || argc == 3)){
        fprintf(2, "Invalid usage!\nUsage: create_file <file>\nUsage: create_file <file> <text>\n");
        exit(1);
    }

    int fd = open(argv[1], O_RDWR | O_CREATE);
    if(fd<0){
        fprintf(2, "Cannot create file: %s\n", argv[1]);
        exit(1);
    }
    
    else if (argc == 3){
        if(strlen(argv[2])> MAX_SIZE_OF_FILE ){
            fprintf(2, "File is bigger than allowed! Size of file:%s", strlen(argv[2]));
            close(fd);
            exit(1);
        }
        else if((write(fd, argv[2], strlen(argv[2]))) < 0){
            fprintf(2, "Cannot write to file: %s\n", argv[1]);
            close(fd);
            exit(1);
        }
        
        printf("File was created: %s, and string in file: %s\n", argv[1], argv[2]);
        close(fd);
        exit(0);
    }

    else{
        printf("File was created: %s\n", argv[1]);
        close(fd);
        exit(0);
    }

}