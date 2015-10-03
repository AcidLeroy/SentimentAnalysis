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

  void ProcessChars(const std::string &in, std::string &out, std::function<int(int)> func) {
    out = in; 
    std::for_each(out.begin(), out.end(), [&](char &c) {
        c = func(c); 
        });
  }

  void ToLower(const std::string &in, std::string &out) {
    std::function<int(int)> f = [](int c)->int{return std::tolower(c);}; 
    ProcessChars(in, out, f); 
  }
  
  void ToUpper(const std::string &in, std::string &out) {
    std::function<int(int)> f = [](int c)->int{return std::toupper(c);}; 
    ProcessChars(in, out, f); 
  }

  template <typename T> 
    void IterateLine(std::string &line, const std::vector<T> &funcs) {
      std::regex rgx("\\w+"); 
      auto words_begin = std::sregex_iterator(line.cbegin(), line.cend(), rgx);
      auto words_end = std::sregex_iterator(); 
      for(; words_begin != words_end; ++words_begin) {
        std::string out = words_begin->str();
        std::for_each(funcs.cbegin(), funcs.cend(),
            [&](const T &func) { func(out, out); 
            });
      }
    }
}

#endif //_SENTIMENT_ANALYSIS_PREPROCESSING_H_



