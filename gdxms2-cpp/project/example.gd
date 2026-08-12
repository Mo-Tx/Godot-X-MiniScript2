extends Node


func _ready() -> void:
	var i : int = 0
	var start_time := Time.get_ticks_msec()
	while true:
		i += 1
		if Time.get_ticks_msec()>=start_time+1000: break
	#end while
	print("GDScript result:", i)
	
	
	Interpreter.init_miniscript(print, push_error)
	var interp = Interpreter.create(
	"""
	i = 0
	while true
		i += 1
		if time >= 1 then break
	end while
	print "MiniScript result: "+i
	""")
	interp.compile()
	interp.run_until_done(2.0)

	
