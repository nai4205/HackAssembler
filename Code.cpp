
#include "code.h"
#include "binary_constants.h"
#include <string>

using namespace std;

Code::Code(string p, string t) {
  part = p;
  type = t;
  if (part.empty())
    return;
}

BinaryValue Code::lookupComp() {
  auto it = compToBinary.find(this->part);
  if (it != compToBinary.end()) {
    return it->second;
  }
  return 0;
}
BinaryValue Code::lookupDest() {
  auto it = destToBinary.find(this->part);
  if (it != destToBinary.end()) {
    return it->second;
  }
  return 0;
}
BinaryValue Code::lookupJump() {
  auto it = jumpToBinary.find(this->part);
  if (it != jumpToBinary.end()) {
    return it->second;
  }
  return 0;
}
