/*
  Jason Rodgers
  CPSC 2311 Sp22 Section 01
  jtrodge@g.clemson.edu
*/


#include "ppm.h"

header_t* readHeader(FILE* in) {
  header_t *read = (header_t*)malloc(256 * sizeof(header_t));
  // Reads header in image
  fscanf(in, "%s\n%d %d %d\n", read->magicNum, &read->width, &read->height, &read->maxVal);
  return read;
}

pixel_t** readPPM(FILE* in,header_t* h) {
  pixel_t** image = allocateMemory(h);
  // Temp variables
  unsigned char r, g, b;
  for (int i = 0; i < h->width; i++) {
    for (int j = 0; j < h->height; j++) {
      // Read rgb values from the file
      fscanf(in, "%c%c%c", &r, &g, &b);
      // fscanf(in, "%c%c%c", &pic.r, &pic.g, &pic.b);
      image[i][j].r = r;
      image[i][j].g = g;
      image[i][j].b = b;
    }
  }
  return image;
}

void writeP6Image(header_t* h, pixel_t** p, FILE* out) {
  // Print header to the file
  fprintf(out, "%s\n%d %d %d\n", h->magicNum, h->width, h->height, h->maxVal);
  // Prints rgb values to the file
  // Read through height first (Similar to a 2d matrix)
  for (int i = 0; i < h->height; i++) {
    for(int j = 0; j < h->width; j++) {
      fprintf(out, "%c%c%c", p[i][j].r,  p[i][j].g,  p[i][j].b);
    }
  }
}

void grayScaleImage(header_t* h, pixel_t** p, FILE* out2) {
  // Print header to the file (P5 image)
  fprintf(out2, "P5\n%d %d %d\n", h->width, h->height, h->maxVal);
  int grayScale;
  int rVal;
  int gVal;
  int bVal;
  for (int i = 0; i < h->width; i++) {
    for (int j = 0; j < h->height; j++) {
      rVal = ((int)p[i][j].r * .299);
      gVal = ((int)p[i][j].g * .587);
      bVal = ((int)p[i][j].b * .114);
      grayScale = rVal + gVal + bVal;
      // Print the new grayscale image to the file
      fprintf(out2, "%c", (unsigned char)grayScale);
    }
  }
}

void flipImage(header_t* h, pixel_t** p, FILE* out) {
  pixel_t **image = allocateMemory(h);
  for (int i = 0; i < (h->width / 2); i++) {
    for (int j = 0; j != h->height; j++) {
      // Swap the variables around
      image[i][j] = p[i][j];
      p[i][j] = p[(h->width - 1 - i)][j];
      p[(h->width - 1 - i)][j] = image[i][j];
    }
  }
}

pixel_t** allocateMemory(header_t* h) {
  // Allocates a 2d array
  pixel_t** color = (pixel_t**)malloc(h->width * sizeof(pixel_t*));
  for (int i = 0; i < h->width; i++) {
    color[i] = (pixel_t*)malloc(h->height * sizeof(pixel_t));
  }
  return color;
}

void freeMemory(pixel_t** p, header_t* h) {
  // Free the memory of the row, and then the rest of the contents
  for(int i = 0; i < h->width; i++) {
    free(p[i]);
  }
  free(p);
}
