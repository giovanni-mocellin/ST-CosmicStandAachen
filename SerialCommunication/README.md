Description of the DAQ code:

DataAcquisition.cpp is the main file that defines the algorithm for the DAQ.
rs232.c & rs232.h are libraries to make the connection to the Arduinos via serial ports easier.

Description of DataAcquisition.cpp:
This program is used for running the DAQ of the Streamer Tubes of the Cosmic Stand Aachen
The DAQ is performed by 8 Arduinos, each reading out half of a layer, plus an Arduino giving the sync signal to the other 8 to syncrhonize them before starting the data taking
The DAQ is following these steps:
- Opening all the 9 ports
- Start a loop that takes the data in chunks, each 2 minutes long
- The chunk data files are created and named Run#_chunk#_ROA#_Year_Month_Day.dat (ROA = Read Out Arduino). We have one file per Arduino
- The stimulus to the Arduino Sync Board is sent via serial and it sends the sync signals the 8 ROA
- For 2 minutes the data is collected from the Arduinos' buffers and written to the files
- The output chunk files are closed and the loop start again
- After a certain number of chunks, the loop is over and the ports can be closed
