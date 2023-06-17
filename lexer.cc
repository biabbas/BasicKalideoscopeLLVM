//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//
#include "lexer.h"

          

class LexicalAnalyzer
{
private:
  int gettok();
  FILE* f = NULL;
  int getCh();
public:
  LexicalAnalyzer(){}
 LexicalAnalyzer(FILE* fin);
  ~LexicalAnalyzer(){fprintf(stderr,"Deconstruct");}
  int CurTok;
  union{
  std::string IdentifierStr; 
  double NumVal;  
  };
  int NextToken();
};

LexicalAnalyzer::LexicalAnalyzer(FILE* fin){
  if(fin == NULL)
  fprintf(stderr,"Error Opening File\n");
  else
  f = fin;
}

int LexicalAnalyzer::NextToken(){

  CurTok = gettok();
  return CurTok;
}
int LexicalAnalyzer::getCh(){
  if(f==NULL)
  return getchar();
  else
  return getc(f);
}
int LexicalAnalyzer::gettok(){
  static int LastChar = ' ';

  // Skip any whitespace.
  while (isspace(LastChar))
    LastChar = getCh();
  if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
    IdentifierStr = LastChar;
    while (isalnum((LastChar = getCh())))
      IdentifierStr += LastChar;

    if (IdentifierStr == "def")
      return tok_def;
    if (IdentifierStr == "extern")
      return tok_extern;
    if (IdentifierStr == "if")
  return tok_if;
    if (IdentifierStr == "then")
  return tok_then;
    if (IdentifierStr == "else")
  return tok_else;
    if (IdentifierStr == "for")
  return tok_for;
if (IdentifierStr == "in")
  return tok_in;
    return tok_identifier;
  }

  if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getCh();
    } while (isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), nullptr);
    return tok_number;
  }

  if (LastChar == '#') {//comments
    do
      LastChar = getCh();
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF)
      return gettok();
  }


  if (LastChar == EOF)
    return tok_eof;

  int ThisChar = LastChar;
  LastChar = getCh();
  return ThisChar;
}
