##example node script using the "Interpreter" class
extends Node

@export var test_number : int

func _ready() -> void:	
	#Init all global MiniScript components(GC, constants, error types, ...) and set the stdout and stderr
	#In this case, they are the defaule godot stdout(print and push_error); but any method that takes a string will work
	Interpreter.init_miniscript(print, push_error)
	#create an interpreter object with its initial code set to the desired source code(to avoid reseting the interpreter after creation)
	var interp = Interpreter.create(
	#here we forcibly injected the variable in the source code since we don't have an I/O or value sharing API yet
	"test_number="+str(test_number)+
	"""
	factorial=funcion(x)
		if x==0 or x==1 or x==null then return 1
		mult=1
		for i in range(x, 2)
			mult*=i
		end for
		return mult
	end function
	print factorial(test_number)
	""")
	#compile the interpreter's source code
	interp.compile()
	#run it with a 2-second time limit and with early returns (read MiniScript docs for more details)
	interp.run_until_done(2.0, true)

	
