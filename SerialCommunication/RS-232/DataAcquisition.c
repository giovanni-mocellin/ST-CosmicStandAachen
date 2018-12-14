#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "rs232.h"

using namespace std;

int main(int cport_nr)
{
  int i, n;
  int baud = 2000000;
  
  unsigned char buf[4096];
  
  char mode[]={'8','N','1',0};
  
  if(RS232_OpenComport(cport_nr, baud, mode))
  {
    printf("Can not open comport\n");
    return(0);
  }
  
  ofstream outfile;
  outfile.open ("example.txt");
  
  while (1)
  {
    n = RS232_PollComport(cport_nr, buf, 4095);
    
    if (n > 0)
    {
      printf("received %i bytes: %s\n", n, (char *)buf);
    }
  }
  
  outfile.close();
  
  return(0);
}


