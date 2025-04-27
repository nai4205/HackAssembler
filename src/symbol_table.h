#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <cstdint>
#include <map>
#include <string>

using BinaryValue = uint16_t;
using namespace std;

class SymbolTable {
public:
  SymbolTable();
  void insert(std::string symbol, int value);
  int getValue(std::string symbol);
  void insertAtNextValue(string symbol);
  void printTable();

private:
  std::map<std::string, int> table;
};

#endif
