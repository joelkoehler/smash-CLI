#-----------------------------------------------------------------------------
#
# Makefile -- Re-usable makefile for building many simple targets
#
# Usage
#  make all    Build all files out of date
#  make clean  Remove build artifacts
#
#-----------------------------------------------------------------------------


#-------Define options passed by make to the compiler and which complier to use
CFLAGS = -std=c99 -Wall  -g

#Arrange for phony target all to rebuild the dependency file, rules.d

all: rules.d smash

smash: smash.o commands.o history.o
	gcc $(CFLAGS) $^ -o $@

#Rebuild rules.d if it’s out-of-date with any *.c or *.h file using gcc -MM
rules.d: $(wildcard *.c) $(wildcard *.h)
	gcc -MM $(wildcard *.c) >rules.d

#Incorporate the auto-generated dependencies from rules.d into this Makefile
-include rules.d

#-------Define target "clean" for removing all build artifacts
clean:
	rm -f *.o smash *.d
  

