#pragma once

#include <list>

class FpsKeeper final {
  public:
    FpsKeeper();
    void wait();
    double get_fps();

  private:
    const static int FPS = 60;                  // FPS
    const static int UPINTVL = FPS;             // UPINTVLフレームごとにFPSを更新
    const static int HISTORIES_SIZE = FPS * 2;  // FPSを計算するための履歴数(2以上)

    std::list<int> time_histories;
    double fps;
    int frame_cnt;

    void update_fps();
    void regist();
    int get_wait_time() const;
};