#include "Unpacker.h"

int main (int argc, char** argv)
{
  int run_num = atoi(argv[1]);
  
  string dataPath = "../../Run" + to_string(run_num);
  
  dataTree = new TTree;
  
  dataTree->Branch("run",&run,"run/i");
  dataTree->Branch("evt",&evt,"evt/i");
  dataTree->Branch("ROA1","std::vector",&ROA1);
  dataTree->Branch("ROA2","std::vector",&ROA2);
  dataTree->Branch("ROA3","std::vector",&ROA3);
  dataTree->Branch("ROA4","std::vector",&ROA4);
  dataTree->Branch("ROA5","std::vector",&ROA5);
  dataTree->Branch("ROA6","std::vector",&ROA6);
  dataTree->Branch("ROA7","std::vector",&ROA7);
  dataTree->Branch("ROA8","std::vector",&ROA8);
  
  run = run_num;
  evt = 0;
  
  // Here open chunk files, do the checks, find first events
  
  // Then start with the things---
  
  ROA1->SetAddress(&ROA1);
  ROA2->SetAddress(&ROA2);
  ROA3->SetAddress(&ROA3);
  ROA4->SetAddress(&ROA4);
  ROA5->SetAddress(&ROA5);
  ROA6->SetAddress(&ROA6);
  ROA7->SetAddress(&ROA7);
  ROA8->SetAddress(&ROA8);
  
  dataTree->Fill();
  
  return 0;
}
