
#include <CS_String.h>
#include <Interpreter.g.h>

#include "example_class.hpp"


void ExampleClass::_bind_methods()
{
	//godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &ExampleClass::print_type);
}

ExampleClass::ExampleClass() : interp(MiniScript::Interpreter::New(
	//source
	::String("print 'hello world'"),

	//standardOutput
	[](::String str, ::Boolean) -> void
	{
		godot::print_line(godot::String(str.c_str()));

	},

	//errorOutput
	[](::String str, ::Boolean) -> void
	{
		godot::print_error(godot::String(str.c_str()));

	}))
/*ExampleClass::ExampleClass()*/
{
	//Init MiniScript (TEMPORARY, TODO MAKE STATIC), Set source, compile and run interpeter on object initialization(construction)
	value_init_constants();
	MiniScript::GCManager::Init();
	MiniScript::ErrorType::Init();

	interp.Compile();
	interp.RunUntilDone(1.0, true);
}

/*### UNUSED ###*/
/*void ExampleClass::print_type(const Variant &p_variant) const
 {
	print_line(vformat("Type: %d", p_variant.get_type()));
	print_line("hello!");
}*/
