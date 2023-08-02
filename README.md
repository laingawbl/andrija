# andrija

This is `andrija`, a [GDExtension](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/index.html). It depends on [`libcircular`](https://github.com/laingawbl/circular) for some numeric stuff and is in turn used by [`micro-gaia`](https://github.com/laingawbl/micro-gaia).

## Building

To build, run `scons`.

To build and install to the Godot project, first make sure `GODOT_PROJECT_PATH` is correct in the file `SConstruct`. Then, run `scons install`.

There is no need to compile the `godot-cpp` submodule separately.
