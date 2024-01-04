// Header file for PGM file functions
#ifndef PGMUTILS_H
#define PGMUTILS_H

// Structure for storing the
// image data
typedef struct PGMImage {
    char pgmType[3];
    unsigned char** data;
    int width;
    int height;
    int maxValue;
} PGMImage;

// Error codes
#define SUCCESS             0
#define BAD_ARGUMENT_COUNT  1
#define BAD_FILE_NAME       2
#define BAD_MAGIC_NUMBER    3
#define BAD_COMMENT_LINE    4
#define BAD_DIMENSIONS      5
#define BAD_MAX_GRAY_VALUE  6
#define MALLOC_FAILED       7
#define BAD_DATA            8
#define OUTPUT_FAILED       9
#define BAD_LAYOUT          10
#define ERROR               100

void openPGM(PGMImage* pgm, const char* filename);
void allocateData(PGMImage* pgm);
void freePGM(PGMImage* pgm);
void savePGM(PGMImage* pgm, const char* filename, const char* comment);
int compPGM(PGMImage* pgm1, PGMImage* pgm2);
void getPGM(PGMImage* src, PGMImage* dst, int row, int col);
void putPGM(PGMImage* src, PGMImage* dst, int row, int col);

#endif