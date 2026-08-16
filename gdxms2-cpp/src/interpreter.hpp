#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/variant.hpp>

#include <miniscript.h>

using namespace godot;

class Interpreter : public RefCounted {
	GDCLASS(Interpreter, RefCounted)

private:
	MiniScript::Interpreter interp;
	static godot::Callable *_standard_output;
	static godot::Callable *_error_output;
	//std::string source_code;

protected:
	static void _bind_methods();

public:
	Interpreter(const godot::String source_code = "");
	~Interpreter() override = default;

	static void init_miniscript(const godot::Callable standard_output = godot::Callable(), const godot::Callable error_output = godot::Callable());
	static Interpreter *create(const godot::String source_code = "");

	static void set_standard_output(const godot::Callable standard_output = Callable());
	static void set_error_output(const godot::Callable error_output = Callable());

	void init(const godot::String source_code = "");

	void reset(const godot::String source_code = "");
	void compile();
	void run_until_done(const double time_limit = 60.0, const bool return_early = true);
#if 0
	godot::String get_source_code() const;
	void set_source_code(const godot::String value);
#endif
	//void print_type(const Variant &p_variant) const;
};
