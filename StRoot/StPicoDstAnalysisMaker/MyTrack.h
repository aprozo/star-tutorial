#ifndef MYTRACK_H
#define MYTRACK_H

#include "TObject.h"

class MyTrack {
public:
  float pt;
  float eta;
  float phi;
  short charge;
  short nHits;

  ClassDef(MyTrack, 1);
};

#endif // MYTRACK_H
