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
 * Archivo p06_automata_simulator.cc: implementación.
 * Contiene implementación de los métodos de la clase Graph.
 *
 * Referencias:
 * https://drive.google.com/file/d/15HKX9AdAv0_3KYwmYDA2VWz-riiimztK/view
 */

#include "graph.h"


Graph::Graph(std::ifstream& input_file) : nodes_() {
  std::string line;
  getline(input_file, line);
  int num_nodes = std::stoi(line);
  for (int i = 1; i <= num_nodes; i++) {
    std::vector<double> distances(num_nodes, 0);
    nodes_.push_back(std::pair<int, std::vector<double>>(i, distances));
  }
  
  for (int i = 0, j = 1; getline(input_file, line); ++j) {
    if (j >= num_nodes) {
      i++;
      j = 0;
    }
    while (nodes_[i].second[j] != 0 || i == j) {
      ++j;
      if (j >= num_nodes) {
        i++;
        j = 0;
      }
    } 
    nodes_[i].second[j] = std::stod(line);
    nodes_[j].second[i] = std::stod(line);
  }
}

void Graph::PrintGraph() const {
    for (int i = 0; i < Size(); i++) {
      for (int j = 0; j < Size(); j++) {
        std::cout << "i: " << GetNodes()[i].first << " j: " 
                  << nodes_[j].first << " content: "<< this->at(i, j) << "\n";
    }
  } 
}

bool Graph::NodeExists(int node) const {
  for (int i = 0; i < Size(); i++) {
    if (nodes_[i].first == node) {
      return true;
    }
  }
  return false;
}

int Graph::EdgeCount() const {
  int count = 0;
  for (int i = 0; i < Size(); i++) {
    for (int j = 0; j < Size(); j++) {
      if (nodes_[i].second[j] != 0 && nodes_[i].second[j] != -1) {
        count++;
      }
    }
  }
  return count / 2;
}

int Graph::CalculateCost(std::vector<int> path) const {
  if (path.size() == 0) return 0;
  int cost = 0;
  for (int i = 0; i < path.size() - 1; i++) {
    cost += at(path[i] - 1, path[i + 1] - 1);
  }
  return cost;
}

inline bool Graph::IsParent(int node, std::vector<int> path) const {
  for (int i = 0; i < path.size(); i++) {
    if (path[i] == node) return true;
  }
  return false;
}

int Graph::CountChildren(int node, std::vector<int> path) const {
  int count = 0;
  std::vector<double> distances = GetNode(node).second;
    for (int j = 0; j < distances.size(); ++j) {
      if (distances[j] == 0 || distances[j] == -1) continue;
      ++count;
      if (IsParent(j + 1, path)) continue;
   
    }
  return count;
}

Instance Graph::BreadthFirstSearch(int start_node, int end_node) const {
  std::vector<std::vector<int>> parents;
  std::vector<int> generated, inspected, path;
  int final_pos = 0;
  generated.push_back(start_node);
  parents.push_back(std::vector<int>());
  for (int i = 0, node; generated[i] != end_node; i++) {
    node = generated[i];
    if (node == 0) return Instance{path, inspected, generated};
    inspected.push_back(node);
    std::vector<int> tree_branch = parents[i];
    std::vector<double> distances = GetNode(node).second;
    for (int j = 0; j < distances.size(); ++j) {
      if (distances[j] == 0 || distances[j] == -1) continue;
      if (IsParent(j + 1, tree_branch)) continue;
      generated.push_back(j + 1);
      if (j + 1 == end_node && final_pos == 0) final_pos = generated.size() - 1;
      parents.resize(generated.size());
      for (int parent : tree_branch) parents.back().push_back(parent);
      parents.back().push_back(node);
    }
  }
  path = parents[final_pos];
  path.push_back(end_node);
  return Instance{path, inspected, generated};
}

inline bool Graph::ShouldGoBackwards(std::stack<int> &stack, bool &come_back, 
                                              std::vector<int> &branch) const {
  if (branch.empty()) return true;
  std::vector<int> adjacent;
  for (int i = 0; i < GetNode(i + 1).second.size(); i++) {
    if (IsNotEdge(branch.back() - 1, i)) continue;
    adjacent.push_back(i + 1);
  }
  return std::find(adjacent.begin(), adjacent.end(), stack.top()) == adjacent.end();
}

Instance Graph::DepthFirstSearch(int start_node, int end_node) const {
  std::vector<int> branch, visited, generated{start_node};
  std::stack<int> stack{{start_node}};
  bool come_back = false;
  while (true) {
    int node = come_back ? branch.back() : stack.top();
    visited.push_back(node);
    stack.pop();
    branch.push_back(node);
    if (node == end_node) break;
    for (int i = GetNode(node).second.size() - 1; i >= 0; --i) {
      if (IsNotEdge(node - 1, i) || FoundInBranch(i + 1, branch)) continue;
      generated.push_back(i + 1);
      stack.push(i + 1);
    }
    if (stack.empty()) return Instance{{}, visited, generated};
    while (ShouldGoBackwards(stack, come_back, branch)) branch.pop_back();
  }
  return Instance{branch, visited, generated};
}