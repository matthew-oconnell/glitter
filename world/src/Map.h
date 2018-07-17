#pragma once
#include <tuple>
#include <map>
#include <Square.h>
namespace Glitter {
namespace World {
typedef std::tuple<int, int> MapIndex;

class Voxel {
 public:
  Voxel(Math::Vec2d world_lo, Math::Vec2d world_hi, std::array<GLfloat, 4> color = {1.0f, 1.0f, 1.0f, 1.0f});
  void render();
 private:
  Math::Vec2d world_lo, world_hi;
  Graphics::Square s;
};

class Map {
 public:
  Map(int voxels_wide, int voxels_high);
  void render();
 private:
  int voxels_wide, voxels_high;
  std::map<MapIndex, Voxel> voxels;
};
}
}


