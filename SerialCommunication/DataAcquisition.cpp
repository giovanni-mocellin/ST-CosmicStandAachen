// This program is used for running the DAQ of the Streamer Tubes of the Cosmic Stand Aachen
// The DAQ is performed by 8 Arduinos, each reading out half of a layer, plus an Arduino giving the sync signal to the other 8 to syncrhonize them before starting the data taking
// The DAQ is following these steps:
//  - Opening all the 9 ports
//  - Start a loop that takes the data in chunks, each 2 minutes long
//  - The chunk data files are created and named Run#_chunk#_ROA#_Year_Month_Day.dat (ROA = Read Out Arduino). We have one file per Arduino
//  - The stimulus to the Arduino Sync Board is sent via serial and it sends the sync signals the 8 ROA
//  - For 2 minutes the data is collected from the Arduinos' buffers and written to the files
//  - The output chunk files are closed and the loop start again
//  - After a certain number of chunks, the loop is over and the ports can be closed

#include "DataAcquisition.h"

int main(int argc, char** argv) // called with argv[0] = run_# , argv[1] = #_of_minutes_to_run
{
  time_t now;
  tm *ltm;
  int t_start, t_stop;
  
  int run_num = atoi(argv[1]);
  int nFiles = atoi(argv[2])/2; // #min/2 if each lasts for ~2 min...
  
  now = time(0);
  ltm = localtime(&now);
  string logname = "Log_Run" + to_string(run_num) + "_" + to_string(1900 + ltm->tm_year) + "_" + to_string(ltm->tm_mon+1) + "_" + to_string(ltm->tm_mday) + ".txt";
    
  outfile[0].open(logname);
  
  openAllPorts();
  
  for (int chunk = 0 ; chunk < nFiles ; chunk++)
  {
    openOutputDataFiles(run_num,chunk,ltm);
    
    logstring = "Run " + to_string(run_num) + " chunk " + to_string(chunk) + ", Date&Time: " + to_string(ltm->tm_mday) + "_" + to_string(ltm->tm_mon+1) + "_" + to_string(1900 + ltm->tm_year) + " " + to_string(ltm->tm_hour) + "_" + to_string(ltm->tm_min) + "_" + to_string(ltm->tm_sec) + "\n";
    
    cout << logstring;
    
    outfile[0] << logstring;
    
    SYNCon();
    
    now = time(0);
    t_start = localtime(&now)->tm_min;
    t_stop = localtime(&now)->tm_min;
    
    while ( ( t_stop - t_start != 2 ) && ( t_stop - t_start + 60 != 2 ) ) // stops after ~2 minutes
    {
      for (int cport_nr = 1 ; cport_nr <= 8 ; cport_nr++)
      {
        n = RS232_PollComport(cport_nr, buf, 4095);
        if (n > 0) outfile[cport_nr] << buf;
        outfile[cport_nr] << "buf \n";
      }
      now = time(0);
      t_stop = localtime(&now)->tm_min;
    }
    
    closeOutputDataFiles();
  }
  
  closeAllPorts();
  
  outfile[0].close();
  
  return(0);
}

// Open and close serial ports

void openAllPorts()
{
  for (int cport_nr = 0 ; cport_nr <= 8 ; cport_nr++)
  {
    RS232_OpenComport(cport_nr, baud, mode);
  }
  sleep(2); // sleep for 2 sec to wait for the ports to opened correctly
}

void closeAllPorts()
{
  for (int cport_nr = 0 ; cport_nr <= 8 ; cport_nr++)
  {
    RS232_CloseComport(cport_nr);
  }
  sleep(2); // sleep for 2 sec to wait for the ports to opened correctly
}

// Send sync message to the ASB (Arduino Sync Board)

void SYNCon()
{
  int cport_nr = 0;
  char SyncChar = 'S';
  
  RS232_SendByte(cport_nr,(char)SyncChar);
}

// Open and close output files

void openOutputDataFiles(int run, int part, tm *ltm)
{
  string outname;
  
  for (int cport_nr = 1 ; cport_nr <= 8 ; cport_nr++)
  {
    outname = "Run" + to_string(run) + "_chunk" + to_string(part) + "_ROA" + to_string(cport_nr) + "_" + to_string(1900 + ltm->tm_year) + "_" + to_string(ltm->tm_mon+1) + "_" + to_string(ltm->tm_mday) + ".dat";
    
    outfile[cport_nr].open(outname);
    //outfile[cport_nr] << "ROA" << cport_nr << " file opened.";
  }
  sleep(1); // sleep for 1 sec to wait for the files to opened correctly
}

void closeOutputDataFiles()
{
  for (int cport_nr = 1 ; cport_nr <= 8 ; cport_nr++)
  {
    outfile[cport_nr].close();
  }
  sleep(1); // sleep for 1 sec to wait for the files to closed correctly
}
