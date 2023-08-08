#include "glue.hpp"

#include <variant>

using namespace moho;

// Helpers

circular::PodVariant GdVariantToPod(const godot::Variant &v) {
  switch (v.get_type()) {
  case godot::Variant::Type::BOOL:
    return bool(v);
  case godot::Variant::Type::INT:
    return int(v);
  case godot::Variant::Type::FLOAT:
    return double(v); // and not float
  case godot::Variant::Type::STRING:
    return glue::StlStringFromGodot(godot::String(v));
  default:
    return circular::PodVariant{};
  }
}

/**
 * @brief Translate a godot::Dictionary to a circular::VariantDict, doing two
 * transformations:
 * 1. eliding value types incompatible with circular::PodVariant, i.e. {bool,
 * int, double, std::string}.
 * 2. stringify()-ing all keys. This may result in aliasing.
 *
 * @param d The dictionary to transform.
 * @return circular::VariantDict
 */
circular::VariantDict GdDictToCircularDict(const godot::Dictionary &d) {
  circular::VariantDict vd{};
  auto keys = d.keys();
  vd.reserve(keys.size());
  for (int i = 0; i < keys.size(); i++) {
    auto stl_key = glue::StlStringFromGodot(keys[i].stringify());
    auto pod_val = GdVariantToPod(d.get(keys[i], godot::Variant{}));
    if (pod_val != circular::PodVariant{}) {
      vd.emplace(stl_key, pod_val);
    }
  }
  return vd;
}

/**
 * @brief Translate a godot::Array to a circular::VariantDict, transforming
 * incompatible value types to std::monostate{} (i.e., a null variant). This is
 * done instead of eliding them in order to preserve the indexes of non-null
 * elements.
 *
 * @param a The array to transform.
 * @return circular::VariantList
 */
circular::VariantList GdArrayToCircularList(const godot::Array &a) {
  circular::VariantList vl{};
  vl.reserve(a.size());
  for (int i = 0; i < a.size(); i++) {
    vl.push_back(GdVariantToPod(a[i]));
  }
  return vl;
}

circular::ConfigVariant GdVariantToConfigValue(const godot::Variant &v) {
  // Impl: it's tempting to reuse GdVariantToPod, but this requires some
  // template trickery to cast to the superset std::variant (see
  // https://stackoverflow.com/questions/47203255) that I think might confuse
  switch (v.get_type()) {
  case godot::Variant::Type::BOOL:
    return bool(v);
  case godot::Variant::Type::INT:
    return int(v);
  case godot::Variant::Type::FLOAT:
    return double(v); // and not float
  case godot::Variant::Type::STRING:
    return glue::StlStringFromGodot(godot::String(v));
  case godot::Variant::Type::ARRAY:
    return GdArrayToCircularList(godot::Array(v));
  case godot::Variant::Type::DICTIONARY:
    return GdDictToCircularDict(godot::Dictionary(v));
  default:
    return circular::ConfigVariant{};
  }
}

// Exports to header

std::string moho::glue::StlStringFromGodot(const godot::String &s) {
  const auto buf = s.to_utf8_buffer();
  if (buf.is_empty()) {
    return "";
  }
  return std::string{buf.ptr(), buf.ptr() + buf.size()};
}

godot::String moho::glue::GodotStringFromStl(const std::string &s) {
  godot::String g;
  g.parse_utf8(s.c_str(), s.length());
  return g;
}

circular::ConfigMap glue::ConfigFileToMap(const godot::ConfigFile &f) {
  circular::ConfigMap m{};
  for (auto section : f.get_sections()) {
    auto section_stl = StlStringFromGodot(section);
    for (auto key : f.get_section_keys(section)) {
      auto val = f.get_value(section, key);
      auto key_stl = StlStringFromGodot(key);
      m.set_value(section_stl, key_stl, GdVariantToConfigValue(val));
    }
  }
  return m;
}