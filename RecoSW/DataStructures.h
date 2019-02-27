#include "IncludeLibraries.h"

using namespace std;

struct inclStrip {
  float m;
  float q;
};

class digi {
  int layer_, wire_, strip_, dstrip_;
  int w_cls_, s_cls_, ds_cls_;
public:
  void set_layer(int);
  void set_wire(int, int);
  void set_strip(int, int);
  void set_dstrip(int, int);
  double layer() {return(layer_);}
  double wire() {return(wire_);}
  double strip() {return(strip_);}
  double dstrip() {return(dstrip_);}
  double wire_clsize() {return(w_cls_);}
  double strip_clsize() {return(s_cls_);}
  double dstrip_clsize() {return(ds_cls_);}
};

void digi::set_layer (int digi_lay) {
  layer_ = digi_lay;
}
void digi::set_wire (int digi_w, int digi_wcls) {
  wire_ = digi_w;
  w_cls_ = digi_wcls;
}
void digi::set_strip (int digi_s, int digi_scls) {
  strip_ = digi_s;
  s_cls_ = digi_scls;
}
void digi::set_dstrip (int digi_ds, int digi_dscls) {
  dstrip_ = digi_ds;
  ds_cls_ = digi_dscls;
}

class recHit {
  double x_, y_, z_;
  double xerr_, yerr_, zerr_;
public:
  void set_x(double, double);
  void set_y(double, double);
  void set_z(double, double);
  double x() {return(x_);}
  double y() {return(y_);}
  double z() {return(z_);}
  double xerr() {return(xerr_);}
  double yerr() {return(yerr_);}
  double zerr() {return(zerr_);}
};

void recHit::set_x (double hit_x, double hit_xerr) {
  x_ = hit_x;
  xerr_ = hit_xerr;
}
void recHit::set_y (double hit_y, double hit_yerr) {
  y_ = hit_y;
  yerr_ = hit_yerr;
}
void recHit::set_z (double hit_z, double hit_zerr) {
  z_ = hit_z;
  zerr_ = hit_zerr;
}
