#include "image.h"

Image::Image(string filename):PNG()
{
    readFromFile(filename);
}
void Image::lighten(double amount)
{
    for(unsigned i=0;i< width();i++)
    {
        for(unsigned j=0;j<height();j++)
        {
            HSLAPixel &p  = getPixel(i,j);
            p.l += amount;
            p.l = (p.l>0) ? p.l:0;
            p.l = (p.l<=1)? p.l:1;
        }
    }
}
void Image::saturate(double amount)
{
    for(unsigned i=0;i< width();i++)
    {
        for(unsigned j=0;j<height();j++)
        {
            HSLAPixel &p  = getPixel(i,j);
            p.s += amount;
            p.s = (p.s>0) ? p.s:0;
            p.s = (p.s<=1)? p.s:1;
        }
    }
}
void Image::rotateColor(double angle)
{
    for(unsigned i=0;i< width();i++)
    {
        for(unsigned j=0;j<height();j++)
        {
            HSLAPixel &p  = getPixel(i,j);
            p.h += angle;
            while (p.h>360)
                p.h=p.h-360;
            while (p.h<0)
                p.h=p.h+360;
        }
    }
}

