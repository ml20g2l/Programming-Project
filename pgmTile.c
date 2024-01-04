#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pgmUtils.h"

// Return 1 if the first string begins with the second string
int  beginwith(const char* s, const char* t)
{
    while (*s != '\0' && *t != '\0') {
        if (*s != *t) {
            return 0;
        }
        s++;
        t++;
    }
    if (*t != '\0') {
        // the first string is shorter
        return 0;
    }
    return 1;
}

// copy a string from pattern into the string tilename replacing <row>
// and <column> with their values from variables row and col respectivly
// If there is no such string or they occerd more then onece
// the function terminates with error mesage.
// Also as error considered the appearance of other words in brackets
void getTileName(char* tilename, const char* pattern, int row, int col)
{
    char strRow[5], strCol[5];
    char *patRow = "row>";
    char *patCol = "column>";
    char *p; 
    const char *q;
    char *s;
    int nRow=0, nCol=0;

    // Convert int to string
    sprintf(strRow, "%d", row);
    sprintf(strCol, "%d", col);

    p = tilename;
    q = pattern;

    while (*q != '\0') {
        // Found a placeholder
        if (*q == '<') {
            q++;
            if (beginwith(q, patRow)) {
                nRow++;
                q += strlen(patRow);
                s = strRow;
            }
            else if (beginwith(q, patCol)) {
                nCol++;
                q += strlen(patCol);
                s = strCol;
            }
            else {
                fprintf(stderr, "ERROR: Miscellaneous (unknown placeholder)\n");
                exit(ERROR);
            }
            // Copy a number to the filename
            while (*s != '\0') {
                *(p++) = *(s++);
            }
        }
        else {
            // just copy a char
            *(p++) = *(q++);
        }
    }
    // Put a null at the end
    *p = '\0';

    if (nRow != 1 || nCol != 1) {
        fprintf(stderr, "ERROR: Miscellaneous (wrong number placeholders)\n");
        exit(ERROR);
    }
}


int main(int argc, char const* argv[])
{
    PGMImage pgm, pgmtile;
    int factor;
    double dx, dy;
    int i, j;
    int width, height;
    int pX, pY;         // x and y coordinate of the first subimage pixel
    char tilename[80];

    if (argc == 1) {
        printf("Usage: %s inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm\n", argv[0]);
        exit(SUCCESS);
    }
    if (argc != 4) {
        fprintf(stdout, "ERROR: Bad Argument Count\n");
        exit(BAD_ARGUMENT_COUNT);
    }

    // Read
    openPGM(&pgm, argv[1]);
    factor = atoi(argv[2]);

    // Get tiles size in real number
    dx = pgm.width / (double) factor;
    dy = pgm.height / (double) factor;

    // Copy image format
    pgmtile.maxValue = pgm.maxValue;
    for (i=0; i<3; i++) {
        pgmtile.pgmType[i] = pgm.pgmType[i];
    }

    pX = pY = 0;
    for (i=0; i<factor; i++) {
        // Calculate tile height
        height = round(dy*(i+1)) - round(dy*i);

        for (j=0; j<factor; j++) {
            // Calculate tile width
            width = round(dx*(j+1)) - round(dx*j);
            pgmtile.width = width;
            pgmtile.height = height;
            allocateData(&pgmtile);
            // Copy tile
            getPGM(&pgm, &pgmtile, pY, pX);
            getTileName(tilename, argv[3], i, j);
            savePGM(&pgmtile, tilename, NULL);

            freePGM(&pgmtile);
            pX += width;
        }

        // Start new row
        pX = 0;
        pY += height;
    }
  
    freePGM(&pgm);
    
    printf("TILED\n");
    
    return SUCCESS;
}