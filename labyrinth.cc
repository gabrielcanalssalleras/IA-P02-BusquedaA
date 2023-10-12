#include "cell.h"

Labyrinth::Labyrinth(std::ifstream& input_file) {
  std::string line;
  std::getline(input_file, line);
  rows_ = std::stoi(line);
  std::getline(input_file, line);
  columns_ = std::stoi(line);
  for (int i = 0; i < rows_; i++) {
    std::vector<Cell> row;
    std::getline(input_file, line);
    for (int j = 0, k = 0; j < columns_; j++, k++) {
      if (line[k] == '3') {
        start_node_ = Cell(i, j, 3);
      } else if (line[k] == '4') {
        end_node_ = Cell(i, j, 4);
      }
      row.push_back(Cell(i, j, line[k++] - '0'));
    }
    labyrinth_.push_back(row);
  }
}

void Labyrinth::PrintLabyrinth() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      if (labyrinth_[i][j].GetKind() == 0) std::cout << "\033[1;37m■\033[0m ";
      else if (labyrinth_[i][j].GetKind() == 1) std::cout << "\033[1;30m■\033[0m ";
      else if (labyrinth_[i][j].GetKind() == 3) std::cout << "\033[1;32m■\033[0m ";
      else if (labyrinth_[i][j].GetKind() == 4) std::cout << "\033[1;33m■\033[0m ";
      //std::cout << labyrinth_[i][j].GetKind() << " ";
    }
    std::cout << "\n";
  }
}

void Labyrinth::ChangeNode(bool final) {
  int i_pos, j_pos;
  std::cout << "Enter the row of the node: ";
  std::cin >> i_pos;
  std::cout << "Enter the column of the node: ";
  std::cin >> j_pos;
  if (i_pos < 1 || i_pos > rows_ || j_pos < 1 || j_pos > columns_) {
    std::cerr << "The node is out of bounds. No changes applied.\n";
    return;
  }
  if (final) {
    std::pair<int, int> end_pos = end_node_.GetPos();
    Node(end_pos).SetKind(1);
    labyrinth_[i_pos - 1][j_pos - 1] = Cell(i_pos - 1, j_pos - 1, 4);
    end_node_ = Cell(i_pos - 1, j_pos - 1, 4);
  } else {
    std::pair<int, int> start_pos = start_node_.GetPos();
    Node(start_pos).SetKind(1);
    labyrinth_[i_pos - 1][j_pos - 1] = Cell(i_pos - 1, j_pos - 1, 3);
    start_node_ = Cell(i_pos - 1, j_pos - 1, 3);
  }
  std::cout << "The " << (final ? "final" : "initial") << " node has been set to"
            << " (" << i_pos << ", " << j_pos << ")\n";
}

void Labyrinth::PrintPath(std::vector<Cell> open_nodes, std::vector<Cell> closed_nodes, Cell current_node) const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      if (labyrinth_[i][j].GetKind() == 0) {
        if (std::find(closed_nodes.begin(), closed_nodes.end(), labyrinth_[i][j]) != closed_nodes.end())
          if (labyrinth_[i][j] == current_node) std::cout << "\033[1;32m■\033[0m ";
          else std::cout << "\033[1;34m■\033[0m ";
        else if (std::find(open_nodes.begin(), open_nodes.end(), labyrinth_[i][j]) != open_nodes.end())
          std::cout << "\033[1;35m■\033[0m ";
        else std::cout << "\033[1;37m■\033[0m ";
      }
        
      else if (labyrinth_[i][j].GetKind() == 1) std::cout << "\033[1;30m■\033[0m ";
      else if (labyrinth_[i][j].GetKind() == 3) std::cout << "\033[1;34m■\033[0m ";
      else if (labyrinth_[i][j].GetKind() == 4) std::cout << "\033[1;33m■\033[0m ";
      //std::cout << labyrinth_[i][j].GetKind() << " ";
    }
    std::cout << "\n";
  }
}

std::vector<Cell> Labyrinth::GetNeighbors(Cell node) const {
  std::vector<Cell> neighbors;
  std::pair<int, int> pos = node.GetPos();
  int i = pos.first, j = pos.second;
  Labyrinth labyrinth = *this;
  if (IsNodeValid(i - 1, j, labyrinth)) {
    neighbors.push_back(labyrinth_[i - 1][j]); // N
  } else neighbors.push_back(Cell(-1, -1, 1));
  if (IsNodeValid(i + 1, j, labyrinth)) {
    neighbors.push_back(labyrinth_[i + 1][j]); // S
  } else neighbors.push_back(Cell(-1, -1, 1));
  if (IsNodeValid(i, j - 1, labyrinth)) {
    neighbors.push_back(labyrinth_[i][j - 1]); // W
  } else neighbors.push_back(Cell(-1, -1, 1));
  if (IsNodeValid(i, j + 1, labyrinth)) {
    neighbors.push_back(labyrinth_[i][j + 1]); // E
  } else neighbors.push_back(Cell(-1, -1, 1));
  if (IsNodeValid(i - 1, j - 1, labyrinth)) {
    neighbors.push_back(labyrinth_[i - 1][j - 1]); // NW
  } else neighbors.push_back(Cell(-1, -1, 1));
  if (IsNodeValid(i - 1, j + 1, labyrinth)) {
    neighbors.push_back(labyrinth_[i - 1][j + 1]); // NE
  } else neighbors.push_back(Cell(-1, -1, 1));
  if (IsNodeValid(i + 1, j - 1, labyrinth)) {
    neighbors.push_back(labyrinth_[i + 1][j - 1]); // SW
  } else neighbors.push_back(Cell(-1, -1, 1));
  if (IsNodeValid(i + 1, j + 1, labyrinth)) {
    neighbors.push_back(labyrinth_[i + 1][j + 1]); // SE
  } else neighbors.push_back(Cell(-1, -1, 1));
  return neighbors;
}

Instance Labyrinth::AStarSearch() const {
  std::vector<Cell> open_nodes{GetStartNode()};
  Cell current_node = GetStartNode();
  std::vector<Cell> closed_nodes;
  std::vector<std::pair<std::vector<Cell>, int>> paths;
  current_node.CalculateHeuristic(GetEndNode());
  while (!open_nodes.empty()) {
    current_node = open_nodes[0];
    closed_nodes.push_back(current_node);
    open_nodes.erase(open_nodes.begin());
    std::cout << "Current node: " << current_node.GetPosString() << "\n";
    std::cout << "Generated: " << VectorToString(open_nodes) << "\n";
    if (current_node.GetKind() == 4) {
      paths.push_back(std::make_pair(closed_nodes, current_node.GetFValue()));
    }
    std::vector<Cell> neighbors = GetNeighbors(current_node);
    for (int i = 0; i < neighbors.size(); i++) {
      if (neighbors[i].GetPos() == std::make_pair(-1, -1)) continue;
      if (std::find(closed_nodes.begin(), closed_nodes.end(), neighbors[i]) != closed_nodes.end()) {
        continue;
      }
      if (std::find(open_nodes.begin(), open_nodes.end(), neighbors[i]) == open_nodes.end()) {
        neighbors[i].CalculateHeuristic(GetEndNode());
        neighbors[i].SetGValue(current_node.GetGValue() + 1);
        neighbors[i].SetFValue(neighbors[i].GetGValue() + neighbors[i].GetHValue());
        open_nodes.push_back(neighbors[i]);
      } else {
        if (neighbors[i].GetGValue() > current_node.GetGValue() + 1) {
          neighbors[i].SetGValue(current_node.GetGValue() + 1);
          neighbors[i].SetFValue(neighbors[i].GetGValue() + neighbors[i].GetHValue());
        }
      }
    }
    std::cout << "Generated: " << VectorToString(neighbors) << "\n";
    std::sort(open_nodes.begin(), open_nodes.end(), [](Cell a, Cell b) {
      return a.GetFValue() < b.GetFValue();
    });
    PrintPath(open_nodes, closed_nodes, current_node);
  }
  if (paths.empty()) {
    std::cerr << "No path found.\n";
    Instance table;
    return table;
  } else {
    std::pair<std::vector<Cell>, int> final_path;
    for (int i = 0; i < paths.size(); i++) {
      // Get the shortest path
      if (paths[i].second < final_path.second || final_path.second == 0) {
        final_path = paths[i];
      }
    }
    std::cout << "Final path: " << VectorToString(final_path.first) << "\n";
    return Instance{final_path.first, closed_nodes, open_nodes};
  }
}