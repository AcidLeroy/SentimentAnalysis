#ifndef _SENTIMENT_ANALYSIS_PREPROCESSING_H_
#define _SENTIMENT_ANALYSIS_PREPROCESSING_H_

#include <iostream>
#include <string> 
#include <regex>
#include <vector> 
#include <iterator> 
#include <sstream>

namespace preprocessing {
  void RemovePunctuation(const std::string &input, std::string &output) {
    std::regex words("[^A-Za-z\\s]");
    output = std::regex_replace(input, words, ""); 
  }

  std::vector<std::string> &Split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
      elems.push_back(item);
    }
    return elems;
  }

  std::vector<std::string> Split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    Split(s, delim, elems);
    return elems;
  }

  void RemoveWord(const std::string &word_to_remove, const std::string &input,
      std::string &output) {
      using namespace std::regex_constants;
    std::ostringstream oss; 
    oss << "(^" << word_to_remove << "\\b\\s*)";
    oss << "|(\\s*\\b" << word_to_remove << "\\b)";
    oss << "|(\\s*\\b" << word_to_remove << "\\b\\s*.$)";
    std::regex words(oss.str(), icase);
    output = std::regex_replace(input, words, ""); 

  }

  void RemoveStopWords(const std::vector<std::string> &stop_words, const std::string &input, std::string &output) 
  {
    output = input; 
    std::for_each(stop_words.begin(), stop_words.end(), [&](std::string stop_word) {
      RemoveWord(stop_word, output, output); 
    });
  }
}

#endif //_SENTIMENT_ANALYSIS_PREPROCESSING_H_
