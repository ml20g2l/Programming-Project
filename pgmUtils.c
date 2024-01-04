#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "pgmUtils.h"

// Function to ignore any comments in file
void ignoreComments(FILE* fp)
{
    int ch;
    char line[100];

    // Ignore any blank lines
    while ((ch = fgetc(fp)) != EOF
        && isspace(ch))
        ;

    // Recursively ignore comments
    // in a PGM image commented lines
    // start with a '#'
    if (ch == '#') {
        do {
            fgets(line, sizeof(line), fp);
        } while (line[strlen(line)-1] != '\n');
        ignoreComments(fp);
    }
    else
        fseek(fp, -1, SEEK_CUR);
}

// Allocate memory for image data
void allocateData(PGMImage* pgm)
{
    int i;

    pgm->data = (unsigned char**)malloc(pgm->height * sizeof(unsigned char*));
    if (!pgm->data) {
        fprintf(stdout, "ERROR: Image Malloc Failed\n");
        exit(MALLOC_FAILED);
    }

    for (i = 0; i < pgm->height; i++) {
        pgm->data[i] = (unsigned char*)malloc(pgm->width);
        if (!pgm->data[i]) {
            fprintf(stdout, "ERROR: Image Malloc Failed\n");
            exit(MALLOC_FAILED);
        }
        // Fill the memory with zeros
        memset(pgm->data[i], 0, pgm->width);
    }
}

// Function to read a PGM image from a file
// On any error functrion print a message and terminate
void openPGM(PGMImage* pgm, const char* filename)
{
    int i, j, res;
    char ch;
    // Open the image file in the 'read binary' mode
    FILE* pgmfile = fopen(filename, "rb");

    // If file does not exist,
    // then return
    if (pgmfile == NULL) {
        fprintf(stdout, "ERROR: Bad File Name (%s)\n", filename);
        exit(BAD_FILE_NAME);
    }

    ignoreComments(pgmfile);
    fgets(pgm->pgmType, 3, pgmfile);

    // Check for correct PGM Binary
    // file type
    if (pgm->pgmType[0] != 'P' && (pgm->pgmType[1] != '2' ||
        pgm->pgmType[1] != '5')) {
        fprintf(stdout, "ERROR: Bad Magic Number (%s)\n", filename);
        fclose(pgmfile);
        exit(BAD_MAGIC_NUMBER);
    }

    ignoreComments(pgmfile);

    // Read the image dimensions
    fscanf(pgmfile, "%d %d", &(pgm->width), &(pgm->height));
    if (pgm->width <= 0 || pgm->height <= 0) {
        fclose(pgmfile);
        fprintf(stdout, "ERROR: Bad Dimensions (%s)\n", filename);
        exit(BAD_DIMENSIONS);
    }

    ignoreComments(pgmfile);

    // Read maximum gray value
    fscanf(pgmfile, "%d", &(pgm->maxValue));
    if (pgm->maxValue <= 0 || pgm->maxValue > 255) {
        fclose(pgmfile);
        fprintf(stdout, "ERROR: Bad Max Gray Value (%s)\n", filename);
        exit(BAD_MAX_GRAY_VALUE);
    }

    if (pgm->pgmType[1] == '2') {
        // In ascii skip a comment
        ignoreComments(pgmfile);
    }
    else {
        // In binary skip a new line
        char ch = fgetc(pgmfile);
        if (ch != '\n') {
            // If it is not - return char back
            ungetc(ch, pgmfile);
        }
    }

    // Allocete memory for data
    allocateData(pgm);

    // Read pixels row by row
    for (i = 0; i < pgm->height; i++) {
        if (pgm->pgmType[1] == '2') {
            // ASCII
            int x;
            for (j = 0; j < pgm->width; j++) {
                res = fscanf(pgmfile, "%uc", &x);
                pgm->data[i][j] = x;
                if (res != 1) {
                    fclose(pgmfile);
                    fprintf(stdout, "ERROR: Bad Data (%s)\n", filename);
                    exit(BAD_DATA);
                }
            }
        }
        else {
            // Binary
            res = fread(pgm->data[i], 1, pgm->width, pgmfile);
            if (res != pgm->width) {
                fclose(pgmfile);
                fprintf(stdout, "ERROR: Bad Data (%s)\n", filename);
                exit(BAD_DATA);
            }
        }
    }
    // Ignore any blank lines
    while ((ch = fgetc(pgmfile)) != EOF && isspace(ch))
        ;

    if (ch != EOF) {
        fclose(pgmfile);
        fprintf(stdout, "ERROR: Bad Data (%s)\n", filename);
        exit(BAD_DATA);
    }

    // Close the file
    fclose(pgmfile);
}

// Free memory allocated for pgm image data
void freePGM(PGMImage* pgm)
{
    int i;

    for (i = 0; i < pgm->height; i++) {
        free(pgm->data[i]);
    }
    free(pgm->data);
    pgm->data = NULL;
}

// Function to write a PGM image from a file
// On any error functrion print a message and terminate
void savePGM(PGMImage* pgm, const char* filename, const char* comment)
{
    FILE* pgmfile = fopen(filename, "wb");

    if (pgmfile == NULL) {
        fprintf(stdout, "ERRPR: Output Failed Error (%s)\n", filename);
        freePGM(pgm);
        exit(OUTPUT_FAILED);
    }

    fprintf(pgmfile, "%s\n", pgm->pgmType);
    if (comment) {
        // If comment is present - output it
        fprintf(pgmfile, "# %s\n", comment);
    }
    else {
        // Output file name as a comment
        fprintf(pgmfile, "# %s\n", filename);
    }
    fprintf(pgmfile, "%d %d\n", pgm->width, pgm->height);
    fprintf(pgmfile, "%d\n", pgm->maxValue);

    if (pgm->pgmType[1] == '2') {
        // ASCII
        int i, j;
        int w;      // field width
        int p, n;   // # of pixel in line, max number of pixel in line

        if (pgm->maxValue <= 10) {
            w = 1;
        }
        else if (pgm->maxValue <= 100) {
            w = 2;
        }
        else {
            w = 3;
        }
        n = 70 / (w + 1);
        n = pgm->width < n ? pgm->width : n;

        p = 0;
        for (i = 0; i < pgm->height; i++) {
            for (j = 0; j < pgm->width; j++) {
                fprintf(pgmfile, "%*d ", w, pgm->data[i][j]);
                p++;
                if (p == n) {
                    // time to start a new line
                    p = 0;
                    fputc('\n', pgmfile);
                }
            }
        }
    }
    else {
        // binary file
        int i;
        for (i = 0; i < pgm->height; i++) {
            // write a hole line of pixels at once
            fwrite(pgm->data[i], sizeof(char), pgm->width, pgmfile);
        }
    }
}

// Compare two pgm images
// return 0 if they are the same and 1 otherwise
int compPGM(PGMImage* pgm1, PGMImage* pgm2)
{
    int i, j;

    // Check sizes
    if (pgm1->width != pgm2->width) {
        return 1;
    }
    if (pgm1->height != pgm2->height) {
        return 1;
    }

    // Compare pixels
    for (i = 0; i < pgm1->height; i++) {
        for (j = 0; j < pgm1->width; j++) {
            if (pgm1->data[i][j] != pgm2->data[i][j]) {
                return 1;
            }
        }
    }
    return 0;
}

// Reduce PGM image src and save it in PGM image dst
// dst will be allocated.
// Reducing to zero size is an error
void reducePGM(PGMImage* src, PGMImage* dst, int factor) {
    int i, j;
    dst->width = src->width / factor;
    dst->height = src->height / factor;
    if (dst->width == 0 || dst->height == 0) {
        fprintf(stdout, "Miscellaneous (image reduced to zero)\n");
        free(src);
        exit(ERROR);
    }
    dst->maxValue = src->maxValue;

    // Copy magic number
    for (i=0; i<3; i++) {
        dst->pgmType[i] = src->pgmType[i];
    }

    // Allocate memory
    allocateData(dst);

    for (i=0; i<dst->height; i++) {
        for (j=0; j<dst->width; j++) {
            dst->data[i][j] = src->data[i*factor][j*factor];
        }
    }
}

// pick up a part of PGM image from src to dst starting at (row, col)
void getPGM(PGMImage* src, PGMImage* dst, int row, int col)
{
    int i, j;
    int n, m;

    // Number of rows to be copied
    n = dst->height < src->height-row ? dst->height : src->height-row;
    // Number of columns to be copied
    m = dst->width < src->width-col ? dst->width : src->width-col;

    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            dst->data[i][j] = src->data[i+row][j+col];
        }
    }
}

// put a PGM image from src to dst starting at (row, col)
void putPGM(PGMImage* src, PGMImage* dst, int row, int col)
{
    int i, j;
    int n, m;

    // Number of rows to be copied
    n = src->height < dst->height-row ? src->height : dst->height-row;
    // Number of columns to be copied
    m = src->width < dst->width-col ? src->width : dst->width-col;

    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            dst->data[i+row][j+col] = src->data[i][j];
        }
    }
    dst->maxValue = dst->maxValue < src->maxValue ? src->maxValue : dst->maxValue;
}