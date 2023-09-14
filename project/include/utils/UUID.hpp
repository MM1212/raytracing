#pragma once

#include <cstdint>

class UUID {
public:
  UUID();
  UUID(uint64_t uuid);
  UUID(const UUID&) = default;
  UUID& operator=(const UUID&) = default;

  operator uint64_t() const { return this->handle; }
private:
  uint64_t handle;
};


namespace std {
  template <typename T> struct hash;

  template<>
  struct hash<UUID> {
    std::size_t operator()(const UUID& uuid) const
    {
      return (uint64_t)uuid;
    }
  };

}