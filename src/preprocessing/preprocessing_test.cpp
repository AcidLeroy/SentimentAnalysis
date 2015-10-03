#include <iostream>
#include <string> 
#include <regex>
#include <vector> 
#include <iterator> 
#include <sstream>
#include <cctype>

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

TEST(PreProcessing, ToUpper) {
  std::string s{"lower"}; 
  std::function<int(int)> f = [](int c)->int{return std::toupper(c);}; 
  pp::ProcessChars(s, s, f); 
  ASSERT_STREQ("LOWER", s.c_str()); 
}

TEST(PreProcessing, ToLower) {
  std::string s{"UPPER"}; 
  std::function<int(int)> f = [](int c)->int{return std::tolower(c);}; 
  pp::ProcessChars(s, s, f); 
  ASSERT_STREQ("upper", s.c_str()); 
}


TEST(PreProcessing, IterateLine) 
{
  using func_type = std::function<void(const std::string&, std::string&)>; 
  std::vector<func_type> funcs; 

  func_type print_val = [] (const std::string &in, std::string &out) {
    out = in; 
    std::cout << "(" << in << ", 1)" << std::endl;
  };

  func_type to_upper = [] (const std::string &in, std::string &out) {
    pp::ToUpper(in, out);
  };

  funcs.push_back(to_upper); 
  funcs.push_back(print_val); 

  std::string s{"This, is, a single LINE!!!"}; 
  std::string truth{"(THIS, 1)\n"
  "(IS, 1)\n"
  "(A, 1)\n"
  "(SINGLE, 1)\n"
  "(LINE, 1)\n"};

  // Redirect cout.
  std::streambuf* old_buf = std::cout.rdbuf();
  std::ostringstream str_cout;
  std::cout.rdbuf( str_cout.rdbuf() );

  pp::IterateLine<func_type>(s, funcs); 

  // Restore old cout.
  std::cout.rdbuf( old_buf );

  ASSERT_STREQ(truth.c_str(), str_cout.str().c_str()); 
}

TEST(PreProcessing, RemoveStopWord) {
  const std::vector<std::string> stop_words{"is", "a"}; 
  std::string in1{"THIS"};
  std::string out; 
  pp::RemoveStopWord(in1, out, stop_words); 
  ASSERT_STREQ(in1.c_str(), out.c_str()); 
  
}

TEST(PreProcessing, PreprocessLine) {

  const std::string input{"This is a line. Documenting"}; 
  const std::vector<std::string> stop_words{"is", "a"}; 
  const std::string truth{"THIS\t1\nLINE\t1\nDOCUMENT\t1\n"};
  // Redirect cout.
  std::streambuf* old_buf = std::cout.rdbuf();
  std::ostringstream str_cout;
  std::cout.rdbuf( str_cout.rdbuf() );

  pp::PreprocessLine(input, stop_words); 

  // Restore old cout.
  std::cout.rdbuf( old_buf );

  ASSERT_STREQ(truth.c_str(), str_cout.str().c_str()); 
}

TEST(PreProcessing, StemWord) {
  std::string in{"Documenting"}; 
  std::string truth{"Document"};
  std::string out; 
  pp::StemWord(in, out); 
  ASSERT_STREQ(truth.c_str(), out.c_str()); 
}
