#include "DataStructures.h"
#include "KascadeChannelMap.h"
#include <Riostream.h>
#include <iomanip>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "TH1.h"
#include "TH2D.h"
#include "TH2.h"
#include "TH3F.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TLatex.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include "TGraphErrors.h"

bool debug = false;

using namespace std;

void ReadBinGenerateRawData(string infile)
{
    ifstream in;
    in.open(infile, ios::in|ios::binary);
    
    string outfile = infile.substr(0, infile.size()-4) + "_toRaw.txt";
    ofstream out;
    out.open("");
    
    unsigned string indata = 0;
    unsigned short = 
    unsigned int time;
    
    while (!in.eof())
    {
        in >> SyncHeader; } while (SyncHeader != "Sync of all the Read-Out Arduinos") }
        firstSync = true;
        
        in >> ()(indata)
        cout << (short)(indata) << endl;
        
    }
    
    in.close();
    out.close();
}

