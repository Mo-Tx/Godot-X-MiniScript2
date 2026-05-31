using Godot;
using System;
using MiniScript;
using static MiniScript.ValueHelpers;

public partial class Node2d : Node2D
{
	[Export]
	public string code = "";
	
	// Called when the node enters the scene tree for the first time.
	public override void _Ready()
	{
		//create interpreter
		var interp = new Interpreter();
	
		//interpreter outputs
		interp.standardOutput = (text, addNewline) => {
			GD.Print(text);
		};
		interp.errorOutput = (text, addNewline) => {
			GD.PrintErr(text);
		};

		//run code assigned by user (in inspector)
		interp.Reset(code);
		interp.Compile();
		if (interp.vm != null) interp.RunUntilDone();
		else GD.PrintErr("MiniScript interpreter VM not found!");
	}
	
	// Called every frame. 'delta' is the elapsed time since the previous frame.
	public override void _Process(double delta)
	{
	}
}
