#pragma once

#include <cstdint>
#include <utils/UUID.hpp>

namespace Engine {
  namespace Components {
    struct ID {
      UUID id;
      ID() = default;
      ID(UUID id) : id(id) {}
      ID(const ID&) = default;

      operator UUID() const { return this->id; }
      operator uint64_t() const { return this->id; }
    };
  }
}