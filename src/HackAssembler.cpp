#include "code.h"
#include "parser.h"
#include "symbol_table.h"
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
  Assembler(string file) { filename = file; }
  void Start() {
    // TODO: first pass with symbol table
    //
    // this->second_pass();
    first_pass();
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

      if (!line.empty()) { // Only print non-empty lines
        Parser p(line);
        // TODO: implement parsing for A commands

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
        cout << bpad << bc << bd << bj << "\n";
      }
    }
    file.close();
  }
};

int main(int argc, char *argv[]) {
  Assembler a(argv[1]);
  a.Start();

  SymbolTable symbolTable;
  // Insert some new symbols
  symbolTable.insert("MY_VARIABLE", 100);
  cout << symbolTable.getValue("KBD");
  return 0;
};
