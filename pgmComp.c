#include <stdio.h>
#include <stdlib.h>
#include "pgmUtils.h"

int main(int argc, char const* argv[])
{
    PGMImage pgm1, pgm2;
    int res;

    if (argc == 1) {
        printf("Usage: %s inputImage.pgm inputImage.pgm\n", argv[0]);
        exit(SUCCESS);
    }
    if (argc != 3) {
        fprintf(stdout, "ERROR: Bad Argument Count\n");
        exit(BAD_ARGUMENT_COUNT);
    }

    // Read
    openPGM(&pgm1, argv[1]);
    openPGM(&pgm2, argv[2]);
    // Compare
    res = compPGM(&pgm1, &pgm2);
    // clean
    freePGM(&pgm1);
    freePGM(&pgm2);

    if (res == 0) {
        printf("IDENTICAL\n");
    }
    else {
        printf("DIFFERENT\n");
    }
    return SUCCESS;
}
