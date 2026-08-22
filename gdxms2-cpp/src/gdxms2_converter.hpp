// gdxms2_converter.hpp

#pragma once

#include <godot_cpp/variant/variant.hpp>

#include <miniscript.h>


[[nodiscard]]
MiniScript::Value var_to_val(godot::Variant v);

[[nodiscard]]
godot::Variant val_to_var(MiniScript::Value v);

