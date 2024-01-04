echo -------------------------------------
make pgma2b
make pgmb2a
make pgmComp
echo

echo -------------------------------------
./pgma2b
echo Return code $?
echo

echo -------------------------------------
./pgmb2a
echo Return code $?
echo

echo -------------------------------------
./pgma2b sampleFile.pgm
echo Return code $?
echo

echo -------------------------------------
./pgmb2a sampleFile.pgm
echo Return code $?
echo

echo -------------------------------------
./pgma2b not_exist.pgm bin.pgm
echo Return code $?
echo

echo -------------------------------------
./pgmb2a not_exist.pgm ascii.pgm
echo Return code $?
echo

echo -------------------------------------
./pgma2b sampleFile.pgm bin.pgm
echo Return code $?
./pgmComp sampleFile.pgm bin.pgm
echo

echo -------------------------------------
./pgmb2a bin.pgm ascii.pgm
echo Return code $?
./pgmComp ascii.pgm bin.pgm
diff sampleFile.pgm ascii.pgm
echo

