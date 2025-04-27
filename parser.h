#ifndef PARSER_H
#define PARSER_H

#include <cstdint>
#include <map>
#include <string>

using namespace std;

class Parser {
public:
  string line;
  string comp;
  string dest;
  string jump;
  Parser(string l);
  void CParser();
};

#endif
