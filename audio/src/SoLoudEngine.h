#include "Audio.h"
#include <map>
#include <soloud.h>
#include <soloud_wav.h>

class SoLoudEngine : public Glitter::Audio {
 public:
  class Clip : public Glitter::Audio::Clip {
   public:
    Clip(SoLoud::Soloud& s);
    void play() override;
   public:
    SoLoud::Soloud& soloud;
    SoLoud::Wav wav;
  };
  SoLoudEngine();
  ~SoLoudEngine();
  Clip* getClip(std::string asset_path) override;
 private:
  SoLoud::Soloud soloud;
  std::map<std::string, std::shared_ptr<Clip>> clips;
};


