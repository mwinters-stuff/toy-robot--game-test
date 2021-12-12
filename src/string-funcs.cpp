
#include "string-funcs.h"
#include <regex>
#include <vector>


// tokenize a string by whitespace and comma
std::vector<std::string> utils::tokenize(const std::string str) {
  auto re = std::regex("([\\s|,]+)");
  std::sregex_token_iterator it{str.begin(), str.end(), re, -1};
  std::vector<std::string> tokenized{it, {}};

  // Additional check to remove empty strings
  tokenized.erase(
      std::remove_if(tokenized.begin(), tokenized.end(),
                     [](std::string const &s) { return s.size() == 0; }),
      tokenized.end());

  return tokenized;
}

// split a string at the first space.
std::vector<std::string> utils::split(const std::string str) {
  std::vector<std::string> split;

  auto pos = str.find_first_of(" ");
  if(pos ==  std::string::npos){
    split.push_back(str);
  }else{
    split.push_back(str.substr(0,pos));
    split.push_back(str.substr(pos+1));
  }

  return split;
}
