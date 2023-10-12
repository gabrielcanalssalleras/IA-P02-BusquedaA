#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

class Cell;
class Labyrinth;

#include "cell.h"

typedef std::pair<int, int> Position;
typedef std::vector<Cell> CellVector;

extern bool debug;

const std::string kBlueSquare = "\033[1;34m■\033[0m ";
const std::string kGreenSquare = "\033[1;32m■\033[0m ";
const std::string kYellowSquare = "\033[1;33m■\033[0m ";
const std::string kRedSquare = "\033[1;31m■\033[0m ";
const std::string kWhiteSquare = "\033[1;37m■\033[0m ";
const std::string kBlackSquare = "\033[1;30m■\033[0m ";
const std::string kCyanSquare = "\033[1;36m■\033[0m ";
const std::string kMagentaSquare = "\033[1;35m■\033[0m ";

const std::string kHelpText = "./graph -- Search algorithms. A* Search. \n\
Usage: ./graph filein \n\
\n\
filein: File to read. \n\
\n\
This program reads a file, takes the representation of a labyrinth \n\
and performs a search on it from start to end (A* algorithm)\n";

// Declaration of the Usage function
void Usage(int argc, char *argv[]);

int Menu(Labyrinth& labyrinth, std::string& filename);

std::string VectorToString(CellVector vector);

bool IsNodeValid(int row, int col, Labyrinth& labyrinth);

std::ofstream StoreSearch(Labyrinth& labyrinth, std::string& instance_name);

bool FoundInBranch(int node, std::vector<int> branch);

int GetRandomNumber(int min, int max);

CellVector ConstructPath(Cell current_node, Cell start_node,
                         std::vector<std::pair<Cell,Cell>> parents);