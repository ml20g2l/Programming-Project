#include <stdio.h>
#include <stdlib.h>
#include "pgmUtils.h"

int main(int argc, char const* argv[])
{
    PGMImage pgm, pgmsub;
    int factor;
    int i, n;
    int res1, res2;
    int width, height;
    int row, col;

    if (argc == 1) {
        printf("Usage: %s outputImage.pgm width height (row column inputImage.pgm)+\n", argv[0]);
        exit(SUCCESS);
    }
    if ((argc-1) % 3 != 0) {
        fprintf(stdout, "ERROR: Bad Argument Count\n");
        exit(BAD_ARGUMENT_COUNT);
    }

    // Set result image size
    res1 = sscanf(argv[2], "%d", &width);
    res2 = sscanf(argv[3], "%d", &height);
    if ( res1 != 1 || res2 != 1 || width <= 0  || height <= 0) {
        fprintf(stdout, "ERROR: Bad Layout\n");
        exit(BAD_LAYOUT);
    }
    pgm.width = width;
    pgm.height = height;

    // Set ASCII type
    pgm.pgmType[0] = 'P';
    pgm.pgmType[1] = '2';
    pgm.pgmType[2] = '\0';
    pgm.maxValue = 0;

    // Allocate space for image pixels
    allocateData(&pgm);

    // Number of subimages
    n = (argc - 3) / 3;
    for (i=0; i<n; i++) {
        res1 = sscanf(argv[3*i+4], "%d", &row);
        res2 = sscanf(argv[3*i+5], "%d", &col);
        if (res1 != 1 || res2 != 1 || row < 0  || col < 0) {
            fprintf(stdout, "ERROR: Bad Layout\n");
            exit(BAD_LAYOUT);
        }
        openPGM(&pgmsub, argv[3*i+6]);

        // Check that subimage is inside large image
        if (col+pgmsub.width > width || row+pgmsub.height > height) {
            fprintf(stdout, "ERROR: Bad Layout\n");
            exit(BAD_LAYOUT);
        }
        // Put the subimage
        putPGM(&pgmsub, &pgm, row, col);
        freePGM(&pgmsub);
    }

    savePGM(&pgm, argv[1], NULL);

    freePGM(&pgm);

    printf("ASSEMBLED\n");

    return SUCCESS;
}
