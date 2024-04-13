#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"


int
main(int argc, char *argv[])
{
  char buf[32];
  read(0,&buf,sizeof(buf));
  printf("%s%d",buf,strlen(buf));
  
  exit(0);
}