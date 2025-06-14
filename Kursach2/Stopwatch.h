#ifndef STOPWATCH_H  
#define STOPWATCH_H  

#include "Digital_counter.h"
#include <ctime>  

class Stopwatch : public Digital_counter {
private:  
  time_t start_time = 0;  
  int work_time = 0;  
  bool is_running = false;  

public:  
  Stopwatch() = default;  
  explicit Stopwatch(double time) : work_time(time), is_running(false) {}  
  void start();  
  void stop();  
  void reset();  
  void show() override;    
  int getResult() const;
};  

#endif
