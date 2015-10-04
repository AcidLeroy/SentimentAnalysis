// Usage example: 
// mapper < foo.txt > output.txt
// 
#include <vector> 
#include <string> 
#include <iostream> 
#include <fstream> 
#include <sys/stat.h>
#include <unistd.h>

#include "preprocessing.h"


void Mapper() {
  std::string line;
  while (std::cin) {
    while ( getline (std::cin, line) )
    {
      preprocessing::PreprocessLine(line, preprocessing::stop_words); 
    }
  }
}


int main (int argc, char *argv[]) {

  Mapper();

}
