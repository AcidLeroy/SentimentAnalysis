#include <iostream>
#include <string> 
#include <regex>
#include <vector> 
#include <iterator> 
#include <sstream>

#include <gtest/gtest.h>

#include "preprocessing.h"

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

TEST(PreProcessing, RemoveWord) {
  const std::string word_to_remove{"this"}; 
  std::string test{"this Don't do ThiS to me this."}; 
  std::string output; 
  pp::RemoveWord(word_to_remove, test, output);
  ASSERT_EQ("Don't do to me.", output); 
}

TEST(PreProcessing, RemoveStopWords) {
  const std::vector<std::string> stop_words{"is", "sentence"}; 
  const std::string test_sentence{"This is my sentence"}; 
  const std::string expr{"(\\s*This\\s*my\\s*)"}; 
  std::regex truth(expr);
  std::string output; 
  pp::RemoveStopWords(stop_words, test_sentence, output); 
  bool match = std::regex_match(output.cbegin(), output.cend(), truth); 
  ASSERT_TRUE(match) << "Output is: '" << output 
  << "'. it should match this regex: " << expr << std::endl;; 
}
