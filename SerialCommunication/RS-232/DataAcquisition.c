#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "rs232.h"

using namespace std;

int main(int cport_nr)
{
  int i, n;
  int bdrate=2000000;       /* 2000000 baud */

  unsigned char buf[4096];

  char mode[]={'8','N','1',0};
  
  if(RS232_OpenComport(cport_nr, bdrate, mode))
  {
    printf("Can not open comport\n");
    return(0);
  }

  while(1)
  {
    n = RS232_PollComport(cport_nr, buf, 4095);

    if(n > 0)
    {
      buf[n] = 0;   /* always put a "null" at the end of a string! */

      for(i=0; i < n; i++)
      {
        if(buf[i] < 32)  /* replace unreadable control-codes by dots */
        {
          buf[i] = '.';
        }
      }

      printf("received %i bytes: %s\n", n, (char *)buf);
    }
  }

  return(0);
}

