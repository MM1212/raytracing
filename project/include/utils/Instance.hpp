#pragma once

template <typename T>
class Instance {
public:
  static T* Get() {
    static T instance;
    return &instance;
  }
};