#include "glue_test.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <iostream>

#include "glue.hpp"

using namespace godot;
using namespace moho;

String dummy::GlueTester::RoundTripConvert(const String &s) {
  auto stl = glue::StlStringFromGodot(s);
  return glue::GodotStringFromStl(stl);
}

void dummy::GlueTester::ConvertAndPrintConfigFile(Ref<ConfigFile> f) {
  auto f_conv = glue::ConfigFileToMap(*f.ptr());
  for (const auto s : f_conv.get_sections()) {
    for (const auto k : f_conv.get_section_keys(s)) {
      std::cout << std::boolalpha << s << " .\t" << k << "\t\n";
      // If and only if this needs debugging in future, write a std::variant
      // visitor to print values and call it here.
    }
  }
}

void dummy::GlueTester::_bind_methods() {
  ClassDB::bind_static_method("GlueTester", D_METHOD("RoundTripConvert", "s"),
                              &GlueTester::RoundTripConvert);
  ClassDB::bind_static_method("GlueTester",
                              D_METHOD("ConvertAndPrintConfigFile", "f"),
                              &GlueTester::ConvertAndPrintConfigFile);
}