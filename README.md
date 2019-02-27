# ST-CosmicStandAachen
All the needed code to run the Streamer Tubes of the CosmicStandAachen, from the Arduino DAQ FW to the muon track reconstruction and analysis SW.

## Get repository
git clone https://github.com/giovanni-mocellin/ST-CosmicStandAachen.git

## Data acquisiton from Arduino boards
The software can be found in the folder "SerialCommunication/"

### To compile the code
```
cd SerialCommunication
./compile.sh
```

### To take a data acquisition run
```
./DAQforST <run_number> <number_of_minutes_of_DAQ>
```
For each of the ROAs, the file size should amount to 120MB per hour of data taking. In total, with 8 connected ROAs, the size would be around 1GB/h.

## Reconstruction code
The software for the reconstruction can be found in the folder "RecoSW/"
The final part of the code, in which the recHits are fitted and the plots are drawn is based on ROOT; the plotting functions are already included and easy to manipulate.
Might think to save results in root file in a TTree structure with plots.
