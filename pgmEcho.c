#include <stdio.h>
#include <stdlib.h>
#include "pgmUtils.h"

int main(int argc, char const* argv[])
{
    PGMImage pgm;

    if (argc == 1) {
        printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
        exit(SUCCESS);
    }
    if (argc != 3) {
        fprintf(stdout, "ERROR: Bad Argument Count\n");
        exit(BAD_ARGUMENT_COUNT);
    }

    openPGM(&pgm, argv[1]);
    savePGM(&pgm, argv[2], NULL);
    freePGM(&pgm);
    printf("ECHOED\n");
    return SUCCESS;
}
