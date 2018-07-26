#include <string>
#include <lodepng.h>
#include <File.h>
#include <Vector2d.h>
#include "Texture.h"
using namespace Glitter;
using namespace Glitter::Graphics;

Texture::Texture(std::string filename, float width, float height) :
    half_width(0.5f*width), half_height(0.5f*height),
    texture_handle(loadTexture(filename)) {

}

GLuint Texture::loadTexture(std::string filename){
  std::vector<unsigned char> image;
  unsigned error = lodepng::decode(image, width, height, filename);
  if(error != 0) {throw std::logic_error(lodepng_error_text(error));}

  u2 = 1; while(u2 < width) u2 *= 2;
  v2 = 1; while(v2 < height) v2 *= 2;
  // Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
  u3 = (double)width / u2;
  v3 = (double)height / v2;

  // Make power of two version of the image.
  std::vector<unsigned char> image2(u2 * v2 * 4);
  for(size_t y = 0; y < height; y++) {
    for (size_t x = 0; x < width; x++) {
      for (size_t c = 0; c < 4; c++) {
        image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
      }
    }
  }

  glGenTextures(1, &texture_handle);
  glBindTexture(GL_TEXTURE_2D, texture_handle);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
//  glDisable(GL_ALPHA_TEST);
//
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);
  glBindTexture(GL_TEXTURE_2D, 0);

  return texture_handle;
}
void Texture::render(Glitter::Math::Vec2d world_location, Glitter::Screen *s) {

  glColor4ub(255, 255, 255, 255);

  glBindTexture(GL_TEXTURE_2D, texture_handle);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  std::array<Math::Vec2d, 4> corners_world = {
      Math::Vec2d{-half_width+world_location.x,   half_width+world_location.y},
      Math::Vec2d{ half_width+world_location.x,   half_width+world_location.y},
      Math::Vec2d{ half_width+world_location.x,  -half_width+world_location.y},
      Math::Vec2d{-half_width+world_location.x,  -half_width+world_location.y}
  };
  for(auto& c : corners_world)
    c = s->convertWorldToRender(c);
  glTexCoord2d(0.0, 0.0); glVertex2f(corners_world[0].x , corners_world[0].y);
  glTexCoord2d( u3, 0.0); glVertex2f(corners_world[1].x , corners_world[1].y);
  glTexCoord2d( u3,  v3); glVertex2f(corners_world[2].x , corners_world[2].y);
  glTexCoord2d(0.0,  v3); glVertex2f(corners_world[3].x , corners_world[3].y);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}
std::tuple<Math::Vec2d, Math::Vec2d> Texture::getBounds() const {
  return {Math::Vec2d{-half_width, -half_height}, Math::Vec2d{half_width, half_height}};
}

