#ifndef PARSER_H
#define PARSER_H

#include <cstdint>
#include <map>
#include <string>

using namespace std;

class Parser {
public:
  string line;
  static int lineNumber;
  string comp;
  string dest;
  string jump;
  Parser(string l);
  void LParser();
  void CParser();
};

#endif
