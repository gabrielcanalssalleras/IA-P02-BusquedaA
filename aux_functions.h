#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <utility>
#include <unordered_map>
#include <queue>

class Cell;
class Labyrinth;

#include "cell.h"

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

std::string VectorToString(std::vector<Cell> vector);

bool IsNodeValid(int row, int col, Labyrinth& labyrinth);

std::ofstream StoreSearch(Labyrinth& labyrinth, std::string& instance_name);

bool FoundInBranch(int node, std::vector<int> branch);

int GetRandomNumber(int min, int max);