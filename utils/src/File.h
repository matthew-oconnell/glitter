#pragma once
#include <string>
#include <fstream>
#include <iostream>

namespace Glitter {
namespace Utilities {
inline std::string readFile(std::string name){
  std::cout << "Reading file: " << name << std::endl;
  std::ifstream t(name.c_str());
  if(t.fail()) throw std::logic_error("Could not load file " + name);
  std::string output;

  t.seekg(0, std::ios::end);
  std::cout << "seek end" << std::endl;
  output.reserve(t.tellg());
  std::cout << "reserve" << std::endl;
  t.seekg(0, std::ios::beg);
  std::cout << "seek beg" << std::endl;

  std::cout << "assign" << std::endl;
  output.assign((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());

  std::cout << "Successfully read file: " << name << std::endl;
  return output;
}
}
}


