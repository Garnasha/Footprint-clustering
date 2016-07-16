
INCLUDE_DIR := includes
INCLUDE_F := -I$(INCLUDE_DIR)

OPTIMIZE_F := -O2
WARN_F := -Weverything -Wno-c++98-compat -Wno-global-constructors -Wno-shadow \
		 -Wno-exit-time-destructors
STANDARD_F := -std=c++14
MODE_F := -g $(OPTIMIZE_F)

CLANG := clang++ $(WARN_F) $(STANDARD_F) $(MODE_F) $(INCLUDE_F)

main.out: lib/libfasta.o src/main.cpp
	$(CLANG) lib/libfasta.o src/main.cpp -o main.out

lib/libfasta.o: src/libfasta.cpp includes/libfasta.h lib/dnatypes.o \
	lib/footprinttypes.o
	$(CLANG) src/libfasta.cpp -c -o lib/libfastabare.o
	ld -r lib/libfastabare.o lib/dnatypes.o lib/footprinttypes.o -o lib/libfasta.o

lib/dnatypes.o: includes/dnatypes.h lib/sequence.o lib/nucleotide.o
	ld -r lib/sequence.o lib/nucleotide.o -o lib/dnatypes.o

lib/footprinttypes.o: includes/footprinttypes.h lib/fullfootprint.o
	cp lib/fullfootprint.o lib/footprinttypes.o

lib/sequence.o: src/sequence.cpp includes/sequence.h
	$(CLANG) src/sequence.cpp -c -o lib/sequence.o

lib/nucleotide.o: src/nucleotide.cpp includes/nucleotide.h
	$(CLANG) src/nucleotide.cpp -c -o lib/nucleotide.o

lib/fullfootprint.o: src/fullfootprint.cpp includes/fullfootprint.h
	$(CLANG) src/fullfootprint.cpp -c -o lib/fullfootprint.o

