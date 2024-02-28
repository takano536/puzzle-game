#include "FpsKeeper.hpp"

#include <SDL2/SDL.h>

FpsKeeper::FpsKeeper()
    : fps(0), frame_cnt(0) {
}

void FpsKeeper::wait() {
    frame_cnt++;
    SDL_Delay(get_wait_time());
    regist();
    if (frame_cnt == UPINTVL) {
        update_fps();
        frame_cnt = 0;
    }
}

double FpsKeeper::get_fps() {
    return fps;
}

void FpsKeeper::update_fps() {
    if (static_cast<int>(time_histories.size()) < HISTORIES_SIZE) {
        return;
    }
    int took_time = time_histories.back() - time_histories.front();
    double avg = static_cast<double>(took_time) / (HISTORIES_SIZE - 1);
    fps = 1000.0 / avg;
}

void FpsKeeper::regist() {
    time_histories.push_back(SDL_GetTicks());
    if (static_cast<int>(time_histories.size()) > HISTORIES_SIZE) {
        time_histories.pop_front();
    }
}

int FpsKeeper::get_wait_time() const {
    int hist_size = static_cast<int>(time_histories.size());
    if (hist_size == 0) {
        return 0;
    }
    int should_took_time = static_cast<int>(1000.0 / FPS * hist_size);
    int actual_took_time = SDL_GetTicks() - time_histories.front();
    int wait_time = should_took_time - actual_took_time;
    return wait_time > 0 ? wait_time : 0;
}