#pragma once

#include <string>
#include <string_view>

namespace Engine {
  namespace Components {
    struct Tag {
      std::string name;

      Tag() = default;
      Tag(const Tag&) = default;
      Tag(std::string_view name)
        : name(name) {}
    };
  }
}