

#include <iostream>
#include <string> 
#include <regex>

#include <gtest/gtest.h>


namespace preprocessing {
  void RemovePunctuation(const std::string &input, std::string &output) {
    std::regex words("[^A-Za-z\\s]");
    output = std::regex_replace(input, words, ""); 

  }
}

namespace pp = ::preprocessing; 
TEST(PreProcessing, RemovePunctuation) {
  std::string input{",.a ,.,'b"}; 
  const std::string truth{"a b"}; 
  pp::RemovePunctuation(input, input);  
  ASSERT_STREQ(truth.c_str(), input.c_str()); 
}
