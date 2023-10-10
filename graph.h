/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Inteligencia Artificial
 * Curso: 3º
 * Práctica 1: Algoritmos de búsqueda. Búsquedas no informadas.
 * Autor: Gabriel Ángel Canals Salleras
 * Correo: alu0101460468@ull.edu.es
 * Fecha: 26/09/2023
 *
 * Archivo graph.h: Fichero de cabecera principal.
 * Contiene las llamadas a las distintas librerías del lenguaje C++ y 
 * la declaración de la clase Graph. También contiene las declaraciones 
 * de algunas funciones auxiliares.
 *
 * Referencias:
 * https://drive.google.com/file/d/15HKX9AdAv0_3KYwmYDA2VWz-riiimztK/view
 * Historial de revisiones
 * 26/09/2023 - Creación (primera versión) del código
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

const std::string kHelpText = "./graph -- Search algorithms. Uninformed Search. \n\
Usage: ./graph filein \n\
\n\
filein: File to read. \n\
\n\
This program reads a file, takes the representation of a graph \n\
and performs a search on it (Breadth First or Depth First)\n";


// Declaration of the Usage function
void Usage(int argc, char *argv[]);

struct Instance {
  std::vector<int> path;
  std::vector<int> visited;
  std::vector<int> generated;
};

class Graph {
 public:
  Graph(std::ifstream& input_file);
  ~Graph() = default;

  std::vector<std::pair<int, std::vector<double>>> GetNodes() const {return nodes_;}

  std::pair<int, std::vector<double>> GetNode(int node) const {return nodes_[node - 1];}

  double at(int i, int j) const {return nodes_[i].second[j];}

  int Size() const {return nodes_.size();}

  int EdgeCount() const;

  void PrintGraph() const;

  bool NodeExists(int node) const;

  Instance BreadthFirstSearch(int start_node, int end_node) const;

  Instance DepthFirstSearch(int start_node, int end_node) const;

  int CalculateCost(std::vector<int> path) const;

  int CountChildren(int node, std::vector<int> path) const;

  inline bool IsParent(int node, std::vector<int> path) const;

  inline bool IsNotEdge(int i, int j) const {
    int cost = at(i, j);
    return cost == 0 || cost == -1;
  }

  inline bool ShouldGoBackwards(std::stack<int> &stack, bool &come_back,
                                        std::vector<int> &branch) const;

 private:
  std::vector<std::pair<int, std::vector<double>>> nodes_;
};

int Menu(Graph& graph);

void BreadthFirstSearchMenu(Graph& graph);

void DepthFirstSearchMenu(Graph& graph);

std::ofstream StoreSearch(Graph& graph, int start_node, int end_node, bool depth_first);

bool FoundInBranch(int node, std::vector<int> branch);

int GetRandomNumber(int min, int max);