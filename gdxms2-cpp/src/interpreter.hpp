#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/variant.hpp>

#include <miniscript.h>

//#include <string>

using namespace godot;

class Interpreter : public RefCounted {
	GDCLASS(Interpreter, RefCounted)

private:
	MiniScript::Interpreter interp;
	//std::string source_code;

protected:
	static void _bind_methods();

public:
	Interpreter(godot::String source_code = "");
	~Interpreter() override = default;

	static void init_miniscript();
	static Interpreter* create(godot::String source_code);

	void init(godot::String source_code);

	void reset(godot::String source_code);
	void compile();
	void run_until_done(double time_limit = 60.0, bool return_early = true);
#if 0
	godot::String get_source_code() const;
	void set_source_code(const godot::String value);
#endif
	//void print_type(const Variant &p_variant) const;
};
