
namespace Glitter {
namespace Utilities {
class FPSCounter {
 public:
  inline FPSCounter() {
    begin = std::chrono::system_clock::now();
    frame_count = 0;
  }
  inline void frame(){
    frame_count++;
  }

  inline double fps() {
    auto now = std::chrono::system_clock::now();
    auto fps_counter_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin);
    double f = frame_count / (fps_counter_time.count()/1000.0);
    if(fps_counter_time.count() > 1000.0){
      reset();
    }
    return f;
  }

 private:
  std::chrono::time_point<std::chrono::system_clock> begin;
  unsigned int frame_count;

  inline void reset() {
    begin = std::chrono::system_clock::now();
    frame_count = 0;
  }
};
}
}


