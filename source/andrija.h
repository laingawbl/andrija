#pragma once

#include <godot_cpp/classes/object.hpp>

namespace moho {
class Adder : public godot::Object {
  GDCLASS(Adder, godot::Object)

public:
  static int Add(int a, int b) { return a + b; }

protected:
  static void _bind_methods();
};
} // namespace moho