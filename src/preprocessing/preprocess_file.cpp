// Usage example: 
// 
// ./preprocess_file ../files/stop_words.txt < .../files/input.txt > ../files/output.txt
//
// The above program loads stops words from a file and removes the stop
// words for the "input.txt" file and outputs it to the "output.txt" file. 
#include <vector> 
#include <string> 
#include <iostream> 
#include <fstream> 
#include <sys/stat.h>
#include <unistd.h>

#include "preprocessing.h"

void PrintUsage() {
  using namespace std; 
  cout << "The input parameters to this program are: \n" 
    << "1. The comma seperated file defining the stop words.\n" << std::endl;
}

bool FilePresent(const std::string &name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0);
}

std::vector<std::string> GetStopWords(const std::string &fname) {
  std::string line;
  std::ifstream myfile (fname);
  std::vector<std::string> stop_words; 
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      auto v = preprocessing::Split(line, ','); 
      stop_words.reserve(stop_words.size() + v.size()); 
      stop_words.insert(stop_words.end(), v.begin(), v.end()); 
    }
    myfile.close();
  }
  else std::cerr << "Unable to open the file " << fname <<  std::endl;

  return stop_words;
}

void RemoveStopWords(const std::vector<std::string>
    stop_words) {
  std::string line;
  while (std::cin) {
    while ( getline (std::cin, line) )
    {
      preprocessing::RemoveStopWords(stop_words, line, line); 
      std::cout << line << std::endl;
    }
  }
}


int main (int argc, char *argv[]) {
  if (argc != 2) {
    PrintUsage();
    return -1; 
  }

  const std::string comma_file{argv[1]};

  // Verify files are present
  std::vector<std::string> files_to_check{comma_file}; 
  std::for_each(files_to_check.cbegin(), files_to_check.cend(), [&](const std::string &s) {
      if (!FilePresent(s)){
      std::cerr << "File " << s << " is not present, exiting program..." << std::endl;
      std::exit(-1); 
      }
      });

  // Get stop word vector
  auto stop_words = GetStopWords(comma_file); 
  RemoveStopWords(stop_words);

}
