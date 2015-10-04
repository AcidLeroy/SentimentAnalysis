/* Written by venkatesh jatla,
INPUT:
  <key, value>
  Ex:
    hope 1
    hope 1

OUTPUT:
    <key, value>
    hope 2

BUILDING:
  g++ -o reducer reducer.cpp

RUNNING:
  reducer <file name.txt>
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

/*
  TOKANIZER
  url: http://www.sbin.org/doc/HOWTO/C++Programming-HOWTO-7.html
*/
void Tokenize(const string& str,
                      vector<string>& tokens,
                      const string& delimiters = " ")
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}


/*
  Parse for <value> from mapper
*/
int parse_value(string CurLine,string& RefKey)
{
  vector<string> tokens;
  string cur_key, cur_value;
  Tokenize(CurLine, tokens);      // Tokenizing
  if(tokens.size() < 2)           // Input strings < 2 => return 0
    return 0;
  cur_key = tokens.at(0);
  cur_value = tokens.at(1);
  if(RefKey.empty())              // RefKey == NULL => cur_key = RefKey
    RefKey = cur_key;
  if(RefKey.compare(cur_key)==0)  // RefKey == cur_key, return cur_value
    return atoi(cur_value.c_str());
  else                            // RefKey ~= cur_key, return 0
    return 0;
}



int main(int argc, char* argv[])
{
  // Checing for input arguments
  int TotalValue = 0;
  string RefKey;
  string CurLine;
  while(getline(cin,CurLine))
  {
    TotalValue = TotalValue + parse_value(CurLine,RefKey);
  }
  cout<<RefKey<<" "<<TotalValue<<endl;
  return 0;
}
