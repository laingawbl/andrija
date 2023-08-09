#pragma once

#include <circular/lib.hpp>
#include <godot_cpp/classes/object.hpp>

namespace moho {
class Adder : public godot::Object {
  GDCLASS(Adder, godot::Object)

public:
  static int Add(int a, int b) {
    // Impl: here's some chicanery to test interfacing with libcircular
    auto [mean, var] = circular::accumulate_vector(
        {static_cast<double>(a), static_cast<double>(b)});
    return static_cast<int>(mean * 2.0);
  }

protected:
  static void _bind_methods();
};
} // namespace moho