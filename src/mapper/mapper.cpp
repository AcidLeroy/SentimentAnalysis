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

const std::vector<std::string> stop_words{
  "a","able","about","across","after","all","almost","also","am","among","an","and","any","are","as","at","be","because","been","but","by","can","cannot","could","dear","did","do","does","either","else","ever","every","for","from","get","got","had","has","have","he","her","hers","him","his","how","however","i","if","in","into","is","it","its","just","least","let","like","likely","may","me","might","most","must","my","neither","no","nor","not","of","off","often","on","only","or","other","our","own","rather","said","say","says","she","should","since","so","some","than","that","the","their","them","then","there","these","they","this","tis","to","too","twas","us","wants","was","we","were","what","when","where","which","while","who","whom","why","will","with","would","yet","you","your"};

void Mapper(const std::vector<std::string>
    stop_words) {
  std::string line;
  while (std::cin) {
    while ( getline (std::cin, line) )
    {
      preprocessing::PreprocessLine(line, stop_words); 
    }
  }
}


int main (int argc, char *argv[]) {

  Mapper(stop_words);

}
