#ifndef RAZOR_H
#define RAZOR_H

#include "Arduino.h"
#include "sio.h"

class razor : public sio
{
  private: float YPR[3] = {0};
           float FYPR[3] = {0};
           float RYPR[3] = {0};
           float WYPR[3] = {0};
  public: razor( String Name, Stream *bridge);
          void extractYPR();
          void displayYPR();
          void displayFYPR();
          void displayWYPR();
          void calculateFYPR();
          float* fetchFYPR( bool deg2rad = false);
          float* fetchYPR( bool deg2rad = false);
          void setReferenceYPR( bool RESET = false );
          void calculateWYPR();
};
#endif
