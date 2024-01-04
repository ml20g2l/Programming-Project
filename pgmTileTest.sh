echo -------------------------------------
make pgmTile
echo

echo -------------------------------------
./pgmTile
echo Return code $?
echo

echo -------------------------------------
./pgmTile sampleFile.pgm
echo Return code $?
echo

echo -------------------------------------
./pgmTile sampleFile.pgm 3 output.pgm 
echo Return code $?
echo

echo -------------------------------------
./pgmTile sampleFile.pgm 3 "output_<row>.pgm" 
echo Return code $?
echo

echo -------------------------------------
./pgmTile sampleFile.pgm 3 "output_<row>_<cols>.pgm" 
echo Return code $?
echo

echo -------------------------------------
./pgmTile sampleFile.pgm 3 "output_<row>_<column>_<row>.pgm" 
echo Return code $?
echo

echo -------------------------------------
./pgmTile sampleFile.pgm 3 "output_<row>_<column>.pgm" 
echo Return code $?
echo