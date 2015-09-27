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
    << "1. The comma seperated file defining the stop words.\n"
    << "2. The file from which to remove the stop words. \n" 
    << "3. The file to store the processed output." << endl;
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
    stop_words, const std::string &input_file, const std::string &output_file) {
  std::string line;
  std::ifstream infile (input_file);
  std::ofstream outfile; 
  outfile.open(output_file,
      std::ios::out| std::ios::trunc); 
  std::cout << "infile: " << infile.is_open() << std::endl;
  std::cout << "outfile: " << outfile.is_open() << std::endl;

  if (infile.is_open() && outfile.is_open())
  {
    while ( getline (infile,line) )
    {
      preprocessing::RemoveStopWords(stop_words, line, line); 
      outfile << line << "\n"; 
    }
    infile.close();
    outfile.close();
  }
  else std::cerr << "Unable to open the file " << input_file
    <<  " or : " << output_file << std::endl;
}


int main (int argc, char *argv[]) {
  if (argc != 4) {
    PrintUsage();
    return -1; 
  }

  const std::string comma_file{argv[1]};
  const std::string input_file{argv[2]};
  const std::string output_file{argv[3]};

  std::cout << "Comma seperated file is: " << comma_file << std::endl; 
  std::cout << "Processing file: " << input_file<< std::endl; 
  std::cout << "Outputing to file: " << output_file << std::endl;

  // Verify files are present
  std::vector<std::string> files_to_check{comma_file, input_file}; 
  std::for_each(files_to_check.cbegin(), files_to_check.cend(), [&](const std::string &s) {
      if (!FilePresent(s)){
      std::cerr << "File " << s << " is not present, exiting program..." << std::endl;
      std::exit(-1); 
      }
      });

  // Get stop word vector
  auto stop_words = GetStopWords(comma_file); 
  RemoveStopWords(stop_words, input_file, output_file);


}
