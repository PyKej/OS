#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int
write_string_to_file(const char *file, const void *charmessage) {
  int fd = open(file, O_CREATE | O_WRONLY);

  

  if(fd < 0){
     fprintf(2, "failed to open %s\n", file);
     exit(1);
  }

  // I want to add newline to the end of the message but it doesn't work

  // if((*(charmessage + strlen(charmessage) - 1) ) != '\n'){
  //   charmessage = strcat(charmessage, "\n");
  // }


  int n = write(fd, charmessage, strlen(charmessage));

  if(n == -1){
    fprintf(2, "failed to write to  %s\n", file);
    exit(1);
  }



  exit(0);
}

int
main(int argc, char *argv[])
{

  if(argc != 4) {
    fprintf(2, "Invalid usage! Usage: fpwriter <file1> <file2> <message>");
    exit(1);
  }


  int pid = fork(); // VHODNE UPRAVTE

  if(pid > 0){
     // parent
    write_string_to_file(argv[1], argv[3]);

   } else if(pid == 0){
     // child
     write_string_to_file(argv[2], argv[3]);
   } else {
     fprintf(1, "fork failed\n");
   }
  exit(0);
}