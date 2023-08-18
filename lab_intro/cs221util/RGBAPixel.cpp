#include "RGBAPixel.h"

RGBAPixel:: RGBAPixel() {
    r = 255;
    g = 255;
    b = 255;
}

RGBAPixel:: RGBAPixel(int x, int y, int z) {
    r = x;
    g = y;
    b = z; 
}

RGBAPixel:: RGBAPixel(int x, int y, int z, double i) {
    r = x;
    g = y;
    b = z; 
    a = i;
}







