#include "illini.h"

Illini::Illini(string filename,int col1,int col2):Image(filename)
{
    this->color1=col1;
    this->color2=col2;
    readFromFile(filename);
    for(unsigned x = 0; x < width() ; x++)
      for(unsigned y = 0; y < height(); y++)
      {
         //reference on the pixel
         HSLAPixel &P = getPixel(x, y);
         //modifiy the element of P
         int ma_hue=max(color1,color2);
         int mi_hue=min(color1,color2);
         int half_r_dist=(ma_hue-mi_hue)/2;
         int half_l_dist=(360-ma_hue+mi_hue)/2+ma_hue;
        P.h= (P.h>half_r_dist && P.h<=half_l_dist) ?ma_hue:mi_hue;
      }
}

