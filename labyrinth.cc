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
  if (final) {
    std::pair<int, int> end_pos = end_node_.GetPos();
    Node(end_pos).SetKind(1);
    labyrinth_[i_pos][j_pos] = Cell(i_pos, j_pos, 4);
    end_node_ = Cell(i_pos, j_pos, 4);
  } else {
    std::pair<int, int> start_pos = start_node_.GetPos();
    Node(start_pos).SetKind(1);
    labyrinth_[i_pos][j_pos] = Cell(i_pos, j_pos, 3);
    start_node_ = Cell(i_pos, j_pos, 3);
  }
  std::cout << "The " << (final ? "final" : "initial") << " node has been set to"
            << " (" << i_pos << ", " << j_pos << ")\n";
}