#ifndef BINARY_CONSTANTS_H
#define BINARY_CONSTANTS_H

#include <cstdint>
#include <map>
#include <string>

using BinaryValue = uint16_t;

extern const std::map<std::string, BinaryValue> compToBinary;
extern const std::map<std::string, BinaryValue> destToBinary;
extern const std::map<std::string, BinaryValue> jumpToBinary;

#endif
