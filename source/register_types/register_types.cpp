#include "andrija.hpp"
#include "glue_test.hpp"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

// General note: the levels in ModuleInitializationLevel correspond to
// - the engine (CORE)
// - servers (SERVERS)
// - normal.. stuff...? (SCENE); and
// - editor-only (EDITOR).
// This is why we are init'ing Andrija at MODULE_INITIALIZATION_LEVEL_SCENE.

void initialize_andrija(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }

  ClassDB::register_class<moho::Adder>();
  ClassDB::register_class<moho::dummy::GlueTester>();
}

void uninitialize_andrija(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }
}

extern "C" {
GDExtensionBool GDE_EXPORT
andrija_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
             const GDExtensionClassLibraryPtr p_library,
             GDExtensionInitialization *r_initialization) {
  godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library,
                                                 r_initialization);

  init_obj.register_initializer(initialize_andrija);
  init_obj.register_terminator(uninitialize_andrija);
  init_obj.set_minimum_library_initialization_level(
      MODULE_INITIALIZATION_LEVEL_SCENE);

  return init_obj.init();
}
}