#pragma once

#include "Interpreter.g.h"

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

using namespace godot;

class ExampleClass : public RefCounted {
	GDCLASS(ExampleClass, RefCounted)

private:
	MiniScript::Interpreter interp;

protected:
	static void _bind_methods();

public:
	ExampleClass();
	~ExampleClass() override = default;

	void print_type(const Variant &p_variant) const;
};
