/*
created by Arthur Gomes
date last modified : 5/4/20
*/
#include "razor.h"


   razor::razor( String Name, Stream *bridge)// : sio{ Name, bridge }  unfinished business here....
   {
     this->serialName = Name;
     this->serialStream = bridge;
   }
   void razor::extractYPR()
   {

     this->writeToSerial("#f");

     while ( this->serialStream->available() <= 0 )
     {
       continue;
     }
     this->serialStream->readStringUntil('=');

     this->YPR[0] = this->serialStream->readStringUntil(',').toFloat() - this->RYPR[0] ;

     this->YPR[1] = this->serialStream->readStringUntil(',').toFloat() - this->RYPR[1] ;

     this->YPR[2] = this->serialStream->readStringUntil('\n').toFloat() - this->RYPR[2] ;


   }
   void razor::displayYPR()
   {
     this->extractYPR();

     String msg = "Y : ";
     msg.concat(this->YPR[0]);
     msg.concat(" P : ");
     msg.concat(this->YPR[1]);
     msg.concat(" R : ");
     msg.concat(this->YPR[2]);
     this->serialMonitor(msg);

   }
   void razor::displayFYPR()
   {
     this->calculateFYPR();

     String msg = "Y : ";
     msg.concat(this->FYPR[0]);
     msg.concat(" P : ");
     msg.concat(this->FYPR[1]);
     msg.concat(" R : ");
     msg.concat(this->FYPR[2]);
     this->serialMonitor(msg);

   }
   void razor::displayWYPR()
   {
     this->calculateWYPR();

     String msg = "Y : ";
     msg.concat(this->WYPR[0]);
     msg.concat(" P : ");
     msg.concat(this->WYPR[1]);
     msg.concat(" R : ");
     msg.concat(this->WYPR[2]);
     this->serialMonitor(msg);
   }
   void razor::calculateFYPR()
   {
     this->extractYPR();

     int i;
     for (i = 0; i < 3; i++ )
     {
       this->FYPR[i] = this->YPR[i] < 0 ? this->YPR[i] + 360 : this->YPR[i];
     }
   }
   float* razor::fetchFYPR( bool deg2rad = false)
   {
     this->extractYPR();
     this->calculateFYPR();

     if ( deg2rad == false )
     {
       return FYPR;
     }
     else
     {
       int i;
       for (i = 0; i < 3; i++)
       {
         this->FYPR[i] = this->FYPR[i] * 0.0174533;
       }
       return FYPR;
     }
   }
   float* razor::fetchYPR( bool deg2rad = false)
   {
     this->extractYPR();

     if ( deg2rad == false )
     {
       return YPR;
     }
     else
     {
       int i;
       for (i = 0; i < 3; i++)
       {
         this->YPR[i] = this->YPR[i] * 0.0174533;
       }
       return YPR;
     }
   }
   void razor::setReferenceYPR( bool RESET = false )
   {
     int i;
     if (RESET)
     {
       for (i = 0; i < 3; i++)
         this->RYPR[i] = 0;
     }
     else
     {
       this->extractYPR();
       for (i = 0; i < 3; i++)
         this->RYPR[i] = this->YPR[i];
     }
   }
   void razor::calculateWYPR()
   {
     int i;
     float ypr[3];
     int itime[3];
     this->calculateFYPR();

     for (i = 0 ; i < 3 ; i++)
     {
       ypr[i] = this->FYPR[i];
       itime[i] = millis();
     }
     this->calculateFYPR();
     for (i = 0; i < 3; i++)
     {
       WYPR[i] = (this -> FYPR[i] - ypr[i]) / (millis() - itime[i]);
     }
   }
