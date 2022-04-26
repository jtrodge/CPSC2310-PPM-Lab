/*
  Jason Rodgers
  CPSC 2311 Sp22 Section 01
  jtrodge@g.clemson.edu
*/

#include "ppm.h"

// int main(void) {
//   FILE* input = fopen("mario.ppm", "r");
//   // FILE* output1 = fopen("", "w");
//   // FILE* output2 = fopen("gray.ppm", "w");
//   // FILE* output3 = fopen("flip.ppm", "w");
//   header_t* header;
//   pixel_t** pixel;
//   header = readHeader(input);
//   pixel = readPPM(input, header);
//   // writeP6Image(header, pixel, output1);
//   // grayScaleImage(header, pixel, output2);
//   // flipImage(header, pixel, output3);
//
//   return 0;
// }

int main(int argc, char* argv[]) {
    // Special case for reading in command line arguments
    if (argc != 4) {
      printf("File will not open. argc <= 2");
      exit(1);
    }
    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "w");
    FILE* out2 = fopen(argv[3], "w");
    //assert(in != NULL);
    // Read in ppm image
    header_t* header;
    pixel_t** pixel;
    header = readHeader(in);
    pixel = readPPM(in, header);
    // Prints out grayScaleImage of mario
    grayScaleImage(header, pixel, out2);
    flipImage(header, pixel, out);
    // writeP6Image prints out flipImage
    writeP6Image(header, pixel, out);
    // Free's allocated memory
    freeMemory(pixel, header);

    return 0;
}
