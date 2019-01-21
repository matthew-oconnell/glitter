#pragma once
#include <string>
#include <fstream>
#include <iostream>

namespace Glitter {
namespace Utilities {
inline std::string readFile(std::string name){
  std::ifstream t(name.c_str());
  if(t.fail()) throw std::logic_error("Could not load file " + name);
  std::string output;

  t.seekg(0, std::ios::end);
  output.reserve(t.tellg());
  t.seekg(0, std::ios::beg);

  output.assign((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());
  return output;
}
}
}


