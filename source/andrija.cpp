#include "andrija.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;
using namespace moho;

void moho::Adder::_bind_methods() {
    ClassDB::bind_static_method("Adder", D_METHOD("Add", "p_a", "p_b"), &Adder::Add);
}