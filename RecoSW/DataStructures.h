#ifndef DataStructures_h
#define DataStructures_h

using namespace std;

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

#endif
