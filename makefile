CC = gcc
CFLAGS = -g -std=c99
LDFLAGS = -lm
EXE = pgmEcho pgmComp pgma2b pgmb2a pgmTile pgmAssemble

all: $(EXE)

pgmEcho: pgmEcho.o pgmUtils.o 
	$(CC) $^ -o $@ $(LDFLAGS)

pgmComp: pgmComp.o pgmUtils.o
	$(CC) $^ -o $@ $(LDFLAGS)

pgma2b: pgma2b.o pgmUtils.o
	$(CC) $^ -o $@ $(LDFLAGS)

pgmb2a: pgmb2a.o pgmUtils.o
	$(CC) $^ -o $@ $(LDFLAGS)
	
pgmTile: pgmTile.o pgmUtils.o
	$(CC) $^ -o $@ $(LDFLAGS)

pgmAssemble: pgmAssemble.o pgmUtils.o
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@  $< $(CFLAGS)

clean:
	rm -f $(EXE)
	rm -f *.o
