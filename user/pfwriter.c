#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int
write_string_to_file(const char file, charmessage) {
  int fd = -1; // VHODNE UPRAVTE

  if(fd < 0){
     fprintf(1, "failed to open %s\n", file);
     exit(1);
  }

  // TU DOPLŇTE KÓD

  exit(0);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc != 4) {
    fprintf(2, "Invalid usage! Usage: fpwriter <file1> <file2> <message>");
    exit(1);
  }

  inr pid = -1; // VHODNE UPRAVTE

  if(pid > 0){
     // TU DOPLŇTE KÓD
   } else if(pid == 0){
     // TU DOPLŇTE KÓD
   } else {
     fprintf(1, "fork failed\n");
   }
  exit(0);
}