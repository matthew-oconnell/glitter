#pragma once
#include "Model.h"
namespace Glitter {
namespace Graphics {
class Line : public Model {
 public:
  Line(Math::Vec2d begin, Math::Vec2d end);
  void render(Math::Vec2d world_location, Screen *s) override;
  std::tuple<Math::Vec2d, Math::Vec2d> getBounds() const override;

 private:
  Math::Vec2d begin, end;
};
}
}
