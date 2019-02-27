#include "RawToDigi.h"

int main (int argc, char** argv)
{
  run_num = atoi(argv[1]);
  
  string dataPath = "../../../ST_Run" + to_string(run_num) + "/";
  
  // Output file
  string outname = dataPath + "Run" + to_string(run_num) + "_digi.root";
  outfile = new TFile(outname.c_str(),"RECREATE");
  if ( outfile->IsOpen() ) cout << "outfile opened successfully" << endl;
  
  // Input file
  cout << "Opening file: Run " << run_num << "_raw.root" << endl;
  infileName = dataPath + "Run" + to_string(run_num) + "_raw.root";
  infile = new TFile(infileName.c_str());
  if ( infile->IsOpen() ) cout << "raw.root file opened successfully!" << endl;
  if ( !infile->IsOpen() )
  {
    cout << "raw.root file not found!" << endl;
    exit (EXIT_FAILURE);
  }
  
  // Input TTree and branches
  TTree *rawTree = (TTree*)infile->Get("dataTree");
  evnum = rawTree->GetEntries();
  rawTree->SetBranchAddress("ROA1b",&ROA[0],&ROA1b);
  rawTree->SetBranchAddress("ROA2b",&ROA[1],&ROA2b);
  rawTree->SetBranchAddress("ROA3b",&ROA[2],&ROA3b);
  rawTree->SetBranchAddress("ROA4b",&ROA[3],&ROA4b);
  rawTree->SetBranchAddress("ROA5b",&ROA[4],&ROA5b);
  rawTree->SetBranchAddress("ROA6b",&ROA[5],&ROA6b);
  rawTree->SetBranchAddress("ROA7b",&ROA[6],&ROA7b);
  rawTree->SetBranchAddress("ROA8b",&ROA[7],&ROA8b);
  
  // Loop for reading the events and storing them in the tree
  for (evt = 0 ; evt < evnum ; evt++)
  {
    if (evt % 250 == 0) cout << "RawToDigi processing: run " << run_num << ", evt " << evt << endl;
    
    unsigned long int tentry = rawTree->LoadTree(evt);
    ROA1b->GetEntry(tentry);
    ROA2b->GetEntry(tentry);
    ROA3b->GetEntry(tentry);
    ROA4b->GetEntry(tentry);
    ROA5b->GetEntry(tentry);
    ROA6b->GetEntry(tentry);
    ROA7b->GetEntry(tentry);
    ROA8b->GetEntry(tentry);
    
    for (int ardnum = 0 ; ardnum < 8 ; ardnum++)
    {
      for (unsigned int j = 0; j < ROA[ardnum]->size(); j++)
      {
        // Mapping of read out channels to detector physical channels
        if (ardnum == 0 && ROA[ardnum]->at(j) < 96) strip[0]->push_back(ROA[ardnum]->at(j) + 97);
        if (ardnum == 0 && ROA[ardnum]->at(j) >= 96) wire[0]->push_back(ROA[ardnum]->at(j) - 95);
        if (ardnum == 1 && ROA[ardnum]->at(j) < 96) dstrip[0]->push_back(ROA[ardnum]->at(j) + 1);
        if (ardnum == 1 && ROA[ardnum]->at(j) >= 96) strip[0]->push_back(ROA[ardnum]->at(j) - 95);
        if (ardnum > 1 && ardnum%2==0 && ROA[ardnum]->at(j) < 96) wire[int(ardnum/2)]->push_back(ROA[ardnum]->at(j) + 1);
        if (ardnum > 1 && ardnum%2==0 && ROA[ardnum]->at(j) >= 96) strip[int(ardnum/2)]->push_back(ROA[ardnum]->at(j) - 95);
        if (ardnum > 1 && ardnum%2==1 && ROA[ardnum]->at(j) < 96) strip[int(ardnum/2)]->push_back(ROA[ardnum]->at(j) + 97);
        if (ardnum > 1 && ardnum%2==1 && ROA[ardnum]->at(j) >= 96) dstrip[int(ardnum/2)]->push_back(ROA[ardnum]->at(j) - 95);
      }
    }
    
    // here fill the occupancy plots for w, s, ds!!!
    
    digiL1b->SetAddress(&digiLay[0]);
    digiL2b->SetAddress(&digiLay[1]);
    digiL3b->SetAddress(&digiLay[2]);
    digiL4b->SetAddress(&digiLay[3]);
    
    digiTree->Fill();
  }
  
  rawTree->ResetBranchAddresses();
  
  digiTree->Write();
  digiTree->Print();
  
  outfile->Close();
  
  return 0;
}
