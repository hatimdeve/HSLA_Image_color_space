#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H
#include "image.h"

class Spotlight : public Image
{
public:
    using Image::Image;
    int centerX;
    int centerY;
    Spotlight(string filename, int centX, int centY);
    void changeSpotPoint(int cX, int cY);
};

#endif // SPOTLIGHT_H
