#include "DataStructures.h"
#include "IncludeLibraries.h"

int main () {
  recHit *hit = new recHit;
  hit->set_xval(1.,1.);
  cout << hit->x() << endl;
  return 0;
}
