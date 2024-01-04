echo -------------------------------------
make pgmComp
make pgmTile
make pgmAssemble
echo

echo -------------------------------------
./pgmAssemble
echo Return code $?
echo

echo -------------------------------------
./pgmAssemble output.pgm 9 9
echo Return code $?
echo 

echo -------------------------------------
./pgmTile sampleFile.pgm 2 "output_<row>_<column>.pgm" 
./pgmAssemble assembe.pgm 9 9 0 0 output_0_0.pgm 0 4 otput_0_1.pgm 4 0 output_1_0.pgm 4 4 output_1_1.pgm
echo Return code $?
./pgmComp sampleFile.pgm assemble.pgm
echo