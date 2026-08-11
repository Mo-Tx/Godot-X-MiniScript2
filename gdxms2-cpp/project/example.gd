extends Node


func _ready() -> void:
	Interpreter.init_miniscript()
	var interp = Interpreter.new()
	interp.source_code = """print "hello world" """
	interp.compile()
	interp.run_until_done()
	
