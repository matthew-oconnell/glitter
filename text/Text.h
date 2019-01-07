#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <array>
#include <map>
#include <GL/glew.h>
#include <Shader.h>

namespace Glitter {
  class Text {
  public:
      Text();
      void renderText(Graphics::Shader &s, const std::string& text,
                      GLfloat x, GLfloat y,
                      GLfloat scale,
                      std::array<GLfloat, 4> color);

  private:
      struct Character {
          GLuint texture_id;
          std::array<unsigned int, 2> size;
          std::array<FT_Int, 2> bearing;    // Offset from baseline to left/top of glyph
          FT_Pos advance_offset;    // Offset to advance to next glyph
      };
      FT_Library ft;
      std::map<GLchar, Character> characters;
      unsigned int VAO, VBO;

  };

}
