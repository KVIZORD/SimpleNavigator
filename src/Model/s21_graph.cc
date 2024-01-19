#define _CRT_SECURE_NO_WARNINGS
#include "s21_graph.h"

using namespace s21;

Graph::Graph(size_t size)
    : matrix_(
          std::vector<std::vector<size_t>>(size, std::vector<size_t>(size, 0))),
      size_(size) {}

Graph::Graph(size_t size, size_t init_value)
    : matrix_(std::vector<std::vector<size_t>>(
          size, std::vector<size_t>(size, init_value))),
      size_(size) {}

void Graph::SetValue(size_t row, size_t column, size_t value) {
  if (row >= size_ || column >= size_) {
    throw std::out_of_range("Cell index is out of range");
  }

  matrix_[row][column] = value;
}

std::vector<std::vector<size_t>>& Graph::GetData() { return matrix_; }

size_t Graph::GetValue(size_t row, size_t column) const {
  if (row >= size_ || column >= size_) {
    throw std::out_of_range("Cell index is out of range");
  }
  return matrix_[row][column];
}

size_t Graph::GetSize() const { return size_; }

std::vector<size_t> Graph::GetNeighbors(size_t from) const {
  if (from >= size_) {
    throw std::out_of_range("Cell index is out of range");
  }

  std::vector<size_t> neighbors;
  for (size_t to = 0; to < size_; ++to) {
    if (from != to && matrix_[from][to] != 0) {
      neighbors.push_back(matrix_[from][to]);
    }
  }

  return neighbors;
}

void Graph::LoadGraphFromFile(std::string filename) {
  std::ifstream in;
  in.open(filename);
  if (in.is_open()) {
    Reset();
    std::string line;
    bool first_line = true;
    size_t row = 0;
    while (std::getline(in, line)) {
      if (first_line) {
        ParseSize(line);
        first_line = false;
      } else if (!line.empty()) {
        if (row >= size_) throw std::out_of_range("The matrix is wrong");
        ParseLine(line, row);
        ++row;
      }
    }
    if (row < size_)
      throw std::length_error("The matrix has less rows than size");
  } else {
    throw std::runtime_error("File not found");
  }
  in.close();
}

void Graph::ExportGraphToDot(std::string filename) const {
  std::ofstream out;
  out.open(filename);
  if (out.is_open()) {
    out << "graph graphname {" << std::endl;
    for (size_t i = 0; i < size_; i++) {
      for (size_t j = i; j < size_; j++) {
        if (matrix_[i][j]) {
          out << "vertex" << i + 1 << " -- vertex" << j + 1 << std::endl;
        }
      }
    }
    out << "}";
  }
  out.close();
}

bool s21::Graph::GraphIsEmpty() const { return size_ == 0; }

void Graph::ParseSize(std::string line) {
  int size = std::stoi(line);
  if (size == 0) throw std::invalid_argument("The matrix has size zero");
  if (size < 0) throw std::invalid_argument("The matrix has incorrect size");
  size_ = size;
}

void Graph::ParseLine(std::string line, size_t row) {
  size_t column = 0;
  char* token = strtok(const_cast<char*>(line.c_str()), " ");
  std::vector<size_t> r;
  matrix_.push_back(r);
  while (token != nullptr) {
    if (column >= size_) throw std::out_of_range("The matrix is wrong");
    matrix_[row].push_back(std::stoi(token));
    token = strtok(nullptr, " ");
    ++column;
  }
  if (column < size_)
    throw std::length_error("The matrix has less columns than size");
}

void Graph::print() const {
  std::cout << "Матрица смежности: " << std::endl;
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      std::cout << std::setw(4) << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void s21::Graph::Reset() {
  if (matrix_.size()) matrix_.clear();
  size_ = 0;
}
