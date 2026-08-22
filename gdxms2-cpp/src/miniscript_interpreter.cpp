// miniscript_interpreter.cpp

#include "miniscript_interpreter.hpp"
#include "gdxms2_converter.hpp"

#if 0
Callable *Interpreter::_standard_output = nullptr;
Callable *Interpreter::_error_output = nullptr;
#endif


void MiniScriptInterpreter::_bind_methods() {
	//### FUNCTIONS ###//
	//  STATIC //
	godot::ClassDB::bind_static_method("MiniScriptInterpreter", D_METHOD("init_miniscript"/*, "standard_output", "error_output"*/), &MiniScriptInterpreter::init_miniscript/*, DEFVAL(godot::Callable()), DEFVAL(godot::Callable())*/);

	godot::ClassDB::bind_static_method("MiniScriptInterpreter", D_METHOD("create", "source_code", "standard_output", "error_output"), &MiniScriptInterpreter::create, DEFVAL(""), DEFVAL(godot::Callable()), DEFVAL(godot::Callable()));

	godot::ClassDB::bind_method(/*"Interpreter", */D_METHOD("set_standard_output", "standard_output"), &MiniScriptInterpreter::set_standard_output, DEFVAL(godot::Callable()));
	godot::ClassDB::bind_method(/*"Interpreter", */D_METHOD("set_error_output", "error_output"), &MiniScriptInterpreter::set_error_output, DEFVAL(godot::Callable()));

	//  MEMBER //
	godot::ClassDB::bind_method(D_METHOD("init", "source_code", "standard_output", "error_output"), &MiniScriptInterpreter::init, DEFVAL(""), DEFVAL(godot::Callable()), DEFVAL(godot::Callable()));
	godot::ClassDB::bind_method(D_METHOD("reset", "source_code"), &MiniScriptInterpreter::reset);
	godot::ClassDB::bind_method(D_METHOD("compile"), &MiniScriptInterpreter::compile);
	godot::ClassDB::bind_method(D_METHOD("run_until_done", "time_limit", "return_early"), &MiniScriptInterpreter::run_until_done, DEFVAL(60.0), DEFVAL(true));
	//### GETTERS/SETTERS ###//
	//  GETTERS  //
	godot::ClassDB::bind_method(D_METHOD("get_global_value", "name"), &MiniScriptInterpreter::get_global_value);
	//  SETTERS //
	godot::ClassDB::bind_method(D_METHOD("set_global_value", "name", "value"), &MiniScriptInterpreter::set_global_value);
#if 0

	godot::ClassDB::bind_method(D_METHOD("get_source_code"), &Interpreter::get_source_code);
	//  SETTERS //
	godot::ClassDB::bind_method(D_METHOD("set_source_code", "code"), &Interpreter::set_source_code);

	//### PROPERTIES ###///
	godot::ClassDB::add_property("Interpreter", godot::PropertyInfo(godot::Variant::STRING, "source_code"), "set_source_code", "get_source_code");

	//godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &Interpreter::print_type);
#endif
}

/*### CONSTRUCTORS/DESTRUCTORS ###*/
MiniScriptInterpreter::MiniScriptInterpreter(godot::String source_code, godot::Callable standard_output, godot::Callable error_output) {
	init(source_code, standard_output, error_output);
}

/*### FUNCTIONS ###*/
/*  STATIC */
void MiniScriptInterpreter::init_miniscript(/*godot::Callable standard_output, godot::Callable error_output*/) {
	MiniScript::value_init_constants();
	MiniScript::GCManager::Init();
	MiniScript::ErrorTypes::Init();

#if 0
	Interpreter::_standard_output = new Callable(standard_output);
	Interpreter::_error_output = new Callable(error_output);
#endif

}

MiniScriptInterpreter *MiniScriptInterpreter::create(godot::String source_code, godot::Callable standard_output, godot::Callable error_output) {
	return memnew(MiniScriptInterpreter(source_code, standard_output, error_output));
}



/*  MEMBER */
void MiniScriptInterpreter::init(godot::String source_code, godot::Callable standard_output, godot::Callable error_output) {
	//source_code = code.utf8();
	interp = MiniScript::Interpreter::New(
			//source
			MiniScript::String(source_code.utf8()),

			//standardOutput
			[this](MiniScript::String str, MiniScript::Boolean) -> void {
				_standard_output.call(godot::String(str.c_str()));
				//godot::print_line(godot::String(str.c_str()));
			},

			//errorOutput
			[this](MiniScript::String str, MiniScript::Boolean) -> void {
				_error_output.call(godot::String(str.c_str()));
				//godot::print_error(godot::String(str.c_str()));
			});

	_standard_output=standard_output;
	_error_output=error_output;
}

void MiniScriptInterpreter::reset(godot::String source_code) {
	interp.Reset(MiniScript::String(source_code.utf8()));
}

void MiniScriptInterpreter::compile() {
	interp.Compile();
}

void MiniScriptInterpreter::run_until_done(double time_limit, bool return_early) {
	interp.RunUntilDone(time_limit, return_early);
}

/*### GETTERS/SETTERS ###*/
/*  GETTERS */
godot::Variant MiniScriptInterpreter::get_global_value(godot::String name) {
	return val_to_var(interp.GetGlobalValue(MiniScript::String(name.utf8())));
}

/*  SETTERS  */
void MiniScriptInterpreter::set_standard_output(godot::Callable standard_output) {
	_standard_output = standard_output;
}

void MiniScriptInterpreter::set_error_output(godot::Callable error_output) {
	_error_output = error_output;
}
void MiniScriptInterpreter::set_global_value(const godot::String name, const godot::Variant value) {
	interp.SetGlobalValue(MiniScript::String(name.utf8()), var_to_val(value));
}

#if 0
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
