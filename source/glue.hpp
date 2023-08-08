/**
 * @file glue.hpp
 * @author Alex Laing (livingearthcompany@gmail.com)
 * @brief Various functions for translating between GD and native (STL) forms.
 */

#include <circular/config_map.hpp>
#include <godot_cpp/classes/config_file.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <string>

#pragma once

namespace moho {
namespace glue {

inline std::string StlStringFromGodot(const godot::String &s);
inline godot::String GodotStringFromStl(const std::string &s);

circular::ConfigMap ConfigFileToMap(const godot::ConfigFile &f);
} // namespace glue
} // namespace moho