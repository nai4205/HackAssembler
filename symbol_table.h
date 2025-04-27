#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <cstdint>
#include <map>
#include <string>

using BinaryValue = uint16_t;

class SymbolTable {
public:
  SymbolTable();
  void insert(std::string symbol, BinaryValue value);
  BinaryValue getValue(std::string symbol);

private:
  std::map<std::string, BinaryValue> table;
};

#endif
