//============================================================================
// Name        : Mist_language.cpp
// Author      : Russell Mstowski
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

enum Token {
  tok_eof = -1,

  //commands
  tok_func = -2,
  tok_extern = -3,

  //primary
  tok_identifier = -4,
  tok_number = -5
};

static std::string IdentifierStr; //filled in if tok_identifier
static double NumVal;       //filled in if tok_number

static int gettok() {
  static int LastChar = ' ';

  //skip whitespace
  while (isspace(LastChar))
    LastChar = getchar();

  if (isalpha(LastChar)) {
    IdentifierStr = LastChar;
    while (isalnum((LastChar = getchar())))
        IdentifierStr += LastChar;

    if (IdentifierStr == "func")
      return tok_func;
    if (IdentifierStr == "extern")
      return tok_extern;
    return tok_identifier;
  }

  if (isdigit(LastChar) || LastChar == '.') {
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), 0);
    return tok_number;
  }

  //handle comments
  if (LastChar == '#') {
    do
      LastChar = getchar();
    while (LastChar != EOF && LastChar != '/n' && LastChar != '/r');

    if (LastChar != EOF)
      return gettok();
  }

  //check for end of file

  if (LastChar == EOF)
    return tok_eof;

  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;

}

int main() {
	cout << "!!!Mist Programming Language!!!" << endl;
	return 0;
}
