#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"


char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}



char*
newPath(char *newPath, const char *addedPath, const char *oldPath)//inspired by strcpy
{
    // what should it do
    // strcpy(buff, path);
    // strcpy(buff + strlen(buff), "/");
    // strcpy(buff + strlen(buff), de.name);
    printf("---------------\n");

    char *wholePath;
    wholePath = newPath; // address to whole string

    while((*newPath++ = *oldPath++) != 0) // zapisovanie oldPath do newPath (čisto copy), spolu s \0
    ;

    printf("%s\n", wholePath);
  
    newPath = newPath + strlen(newPath) -1; // ponter ukaže na koniec stringu, bez \0,  !!!!!! ???????  !!!!!!
    *newPath++ = '/'; // zapiše sa / a posunie sa pointer o 1 dalej
    printf("%s\n", wholePath);

    while((*newPath++ = *addedPath++) != 0) // zapisovanie celeho addedPath do newPath, spolu s \0
    ;

    printf("%s\n", wholePath);
    printf("---------------\n");
    // newPath = wholePath;
    return wholePath;
}

int
find(char *path, char*name){
    struct stat st;
    char buff[512];
    // char *p;
    struct dirent de;



    int fd = open(path, O_RDONLY);
    if(fd <0){
        fprintf(2, "File to open file: %s", path);
        return 1;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return 1;
    }

    // printf("fmtname(path): %s\n st.type: %d\n st.ino: %d\n st.size: %l\n", fmtname(path), st.type, st.ino, st.size);
    switch (st.type)
    {
    case T_FILE:
        if(strcmp(fmtname(path), name) == 0){ // 0 == is equal
            printf("%s\n", path);
        }
        break;

    case T_DIR:

//         ushort inum;
//   char name[DIRSIZ];



        // int fd = open(path, O_RDONLY);
        // find(path /fmtname(path), name)
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) continue; // de.name == . || de.name == ..

            // printf("FD: %d\n de-inum:%d de-name:%s\n", fd, de.inum, de.name);
            

            // if(de.name == name);
            // printf("kokot: %s, %d\n", fmtname(de.name), strlen(fmtname(de.name)));
            // printf("piča: %s, %d\n", name, strlen(name));



            // if(strcmp(fmtname(de.name), name) >= 0){
            //     printf("path: %s\n", path);
            // }


            // printf("buffer: %d, str:%s\n", buff, buff);


            strcpy(buff, path);
            strcpy(buff + strlen(buff), "/");
            strcpy(buff + strlen(buff), de.name);


            if(strcmp(fmtname(de.name), name) == 0){
                printf("path: %s\n", buff);
            }
            
            // newPath(buff, de.name, path);


            // printf("newbuffer: %d, str:%s\n", buff, buff);
            find(buff, name);

        }
        break;
    }


    return 0;

}

int
main(int argc, char *argv[])
{
    find(argv[1], argv[2]);
    return 0; 
}
