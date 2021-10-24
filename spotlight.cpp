#include "spotlight.h"
#include <cmath>

Spotlight::Spotlight(string filename,int centX, int centY):Image(filename)
{
    this->centerX=centX;
    this->centerY=centY;
    readFromFile(filename);
    for(unsigned x = 0; x < width() ; x++)
      for(unsigned y = 0; y < height(); y++)
      {
         double dist = sqrt(((x-centerX)*(x-centerX))+((y-centerY)*(y-centerY)));
         //reference on the pixel
         HSLAPixel &P = getPixel(x, y);
         //modifiy the element of P
         if(dist<160)
              P.l=P.l*(1-dist*0.005);
         else
            P.l=0.2*P.l;
      }
}


void Spotlight::changeSpotPoint(int cX, int cY)
{
    for(unsigned x = 0; x < width() ; x++)
      for(unsigned y = 0; y < height(); y++)
      {
         double O_dist = sqrt(((x-centerX)*(x-centerX))+((y-centerY)*(y-centerY)));
         double N_dist = sqrt(((x-cX)*(x-cX))+((y-cY)*(y-cY)));
         //reference on the pixel
         HSLAPixel &P = getPixel(x, y);
         //modifiy the element of P
         if(O_dist>=160)
             P.l=5*P.l;
         else
            P.l=P.l/(1-O_dist*0.005);

         if(N_dist>=160)
             P.l=0.2*P.l;
         else
            P.l=P.l*(1-N_dist*0.005);
      }
}

