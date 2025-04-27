#include "parser.h"
#include <string>
#include <sys/_types/_u_int16_t.h>

using namespace std;
Parser::Parser(string l) { line = l; }

void Parser::CParser() {
  size_t eqPos = line.find('=');
  size_t semiPos = line.find(';');

  // string::npos means not found
  // so if equals is found in the string, split the line up until but not
  // including it
  if (eqPos != string::npos) {
    this->dest = line.substr(0, eqPos);
  } else {
    this->dest = "null";
  }

  // if semicolon is found in the string
  if (semiPos != string::npos) {
    // start at the character after the equals, then split based on the
    // difference of the semi colon position equals position
    this->comp = line.substr(eqPos + 1, semiPos - eqPos - 1);
    this->jump = line.substr(semiPos + 1);
  } else {
    this->comp = line.substr(eqPos + 1); // No ';' means no jump part
    this->jump = "null";
  }
}
