#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include "rs232.h"

using namespace std;

int main(int cport_nr, unsigned long long int nmaxtrig) //cport_nr = ROA#-1 , nmaxtrig = number of triggers to be registered (1M)
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
  
  unsigned long long int trig = 0;
  
  time_t now = time(0);
  tm *ltm = localtime(&now);
  
  string outname = "ROA" + to_string(cport_nr+1) + "_" + to_string(1900 + ltm->tm_year) + "_" + to_string(ltm->tm_mon) + "_" + to_string(ltm->tm_mday) + "_" + to_string(ltm->tm_hour) + "_" + to_string(ltm->tm_min) + "_" + to_string(ltm->tm_sec) + ".dat";
  
  ofstream outfile;
  outfile.open(outname);
  
  while (trig < nmaxtrig)
  {
    n = RS232_PollComport(cport_nr, buf, 4095);
    
    if (n > 0)
    {
      printf("received %i bytes: %s\n", n, (char *)buf);
      outfile << buf;
      trig++;
    }
  }
  
  outfile.close();
  
  return(0);
}
