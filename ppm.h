/*
  Jason Rodgers
  CPSC 2311 Sp22 Section 01
  jtrodge@g.clemson.edu
*/

#ifndef FILE_NAME_H
#define FILE_NAME_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct Header{
  char magicNum[3];
  int width;
  int height;
  int maxVal;
}header_t;

typedef struct Pixel{
  unsigned char r,g,b;
}pixel_t;

header_t* readHeader(FILE*);
pixel_t** readPPM(FILE*,header_t*);
void writeP6Image(header_t*, pixel_t**, FILE*);
void grayScaleImage(header_t*, pixel_t**, FILE*);
void flipImage(header_t*, pixel_t**, FILE*);
pixel_t** allocateMemory(header_t*);
void freeMemory(pixel_t**, header_t*);
#endif
