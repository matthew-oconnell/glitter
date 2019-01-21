#include <catch.hpp>
#include <thread>
#include <Audio.h>
#include <SoLoudEngine.h>

TEST_CASE("Play simple Audio"){
  SoLoudEngine audio_engine;
  auto clip = audio_engine.getClip("assets/sound_effects/laser1.mp3");
  clip->play();
  std::this_thread::sleep_for(std::chrono::seconds(2));
}

