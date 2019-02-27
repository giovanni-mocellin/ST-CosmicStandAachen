#!/bin/bash

g++ -pthread -stdlib=libc++ -std=c++11 -m64 -I/Applications/root_v6.14.06/include -L/Applications/root_v6.14.06/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTDataFrame -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lpthread -stdlib=libc++ -lm -ldl Unpacker/Unpacker.cpp -o Unpacker/Unpacker

g++ -pthread -stdlib=libc++ -std=c++11 -m64 -I/Applications/root_v6.14.06/include -L/Applications/root_v6.14.06/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTDataFrame -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lpthread -stdlib=libc++ -lm -ldl DigiToRecHit/DigiToRecHit.cpp -o DigiToRecHit/DigiToRecHit

g++ -pthread -stdlib=libc++ -std=c++11 -m64 -I/Applications/root_v6.14.06/include -L/Applications/root_v6.14.06/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTDataFrame -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lpthread -stdlib=libc++ -lm -ldl RawToDigi/RawToDigi.cpp -o RawToDigi/RawToDigi
