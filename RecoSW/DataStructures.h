#ifndef DataStructures_h
#define DataStructures_h

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

using namespace std;

class digi {
  int layer, wire, strip, dstrip;
public:
  void
};

class recHit {
  double x_, y_, z_;
public:
  void set_val(int, int, int);
  double x() {return x_};
  double y() {return y_};
  double z() {return z_};
};

void recHit::set_val (int hit_x, int hit_y, int hit_z) {
  width = hit_x;
  height = hit_y;
}

#endif
