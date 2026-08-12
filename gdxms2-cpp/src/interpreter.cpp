
#include <miniscript.h>

#include "interpreter.hpp"


void Interpreter::_bind_methods() {
	//### FUNCTIONS ###//
	//  STATIC //
	godot::ClassDB::bind_static_method("Interpreter", D_METHOD("init_miniscript"), &Interpreter::init_miniscript);
	godot::ClassDB::bind_static_method("Interpreter", D_METHOD("create", "source_code"), &Interpreter::create);

	//  MEMBER //
	godot::ClassDB::bind_method(D_METHOD("init", "source_code"), &Interpreter::init, DEFVAL(""));
	godot::ClassDB::bind_method(D_METHOD("compile"), &Interpreter::compile);
	godot::ClassDB::bind_method(D_METHOD("run_until_done", "time_limit", "return_early"), &Interpreter::run_until_done, DEFVAL(60.0), DEFVAL(true));

#if 0
	//### GETTERS/SETTERS ###//
	//  GETTERS  //
	godot::ClassDB::bind_method(D_METHOD("get_source_code"), &Interpreter::get_source_code);
	//  SETTERS //
	godot::ClassDB::bind_method(D_METHOD("set_source_code", "code"), &Interpreter::set_source_code);

	//### PROPERTIES ###///
	godot::ClassDB::add_property("Interpreter", godot::PropertyInfo(godot::Variant::STRING, "source_code"), "set_source_code", "get_source_code");

	//godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &Interpreter::print_type);
#endif
}

/*### CONSTRUCTORS/DESTRUCTORS ###*/
Interpreter::Interpreter(godot::String source_code) {
	init(source_code);
}

/*### FUNCTIONS ###*/
/*  STATIC */
void Interpreter::init_miniscript() {
	MiniScript::value_init_constants();
	MiniScript::GCManager::Init();
	MiniScript::ErrorTypes::Init();
}

Interpreter* Interpreter::create(godot::String source_code)
{
	return memnew(Interpreter(source_code));
}



/*  MEMBER */
void Interpreter::init(godot::String source_code) {
	//source_code = code.utf8();
	interp = MiniScript::Interpreter::New(
		//source
		MiniScript::String(source_code.utf8()),

		//standardOutput
		[](MiniScript::String str, MiniScript::Boolean) -> void {
			godot::print_line(godot::String(str.c_str()));

		},

		//errorOutput
		[](MiniScript::String str, MiniScript::Boolean) -> void {
			godot::print_error(godot::String(str.c_str()));

		}
	);
}

void Interpreter::reset(godot::String source_code)
{
	interp.Reset(MiniScript::String(source_code.utf8()));
}


void Interpreter::compile() {
	interp.Compile();
}

void Interpreter::run_until_done(double time_limit, bool return_early) {
	interp.RunUntilDone(time_limit, return_early);
}


#if 0
/*### GETTERS/SETTERS ###*/
/*  GETTERS  */
godot::String Interpreter::get_source_code() const {
	return godot::String(source_code.c_str());
}

/*  SETTERS  */
void Interpreter::set_source_code(const godot::String value) {
	source_code = std::string(value.utf8());
	interp.Reset(source_code.c_str());
}
#endif


/*### UNUSED ###*/
/*void Interpreter::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
	print_line("hello!");
}*/
