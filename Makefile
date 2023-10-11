# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Computabilidad y Algoritmia
#
# @author Gabriel Canals
# @date 26 Sep 2023
# @brief A Makefile for the Graph program

CXX = g++						       # The C++ compiler command
CXXFLAGS = -std=c++17 -g	 # The C++ compiler options (C++17 and preserve debug symbols)

# The all target builds all of the programs handled by the makefile.
all: graph

graph: cell.cc main.cc labyrinth.cc aux_functions.cc menu.cc
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Indicate that the all and clean targets do not
# correspond to actual files.
.PHONY: all clean blank


# The clean target removes all of the executable files
# and object files produced by the build process
# We can use it for additional housekeeping purposes
clean :
	rm -rf *.o graph ../doc
	rm -rf *~ basura b i
	rm -rf a.out
	rm -rf *.md
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;

blank :
	rm -rf *s.md