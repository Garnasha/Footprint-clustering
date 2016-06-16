
INCLUDE_DIR = includes
INCLUDE_F = -I$(INCLUDE_DIR)

OPTIMIZE_F = -O2
WARN_F = -Weverything -Wno-c++98-compat -Wno-global-constructors -Wno-shadow \
		 -Wno-exit-time-destructors
STANDARD_F = -std=c++14
MODE_F = -g $(OPTIMIZE_F)

CLANG = clang++ $(WARN_F) $(STANDARD_F) $(MODE_F) $(INCLUDE_F)


lib/libfasta.o: src/libfasta.cpp includes/libfasta.h
	$(CLANG) src/libfasta.cpp -c -o lib/libfasta.o


