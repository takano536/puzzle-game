#pragma once

template <typename T>
class Singleton {
  protected:
    Singleton() = default;
    virtual ~Singleton() = default;
    Singleton(const Singleton &) = default;
    Singleton &operator=(const Singleton &) = default;

  public:
    static T &get_instance() {
        static T instance;
        return instance;
    }
};