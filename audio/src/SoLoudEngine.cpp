#include "SoLoudEngine.h"
#include <soloud_thread.h>

SoLoudEngine::SoLoudEngine() {
  soloud.init();
}
SoLoudEngine::Clip* SoLoudEngine::getClip(std::string asset_path) {
  clips[asset_path] = std::make_shared<SoLoudEngine::Clip>(soloud);
  auto* clip = clips.at(asset_path).get();
  auto err = clip->wav.load(asset_path.c_str());
  if(err != 0)
    printf("Error loading sound asset: %s\n", asset_path.c_str());
  return clip;
}
void SoLoudEngine::Clip::play() {
  soloud.play(wav);
}
SoLoudEngine::Clip::Clip(SoLoud::Soloud &s) : soloud(s){

}
