#include <iostream>
#include <string> 
#include <regex>
#include <vector> 
#include <iterator> 
#include <sstream>

#include <gtest/gtest.h>


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

  void RemoveStopWords(const std::string &input, std::string &output) 
  {
  }



}

namespace pp = ::preprocessing; 
TEST(PreProcessing, RemovePunctuation) {
  std::string input{",.a ,.,'b"}; 
  const std::string truth{"a b"}; 
  pp::RemovePunctuation(input, input);  
  ASSERT_STREQ(truth.c_str(), input.c_str()); 
}

TEST(PreProcessing, MakeCommaVector) {
  const std::string input{"stop,word,cool"}; 
  const std::vector<std::string> output = pp::Split(input, ',');
  size_t i = 0; 
  ASSERT_EQ(3, output.size());
  ASSERT_EQ("stop", output[i++]); 
  ASSERT_EQ("word", output[i++]); 
  ASSERT_EQ("cool", output[i++]); 
}
