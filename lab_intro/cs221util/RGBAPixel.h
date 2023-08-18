#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

class RGBAPixel {

public:

// A RGBA pixel is characterized by 3 unsigned chars:
unsigned char r;
unsigned char g;
unsigned char b;

// and 1 double representing the transparency value typically called alpha (in the range of [0, 1]):
double a;


RGBAPixel();

RGBAPixel(int x, int y, int z);

RGBAPixel(int x, int y, int z, double i);

};

#endif
