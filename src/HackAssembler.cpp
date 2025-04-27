#include "code.h"
#include "parser.h"
#include "symbol_table.h"
#include "symbol_table_instance.h"
#include <bitset>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/_types/_u_int16_t.h>
using namespace std;

class Assembler {
public:
  string filename;
  ofstream outputFile;
  Assembler(string file) {
    filename = file;
    outputFile.open("output.txt");
    if (!outputFile.is_open()) {
      cerr << "Failed to open output file\n";
    }
  }
  ~Assembler() {
    if (outputFile.is_open()) {
      outputFile.close(); // Close the file when done
    }
  }
  void Start() {
    first_pass();
    second_pass();
  }
  void first_pass() {

    ifstream file(filename);
    ostringstream result;
    string line;

    if (!file.is_open()) {
      cerr << "Failed to open file: " << filename << "\n";
    }

    while (getline(file, line)) {
      // Remove comments
      size_t commentPos = line.find("//");
      if (commentPos != string::npos) {
        line = line.substr(0, commentPos);
      }
      // Remove trailing whitespace from the line (optional but nicer)
      line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);

      if (!line.empty()) { // Only print non-empty lines
        Parser p(line);
        p.LParser();
      }
    }
    file.close();
  }
  void second_pass() {
    ifstream file(filename);
    ostringstream result;
    string line;

    if (!file.is_open()) {
      cerr << "Failed to open file: " << filename << "\n";
    }
    while (getline(file, line)) {
      // Remove comments
      size_t commentPos = line.find("//");
      if (commentPos != string::npos) {
        line = line.substr(0, commentPos);
      }
      // Remove trailing whitespace from the line (optional but nicer)
      line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
      line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
      if (!line.empty()) { // Only print non-empty lines
        Parser p(line);
        if (line[0] == '@') {
          if (std::isdigit(line[1])) {
            string addr = line.erase(0, 1);
            bitset<16> binary(stoi(addr));
            outputFile << binary << "\n";
          } else {
            string addr = line.erase(0, 1);
            int val = globalSymbolTable.getValue(addr);
            bitset<16> bbinary(val);
            outputFile << bbinary << "\n";
          }
        } else if (line[0] != '(') {
          // For C commands, currently just runs on every line
          p.CParser();
          string c = p.comp;
          string d = p.dest;
          string j = p.jump;
          Code cc(c, "comp");
          bitset<7> bc = cc.lookupComp();
          Code dd(d, "dest");
          bitset<3> bd = dd.lookupDest();
          Code jj(j, "jump");
          bitset<3> bj = jj.lookupJump();
          bitset<3> bpad = 0b111;
          outputFile << bpad << bc << bd << bj << "\n";
        }
      }
    }
    file.close();
  }
};

int main(int argc, char *argv[]) {
  Assembler a(argv[1]);
  a.Start();
  globalSymbolTable.printTable();
  return 0;
};
