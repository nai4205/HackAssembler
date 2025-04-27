#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <cstdint>
#include <map>
#include <string>

using BinaryValue = uint16_t;

class SymbolTable {
public:
  SymbolTable();
  void insert(std::string symbol, int value);
  int getValue(std::string symbol);

private:
  std::map<std::string, int> table;
};

#endif
