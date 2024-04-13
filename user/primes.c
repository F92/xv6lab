#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

#define W 1
#define R 0


int first_data(int p[2],int* first)
{
  if(read(p[0],first,sizeof(int)) == sizeof(int))
  {
    printf("prime %d\n",*first);
    return 0;
  }
  return -1;
}

void transfo(int p[2],int m[2],int first)
{
  int data;
  while (read(p[R],&data,sizeof(int)) == sizeof(int))
  {
    if(data % first != 0)
    {
      write(m[W],&data,sizeof(int));
    }
  }
  close(p[R]);
  close(m[W]);
}

void prime(int p[2])
{
  close(p[W]);
  int first = 0;
  if(first_data(p,&first) == 0)
  {
    int m[2];
    pipe(m);
    transfo(p,m,first);

    if(fork() == 0)
    {
      prime(m);
    }
    else
    {
      close(p[R]);
      wait(0);
    }
  }
  exit(0);
}

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  for (int i = 2; i < 36; i++)
  {
    write(p[W],&i,sizeof(int));
  }

  if(fork() == 0)
  {
    prime(p);
  }
  else
  {
    close(p[R]);
    close(p[W]);
    wait(0);
  }

  exit(0);
}
