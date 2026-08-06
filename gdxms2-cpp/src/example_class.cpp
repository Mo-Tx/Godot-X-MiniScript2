
#include <miniscript.h>

#include "example_class.hpp"


void ExampleClass::_bind_methods()
{
	//godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &ExampleClass::print_type);
}

ExampleClass::ExampleClass() : interp(MiniScript::Interpreter::New(
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

	}))
/*ExampleClass::ExampleClass()*/
{
	godot::print_line("about to init constants");
	//Init MiniScript (TEMPORARY, TODO MAKE STATIC), Set source, compile and run interpeter on object initialization(construction)
	MiniScript::value_init_constants();
	godot::print_line("about to init GCManager");
	MiniScript::GCManager::Init();
	godot::print_line("about to init ErrorTypes");
	MiniScript::ErrorTypes::Init();
}

/*### UNUSED ###*/
/*void ExampleClass::print_type(const Variant &p_variant) const
 {
	print_line(vformat("Type: %d", p_variant.get_type()));
	print_line("hello!");
}*/
