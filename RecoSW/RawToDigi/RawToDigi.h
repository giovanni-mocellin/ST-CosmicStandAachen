#include "../DataStructures/DataStructures.h"
#include "../Libraries/IncludeLibraries.h"

// Input files related variables
int run_num;
unsigned long int evt = 0, evnum = 0;

// Input file
string infileName;
TFile * infile;
TBranch * ROA1b = 0;
TBranch * ROA2b = 0;
TBranch * ROA3b = 0;
TBranch * ROA4b = 0;
TBranch * ROA5b = 0;
TBranch * ROA6b = 0;
TBranch * ROA7b = 0;
TBranch * ROA8b = 0;
vector<unsigned int> *ROA[8] = {0,0,0,0,0,0,0,0};

// Output file + tree with branches declaration
vector<digi> *digiLay[4];
TFile * outfile;
TTree * digiTree = new TTree;
TBranch * runb = digiTree->Branch("runb",&run_num,"run/I");
TBranch * evtb = digiTree->Branch("evtb",&evt,"evt/i");
TBranch * digiL1b = digiTree->Branch("digiL1",&digiLay[0]);
TBranch * digiL2b = digiTree->Branch("digiL2",&digiLay[1]);
TBranch * digiL3b = digiTree->Branch("digiL3",&digiLay[2]);
TBranch * digiL4b = digiTree->Branch("digiL4",&digiLay[3]);

// create some histograms for occupancy plots!!!

// Intermediate variables (fill these vectors with mapped raw)
vector<unsigned int> *wire[4] = {0,0,0,0};
vector<unsigned int> *strip[4] = {0,0,0,0};
vector<unsigned int> *dstrip[4] = {0,0,0,0};

// Functions
void clusterize(vector<unsigned int>, vector<unsigned int>); // create a new cluster if the hole is 1 strip at least (discontinuity)
void createDigis(vector<unsigned int>, vector<unsigned int>, vector<unsigned int>, vector<digi>); // creates all the combinations of hits - all the wires, with all the strips, with all the dstrips
