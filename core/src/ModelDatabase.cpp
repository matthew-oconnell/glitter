#include "ModelDatabase.h"
#include <vector>
#include <glDebug.h>
#include <lodepng.h>
void Glitter::ModelDatabase::loadTexture(std::string filename, unsigned int width, unsigned int height) {
  if(textures.count(filename))
    return;
  std::vector<unsigned char> image;
  GLuint texture_handle;
  unsigned error = lodepng::decode(image, width, height, filename);
  if(error != 0) {
    printf("ERROR: %s\n", lodepng_error_text(error));
    abort();
  }


  size_t u2, v2;
  u2 = 1; while(u2 < width) u2 *= 2;
  v2 = 1; while(v2 < height) v2 *= 2;
  // Ratio for power of two version compared to actual version, to render the non power of two image with proper size.

  // Make power of two version of the image.
  std::vector<unsigned char> image2(u2 * v2 * 4);
  for(size_t y = 0; y < height; y++) {
    for (size_t x = 0; x < width; x++) {
      for (size_t c = 0; c < 4; c++) {
        image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
      }
    }
  }

  glCheckError();
  glGenTextures(1, &texture_handle);
  glCheckError();
  glBindTexture(GL_TEXTURE_2D, texture_handle);
  glCheckError();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);
  glCheckError();
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  glCheckError();

  textures[filename] = texture_handle;
}
GLuint Glitter::ModelDatabase::getTextureHandle(std::string filename) {
  return textures.at(filename);
}
