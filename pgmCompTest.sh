echo -------------------------------------
make pgmComp
make pgmEcho
echo

echo -------------------------------------
./pgmComp
echo Return code $?
echo

echo -------------------------------------
./pgmComp sampleFile.pgm
echo Return code $?
echo

echo -------------------------------------
./pgmComp sampleFile.pgm not_exist.pgm 
echo Return code $?
echo

echo -------------------------------------
./pgmEcho sampleFile.pgm copy.pgm
./pgmComp sampleFile.pgm copy.pgm
echo Return code $?
echo

echo -------------------------------------
./pgmComp sampleFile.pgm casablanca.pgm
echo Return code $?
