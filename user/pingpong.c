#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int to_child[2];
    int to_parent[2];


    pipe(to_child);
    pipe(to_parent);


   int ret = fork();

   if(ret == 0){
    // child
    char readed;
    int n = read(to_child[0], &readed,  1); // [0] is read end of pipe, &readed is buffer, 1 is size of buffer , read returns number of bytes read
    if(n == 1){
        printf("%d: received ping\n", getpid());
    }

    write(to_parent[1], "k",  1);

   }

      if(ret > 0){
    // parent
    
    write(to_child[1], "h",  1); //[1] is write end of pipe, "h" is buffer, 1 is size of buffer

    char readed;
    int n = read(to_parent[0], &readed, 1);

    
    if(n == 1){
        printf("%d: received pong\n", getpid());
    }
   }

    if(ret < 0){
        fprintf(2, "Fork error");
        exit(1);
    }


   exit(0);
}
