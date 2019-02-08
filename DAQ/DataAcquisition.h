#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include "rs232.h"

using namespace std;

ofstream outfile[9];
string logstring;
int i, n;

int baud = 230400; // Highest supported by Mac
// int baud = 2000000; // change also rs232.c file including the commented out baud (not supported by Mac)
char mode[]={'8','N','1',0};
unsigned char buf[4096];

void openAllPorts();
void openOutputDataFiles(int, int, tm *);
void SYNCon();
void closeOutputDataFiles();
void closeAllPorts();
