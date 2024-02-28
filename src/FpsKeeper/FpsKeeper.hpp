#pragma once

#include <list>

class FpsKeeper final {
  public:
    FpsKeeper();
    void wait();
    double get_fps();

  private:
    std::list<int> time_histories;
    double fps;
    int frame_cnt;

    void update_fps();
    void regist();
    int get_wait_time() const;
};