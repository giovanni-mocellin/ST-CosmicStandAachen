# Description of the DAQ code:
This program is used for running the DAQ of the Streamer Tubes of the Cosmic Stand Aachen.
The DAQ is performed by 8 Arduinos (ROA = Read Out Arduino), each reading out half of a layer. In addition, one Arduino sends a signal to the other 8 to syncrhonize them before starting the data taking.
- "DataAcquisition" is the main file that defines the algorithm for the DAQ.
- "rs232.c" are libraries to make the connection to the Arduinos via serial ports easier.

## Description of DataAcquisition.cpp:
The DAQ is following these steps:
- It is called with 2 main arguments: the RUN_NUMBER, which is THE KEY parameter and the number of minutes. Since the chunk files last for 2 minutes, it is supposed to be an even number. If it is odd, then the number of chunks is one less than expected...
- Opening all the 9 ports (ASB + 8 ROAs)
- Start a loop that takes the data in chunks, each 2 minutes long (first chunk is from when you launch it until the second = 0 of the + 2 minutes. e.g.: if it starts at 08:51:52, the chunk 0 lasts until 08:53:00, so 1:08 and not 2:00)
- The chunk data files are created in the folder '../../ST_Run#/' and named 'Run#_chunk#_ROA#.dat'
- The stimulus to the Arduino Sync Board is sent via serial and it sends the sync signals the 8 ROA
- For 2 minutes the data is collected from the Arduinos' buffers and written to the files
- The output chunk files are closed and the loop start again
- After a certain (even) number of minutes, defined by the user when launching the DAQ, the loop is over and the ports can be closed
- To keep track of the exact time when each chunk is created, a log file is created. There the chunk number is followed by the date and time
