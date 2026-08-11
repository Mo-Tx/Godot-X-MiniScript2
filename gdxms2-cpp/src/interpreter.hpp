#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/variant.hpp>

#include <miniscript.h>

#include <string>

using namespace godot;

class Interpreter : public RefCounted {
	GDCLASS(Interpreter, RefCounted)

private:
	MiniScript::Interpreter interp;
	std::string source_code;

protected:
	static void _bind_methods();

public:
	Interpreter();
	~Interpreter() override = default;

	static void init_miniscript();

	void compile();
	void run_until_done(double time_limit, bool return_early);
;
	godot::String get_source_code() const;
	void set_source_code(const godot::String value);

	//void print_type(const Variant &p_variant) const;
};
