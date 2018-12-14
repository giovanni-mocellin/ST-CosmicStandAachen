# ST-CosmicStandAachen
All the needed code to run the Streamer Tubes of the CosmicStandAachen, from the Arduino DAQ FW to the muon track reconstruction and analysis SW

## Get repo
git clone https://github.com/giovanni-mocellin/ST-CosmicStandAachen.git

## Data acquisiton from Arduino boards
The software can be found in the folder "SerialCommunication/RS-232/"

### To compile the code
```
g++ DataAcquisition.c rs232.c -Wall -Wextra -o2 -o arduinoDAQ
```

### To run a data acquisition
```
pyhton DAQarduinoON.py <time for each chunk> <number of chuncks>
```
