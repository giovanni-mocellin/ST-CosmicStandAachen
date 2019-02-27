#include "IncludeLibraries.h"

using namespace std;

struct inclStrip {
  float m;
  float q;
};

class digi {
  int layer, wire, strip, istrip;
};

class recHit {
  double x_, y_, z_;
  double xerr_, yerr_, zerr_;
public:
  void set_xval(double, double);
  void set_yval(double, double);
  void set_zval(double, double);
  double x() {return(x_);}
  double y() {return(y_);}
  double z() {return(z_);}
  double xerr() {return(xerr_);}
  double yerr() {return(yerr_);}
  double zerr() {return(zerr_);}
};

void recHit::set_xval (double hit_x, double hit_xerr) {
  x_ = hit_x;
  xerr_ = hit_xerr;
}
void recHit::set_yval (double hit_y, double hit_yerr) {
  y_ = hit_y;
  yerr_ = hit_yerr;
}
void recHit::set_zval (double hit_z, double hit_zerr) {
  z_ = hit_z;
  zerr_ = hit_zerr;
}
