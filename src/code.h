#ifndef CODE_H
#define CODE_H

#include "binary_constants.h"
#include <cstdint>
#include <map>
#include <string>

using namespace std;

class Code {
public:
  string part;
  string type;
  BinaryValue lookupComp();
  BinaryValue lookupDest();
  BinaryValue lookupJump();

  Code(string p, string t);
};

#endif
