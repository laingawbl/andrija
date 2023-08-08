#pragma once

#include <godot_cpp/classes/config_file.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/object.hpp>

namespace moho {
namespace dummy {
class GlueTester : public godot::Object {
  GDCLASS(GlueTester, godot::Object)

public:
  static godot::String RoundTripConvert(const godot::String &s);
  static void ConvertAndPrintConfigFile(godot::Ref<godot::ConfigFile> f);

protected:
  static void _bind_methods();
};
} // namespace dummy
} // namespace moho