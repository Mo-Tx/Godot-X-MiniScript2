// miniscript_interpreter.hpp

#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/variant.hpp>

#include <miniscript.h>

using namespace godot;

class MiniScriptInterpreter : public RefCounted {
	GDCLASS(MiniScriptInterpreter, RefCounted)

private:
	MiniScript::Interpreter interp;
	/*static*/ godot::Callable _standard_output;
	/*static*/ godot::Callable _error_output;
	//std::string source_code;

protected:
	static void _bind_methods();

public:
	MiniScriptInterpreter(const godot::String source_code = "", const godot::Callable standard_output = godot::Callable(), const godot::Callable error_output = godot::Callable());
	~MiniScriptInterpreter() override = default;

	static void init_miniscript(/*const godot::Callable standard_output = godot::Callable(), const godot::Callable error_output = godot::Callable()*/);
	static MiniScriptInterpreter *create(const godot::String source_code = "", const godot::Callable standard_output = godot::Callable(), const godot::Callable error_output = godot::Callable());

	void init(const godot::String source_code = "", const godot::Callable standard_output = godot::Callable(), const godot::Callable error_output = godot::Callable());

	void reset(const godot::String source_code = "");
	void compile();
	void run_until_done(const double time_limit = 60.0, const bool return_early = true);

	/*static*/ void set_standard_output(const godot::Callable standard_output = Callable());
	/*static*/ void set_error_output(const godot::Callable error_output = Callable());

	godot::Variant get_global_value(const godot::String name = "");
	void set_global_value(const godot::String name = "", const godot::Variant value = godot::Variant());

#if 0
	godot::String get_source_code() const;
	void set_source_code(const godot::String value);
#endif
	//void print_type(const Variant &p_variant) const;
};
