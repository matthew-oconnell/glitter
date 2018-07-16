#include "File.h"
#include <fstream>
#include <streambuf>
#include <utility>

using namespace Glitter;
using namespace Utilities;

std::string readFile(std::string name) {
  std::ifstream t(name.c_str());
  std::string output;

  t.seekg(0, std::ios::end);
  output.reserve(t.tellg());
  t.seekg(0, std::ios::beg);

  output.assign((std::istreambuf_iterator<char>(t)),
             std::istreambuf_iterator<char>());


  return output;
}
