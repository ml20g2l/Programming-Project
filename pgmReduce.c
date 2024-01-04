#include <stdio.h>
#include <stdlib.h>
#include "pgmUtils.h"

int main(int argc, char const* argv[])
{
    PGMImage pgm, pgmr;
    int factor;

    if (argc == 1) {
        printf("Usage: %s inputImage.pgm reduction_factor outputImage.pgm\n", argv[0]);
        exit(SUCCESS);
    }
    if (argc != 4) {
        fprintf(stderr, "ERROR: Bad Argument Count\n");
        exit(BAD_ARGUMENT_COUNT);
    }

    // Read
    openPGM(&pgm, argv[1]);
    factor = atoi(argv[2]);
    // Reduce
    reducePGM(&pgm, &pgmr, factor);
    // Save
    savePGM(&pgmr, argv[3], NULL);
    freePGM(&pgm);
    freePGM(&pgmr);
    
    printf("REDUCED\n");
    
    return SUCCESS;
}