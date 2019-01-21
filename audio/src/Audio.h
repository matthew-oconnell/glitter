#pragma once
#include <string>
namespace Glitter {
class Audio {
 public:
  class Clip {
   public:
    virtual void play() = 0;
  };
  virtual Clip* getClip(std::string asset_path) = 0;
};
}


