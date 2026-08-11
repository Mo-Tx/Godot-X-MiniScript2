
#include <miniscript.h>

#include "interpreter.hpp"


void Interpreter::_bind_methods()
{
	//### FUNCTIONS ###//
	//  STATIC //
	godot:;ClassDB::bind_static_method("Interpreter", D_METHOD("init_miniscript"), &Interpreter::init_miniscript);

	//  MEMBER //
	godot::ClassDB::bind_method(D_METHOD("compile"), &Interpreter::compile);
	godot::ClassDB::bind_method(D_METHOD("run_until_done", "time_limit", "return_early"), &Interpreter::run_until_done, DEFVAL(60.0), DEFVAL(true));

	//### GETTERS/SETTERS ###//
	//  GETTERS  //
	godot::ClassDB::bind_method(D_METHOD("get_source_code"), &Interpreter::get_source_code);
	//  SETTERS //
	godot::ClassDB::bind_method(D_METHOD("set_source_code", "code"), &Interpreter::set_source_code);

	//### PROPERTIES ###///
	godot::ClassDB::add_property("Interpreter", godot::PropertyInfo(godot::Variant::STRING, "source_code"), "set_source_code", "get_source_code");

	//godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &Interpreter::print_type);
}

/*### CONSTRUCTORS/DESTRUCTORS ###*/
Interpreter::Interpreter() : interp(MiniScript::Interpreter::New(
	//source
	MiniScript::String(),

	//standardOutput
	[](MiniScript::String str, MiniScript::Boolean) -> void
	{
		godot::print_line(godot::String(str.c_str()));

	},

	//errorOutput
	[](MiniScript::String str, MiniScript::Boolean) -> void
	{
		godot::print_error(godot::String(str.c_str()));

	})), source_code()
/*Interpreter::Interpreter()*/
{
}

/*### FUNCTIONS ###*/
/*  STATIC */
void Interpreter::init_miniscript()
{
	MiniScript::value_init_constants();
	MiniScript::GCManager::Init();
	MiniScript::ErrorTypes::Init();
}

/*  MEMBER */
void Interpreter::compile()
{
	interp.Compile();
}

void Interpreter::run_until_done(double time_limit = 60.0, bool return_early = true)
{
	interp.RunUntilDone(time_limit, return_early);
}



/*### GETTERS/SETTERS ###*/
/*  GETTERS  */
godot::String Interpreter::get_source_code() const
{
	return godot::String(source_code.c_str());
}

/*  SETTERS  */
void Interpreter::set_source_code(const godot::String value)
{
	source_code = std::string(value.utf8());
	interp.Reset(source_code.c_str());
}


/*### UNUSED ###*/
/*void Interpreter::print_type(const Variant &p_variant) const
 {
	print_line(vformat("Type: %d", p_variant.get_type()));
	print_line("hello!");
}*/
