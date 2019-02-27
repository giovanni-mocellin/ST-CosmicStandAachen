#include "../DataStructures/DataStructures.h"
#include "../Libraries/IncludeLibraries.h"

// Input files related variables
int run_num;
unsigned long int evt = 0, evnum = 0, chunk = 0, chunknum = 0;
TFile * testFile;
string infileName;
fstream * infile[8];
unsigned int syncPosRoa[8] = {0,0,0,0,0,0,0,0};
unsigned int firstEvPosRoa[8] = {0,0,0,0,0,0,0,0};
unsigned int numEvRoa[8] = {0,0,0,0,0,0,0,0};

// Event with headers, data and trailer
char * roaFromFile;
unsigned short evtNumFromFile;
unsigned int datablock;
vector<unsigned int> *ROA[8];
char * checksum;

// Output file + tree with branches declaration
TFile * outfile;
TTree * dataTree = new TTree;
TBranch * runb = dataTree->Branch("runb",&run_num,"run/I");
TBranch * evtb = dataTree->Branch("evtb",&evt,"evt/i");
TBranch * ROA1b = dataTree->Branch("ROA1b","std::vector<unsigned int>",&ROA[0]);
TBranch * ROA2b = dataTree->Branch("ROA2b","std::vector<unsigned int>",&ROA[1]);
TBranch * ROA3b = dataTree->Branch("ROA3b","std::vector<unsigned int>",&ROA[2]);
TBranch * ROA4b = dataTree->Branch("ROA4b","std::vector<unsigned int>",&ROA[3]);
TBranch * ROA5b = dataTree->Branch("ROA5b","std::vector<unsigned int>",&ROA[4]);
TBranch * ROA6b = dataTree->Branch("ROA6b","std::vector<unsigned int>",&ROA[5]);
TBranch * ROA7b = dataTree->Branch("ROA7b","std::vector<unsigned int>",&ROA[6]);
TBranch * ROA8b = dataTree->Branch("ROA8b","std::vector<unsigned int>",&ROA[7]);

// Functions

unsigned int FindSyncMsg(fstream *);
unsigned int FindFirstEvent(fstream *, unsigned int, int);
unsigned long int FindEvNumber(fstream *, unsigned int);
unsigned int FindMinEvNum(unsigned int []);
unsigned int powerOfTwo(int);
