#ifndef DataStructures_h
#define DataStructures_h

struct DStrip {
  float m;
  float q;
};

struct DStrip {
    float m;
    float q;
};

class point3D {
public:
    float x;
    float y;
    DStrip d;
    float z;
};

struct RecoTrack {
    float Angle;
    float Extrap;
    float NormChi2;
};

int main () {
  Rectangle rect;
  rect.set_values (3,4);
  cout << "area: " << rect.area();
  return 0;
}

#endif
