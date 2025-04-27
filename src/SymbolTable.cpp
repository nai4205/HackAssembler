#include "symbol_table.h"

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

void SymbolTable::insert(std::string symbol, BinaryValue value) {
  table[symbol] = value;
}

BinaryValue SymbolTable::getValue(std::string symbol) {
  if (table.count(symbol)) {
    return table.at(symbol);
  } else {
    throw std::out_of_range("Symbol '" + symbol + "' not found in the table.");
  }
}
