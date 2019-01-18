#include "Text.h"
#include <iostream>
#include <glDebug.h>

Glitter::Text::Text() {
    if (FT_Init_FreeType(&ft))
        throw std::logic_error("ERROR::FREETYPE: Could not init FreeType Library");

    FT_Face face;
    if (FT_New_Face(ft, "assets/fonts/AnonymousPro.ttf", 0, &face))
        throw std::logic_error("ERROR::FREETYPE: Failed to load font");
    FT_Set_Pixel_Sizes(face, 0, 48);
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
        throw std::logic_error("ERROR::FREETYTPE: Failed to load Glyph");

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    printf("initializing character map"); fflush(stdout);
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
                texture,
                {face->glyph->bitmap.width, face->glyph->bitmap.rows},
                {face->glyph->bitmap_left, face->glyph->bitmap_top},
                face->glyph->advance.x
        };
        characters.insert(std::pair<GLchar, Character>(c, character));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void Glitter::Text::renderText(Graphics::Shader &s, const std::string& text,
                GLfloat x, GLfloat y,
                GLfloat scale,
                std::array<GLfloat, 4> color){

    // Activate corresponding render state
    glCheckError();
    s.enable();
    glCheckError();
    glUniform3f(glGetUniformLocation(s.getId(), "textColor"), color[0], color[1], color[2]);
    glCheckError();
    glActiveTexture(GL_TEXTURE0);
    glCheckError();
    glBindVertexArray(VAO);
    glCheckError();

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = characters[*c];

        GLfloat xpos = x + ch.bearing[0] * scale;
        GLfloat ypos = y - (ch.size[1] - ch.bearing[1]) * scale;

        GLfloat w = ch.size[0] * scale;
        GLfloat h = ch.size[1] * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.texture_id);
        glCheckError();
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glCheckError();
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glCheckError();
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glCheckError();
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glCheckError();
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance_offset >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glCheckError();
    glBindTexture(GL_TEXTURE_2D, 0);
    glCheckError();
}

