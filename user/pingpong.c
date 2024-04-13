#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  fork();
  if(getpid() == 3)
  {
    close(p[0]);
    write(p[1],"1",sizeof(char));
    close(p[1]);
    exit(0);
  }
  if(getpid() == 4)
  {
    close(p[1]);
    char buf[1];
    read(p[0],buf,sizeof(char));
    if(buf[0] == '1')
    {
      printf("%d:recieve ping\n",getpid());
    }
    close(p[0]);
  }

  exit(0);
}
