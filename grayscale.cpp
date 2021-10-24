#include "grayscale.h"

Grayscale::Grayscale(string filename):Image(filename)
{
    readFromFile(filename);
    saturate(-1);
}

