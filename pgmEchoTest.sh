echo -------------------------------------
make pgmEcho
echo

echo -------------------------------------
./pgmEcho
echo Return code $?
echo

echo -------------------------------------
./pgmEcho sampleFile.pgm
echo Return code $?
echo

echo -------------------------------------
./pgmEcho not_exist.pgm copy.pgm
echo Return code $?
echo

echo -------------------------------------
./pgmEcho sampleFile.pgm copy.pgm
echo Return code $?
diff sampleFile.pgm copy.pgm
