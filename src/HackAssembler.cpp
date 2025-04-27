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
    // TODO: first pass with symbol table
    //
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
    // globalSymbolTable.printTable();
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
        // TODO: implement parsing for A commands
        Parser p(line);
        if (line[0] == '@') {
          // cout << line[0];
          if (std::isdigit(line[1])) {
            // cout << "number"
            //       "\n";
            string addr = line.erase(0, 1);
            // cout << addr;
            bitset<16> binary(stoi(addr));
            // cout << binary;
            outputFile << binary << "\n";
          } else {
            // cout << "not number" << "\n";
            string addr = line.erase(0, 1);
            // cout << "addr: " << addr;
            int val = globalSymbolTable.getValue(addr);
            // cout << "val: " << val;
            bitset<16> bbinary(val);
            // cout << "symbol" << addr << "binary" << bbinary << "\n";
            //  cout << "binary: " << bbinary << "\n";
            outputFile << bbinary << "\n";
          }
        } else if (line[0] != '(') {
          // For C commands, currently just runs on every line
          p.CParser();
          string c = p.comp;
          string d = p.dest;
          string j = p.jump;
          // cout << "line" << line << "\n";
          Code cc(c, "comp");
          bitset<7> bc = cc.lookupComp();
          // cout << "comp" << bc << '\n';
          Code dd(d, "dest");
          bitset<3> bd = dd.lookupDest();
          // cout << "dest" << bd << '\n';
          Code jj(j, "jump");
          bitset<3> bj = jj.lookupJump();
          // cout << "jump" << bj << '\n';
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
