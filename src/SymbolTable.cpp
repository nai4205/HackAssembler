#include "symbol_table.h"
#include <iostream>

SymbolTable::SymbolTable() {
  table["SP"] = 0;
  table["LCL"] = 1;
  table["ARG"] = 2;
  table["THIS"] = 3;
  table["THAT"] = 4;
  table["SCREEN"] = 16384;
  table["KBD"] = 24576;
  for (int i = 0; i <= 15; ++i) {
    table["R" + std::to_string(i)] = i;
  }
}

void SymbolTable::insert(std::string symbol, int value) {
  table[symbol] = value;
}

int SymbolTable::getValue(std::string symbol) {
  if (table.count(symbol)) {
    return table.at(symbol);
  } else {
    insertAtNextValue(symbol);
    return table.at(symbol);
  }
}

void SymbolTable::insertAtNextValue(std::string symbol) {
  static int nextAvailableValue =
      16; // Start from 16 because R0-R15 are reserved

  // Insert the symbol with the next available value
  table[symbol] = nextAvailableValue;

  // Increment the value for the next symbol
  nextAvailableValue++;
}

void SymbolTable::printTable() {
  for (auto it = table.cbegin(); it != table.cend(); ++it) {
    std::cout << it->first << it->second << " ";
  }
}
