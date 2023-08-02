#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

GODOT_PROJECT_PATH = "../micro-gaia/bin"

# allow for colour output...
env["ENV"]["TERM"] = os.environ["TERM"]

# reigster headers
env.Append(
    CPPPATH=["/usr/local/include"]
)

# register static libraries
env.Append(LIBS=["libcircular"])

# register source files
source_dirs=[
    "source/",
    "source/register_types/"
]

env.Append(CPPPATH=source_dirs)
sources = [Glob(d + "*.cpp") for d in source_dirs]

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "build/libandrija.{}.{}.framework/libandrija.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "build/libandrija{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

# allow installing to the Godot project bin/ directory
env.Install(GODOT_PROJECT_PATH, library)
env.Alias('install', GODOT_PROJECT_PATH)

Default(library)