#include "Unpacker.h"

int main (int argc, char** argv)
{
  run_num = atoi(argv[1]);
  
  string dataPath = "../../../ST_Run" + to_string(run_num) + "/";
  
  string outname = dataPath + "Run" + to_string(run_num) + "_raw.root";
  outfile = new TFile(outname.c_str(),"RECREATE");
  if ( outfile->IsOpen() ) cout << "outfile opened successfully" << endl;
  
  // Here we find how many chunks are in this run using ROA1 as test
  chunknum = 0;
  while (chunknum < 1000)
  {
    infileName = dataPath + "Run" + to_string(run_num) + "_chunk" + chunknum + "_ROA1.dat";
    testFile = new TFile(infileName.c_str());
    if ( testFile->IsOpen() ) testFile->Close();
    if ( !testFile->IsOpen() ) break;
    chunknum++;
  }
  
  if (chunknum == 1000)
  {
    cout << "Too many chunk files: more than 1000!!!" << endl;
    exit (EXIT_FAILURE);
  }
  
  for (chunk = 0 ; chunk < chunknum ; chunk++)
  {
    // - Open the 8 ROA files
    // - Find syncPosRoa, firstEvPosRoa, NumEvRoa for each of the 8 ROA
    // - The pointer is set to the first event to be read
    
    for (int ardnum = 0; ardnum < 8; ardnum++)
    {
      cout << "Checking file: run " << run_num << ", chunk " << chunk << ", ROA " << (ardnum+1) << endl;
      
      infileName = dataPath + "Run" + to_string(run_num) + "_chunk" + chunk + "_ROA" + ardnum + ".dat";
      infile[ardnum]->open(infileName.c_str(),ios::in|ios::binary);
      
      syncPosRoa[ardnum] = FindSyncMsg(infile[ardnum]);
      firstEvPosRoa[ardnum] = FindFirstEvent(infile[ardnum] ,syncPosRoa[ardnum], ardnum);
      numEvRoa[ardnum] = FindEvNumber(infile[ardnum] ,firstEvPosRoa[ardnum]);
      
      infile[ardnum]->seekg(firstEvPosRoa[ardnum],ios::beg);
    }
    
    // The min number of events is found among the 8 ROA chunk files
    evnum = FindMinEvNum(numEvRoa);
    
    // Loop for reading the events and storing them in the tree
    for (evt = 0 ; evt < evnum ; evt++)
    {
      if (evt % 250 == 0) cout << "Analyzing files: run " << run_num << ", chunk " << chunk << ", evt " << evt << endl;
      for (int ardnum = 0 ; ardnum < 8 ; ardnum++)
      {
        // Positioning at the corresponding event in the file
        infile[ardnum]->seekg((firstEvPosRoa[ardnum]+(evt*28)),ios::beg);
        
        // Reading the ROA number
        infile[ardnum]->read((char*)&roaFromFile, 1);
        if ((atoi(roaFromFile)-1) == ardnum) cout << "ROA number is wrong in ROA " << ardnum << ", evt " << evt << endl;
        
        // Reading the evt number
        infile[ardnum]->read((char*)&evtNumFromFile, 2);
        if (evt % 65536 != evtNumFromFile) cout << "Evt number is wrong in ROA " << ardnum << ", evt " << evt << endl;
        
        // Reading the data
        for (int sr = 0; sr < 6; sr++) // datablock is 4 bytes long (type = int) => 24/4 = 6 loops
        {
          infile[ardnum]->read((char*)&datablock, 4);
          for (unsigned int ch = 31; ch >= 0; ch--)
          {
            if (datablock-powerOfTwo(ch) > 0)
            {
              datablock = datablock - powerOfTwo(ch);
              ROA[ardnum]->push_back(ch+(sr*32));
            }
          }
        }
      }
      
      ROA1b->SetAddress(&ROA[0]);
      ROA2b->SetAddress(&ROA[1]);
      ROA3b->SetAddress(&ROA[2]);
      ROA4b->SetAddress(&ROA[3]);
      ROA5b->SetAddress(&ROA[4]);
      ROA6b->SetAddress(&ROA[5]);
      ROA7b->SetAddress(&ROA[6]);
      ROA8b->SetAddress(&ROA[7]);
      
      dataTree->Fill();
    }
    
    for (int ardnum = 0; ardnum < 8; ardnum++)
    {
      infile[ardnum]->close();
    }
  }
  
  dataTree->Write();
  dataTree->Print();
  outfile->Close();
  
  return 0;
}

unsigned int FindSyncMsg(fstream *datafile)
{
  unsigned int syncPos = 0;
  char * read33bytes;
  while (syncPos < 300)
  {
    datafile->seekg(syncPos*sizeof(char),ios::beg);
    datafile->read((char*)&read33bytes, 33*sizeof(char));
    if (string(read33bytes) == "Sync of all the Read-Out Arduinos") break;
    if (string(read33bytes) != "Sync of all the Read-Out Arduinos") syncPos++;
  }
  if (syncPos == 300)
  {
    cout << "Not found sync msg in the first 300 bytes" << endl;
    exit (EXIT_FAILURE);
  }
  return syncPos;
}

unsigned int FindFirstEvent(fstream *datafile, unsigned int syncPos, int roaNum)
{
  unsigned int firstEvPos = (syncPos+33);
  
  while (firstEvPos < 300)
  {
    datafile->seekg(firstEvPos,ios::beg);
    datafile->read((char*)&roaFromFile, 1);
    datafile->read((char*)&evtNumFromFile, 2);
    if ((atoi(roaFromFile)-1) == roaNum && evtNumFromFile == 1) break;
    firstEvPos++;
  }
  if (firstEvPos == 300)
  {
    cout << "Not found first event in the first 300 bytes" << endl;
    exit (EXIT_FAILURE);
  }
  return firstEvPos;
}

unsigned long int FindEvNumber(fstream *datafile, unsigned int firstEvPos)
{
  unsigned long int evntnumb = 0;
  while (evntnumb < 1000000) // Max 1 mln events in 2 minutes! (They should be max around 200k evts)
  {
    if (!datafile->seekg(firstEvPos + (evntnumb*28),ios::beg)) break;
    evntnumb++;
  }
  if (evntnumb == 1000000)
  {
    cout << "Something is wrong in this chunk file: too large number of events!!!" << endl;
    exit (EXIT_FAILURE);
  }
  return evntnumb;
}

unsigned int FindMinEvNum(unsigned int evNumRoa[8])
{
  unsigned int min = evNumRoa[0];
  for (int i=0; i<8; i++)
  {
    if(evNumRoa[i] < min) min = evNumRoa[i];
  }
  return min;
}

unsigned int powerOfTwo(int power)
{
  unsigned int result = 1;
  for (int i=0; i < power; i++) { result *= 2; }
  return result;
}
