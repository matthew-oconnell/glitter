#pragma once
#include "Window.h"
#include "Camera.h"
#include "GlewContext.h"
#include "GLFWInput.h"
#include "ModelDatabase.h"
#include <SoLoudEngine.h>

namespace Glitter {
class Engine {
 public:
  Engine();
  Window* getWindow();
  Camera* getCamera();
  GLFWInput* getInput();
  ModelDatabase* getModelDatabase();
  Audio* getAudioDatabase();
 private:
  Camera camera;
  Window window;
  GlewContext glew_context;
  GLFWInput input;
  ModelDatabase model_database;
  SoLoudEngine audio_databse;
};
}


