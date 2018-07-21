#include "Map.h"

Glitter::World::Voxel::Voxel(Glitter::Math::Vec2d world_lo, Glitter::Math::Vec2d world_hi, std::array<GLfloat, 4> color)
    : world_lo(world_lo), world_hi(world_hi), s(1.0, 1.0, color){

}
void Glitter::World::Voxel::render(Screen* screen) {
  s.render((world_lo + world_hi)*0.5, screen);
}

Glitter::World::Map::Map(int voxels_wide, int voxels_high)
    : voxels_wide(voxels_wide), voxels_high(voxels_high){

  std::array<GLfloat, 4> white = {1.0f, 1.0f, 1.0f, 1.0f};
  std::array<GLfloat, 4> red = {1.0f, 0.1f, 0.1f, 1.0f};

  std::array<GLfloat, 4> color;
  for(int i = 0; i < voxels_wide; i++){
    for(int j = 0; j < voxels_high; j++){
      if(i % 2 == 0 && j % 2 == 0)
        color = red;
      else
        color = white;
      voxels.insert({{i, j},Voxel({float(i), float(j)}, {float(i+1), float(j+1)}, color)});
    }
  }
}
void Glitter::World::Map::render(Screen* screen) {
  for(auto& voxel_pair : voxels){
    voxel_pair.second.render(screen);
  }
}
