#include <stdio.h>
#include <stdlib.h>
#include "pgmUtils.h"

int main(int argc, char const* argv[])
{
    PGMImage pgm;
    int res;

    if (argc == 1) {
        printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
        exit(SUCCESS);
    }
    if (argc != 3) {
        fprintf(stdout, "ERROR: Bad Argument Count\n");
        exit(BAD_ARGUMENT_COUNT);
    }

    // Read
    openPGM(&pgm, argv[1]);
    if (pgm.pgmType[1] != '2') {
        fprintf(stdout, "ERROR: Miscellaneous (%s is not ASCII)\n", 
                argv[1]);
        freePGM(&pgm);
        exit(ERROR);
    }
    // Change the type
    pgm.pgmType[1] = '5';
    // Save
    savePGM(&pgm, argv[2], NULL);
    freePGM(&pgm);
    
    printf("CONVERTED\n");
    
    return SUCCESS;
}