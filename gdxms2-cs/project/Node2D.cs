using Godot;
using System;
using MiniScript;

public class Node2D : Godot.Node2D
{
	[Export]
	public string code = "";
	// Declare member variables here. Examples:
	// private int a = 2;
	// private string b = "text";

	// Called when the node enters the scene tree for the first time.
	public override void _Ready()
	{
		MiniScript.Interpreter interp = new MiniScript.Interpreter(code,
			(text, addNewline) => {
				GD.Print(text);
		},

			(text, addNewline) => {
				GD.Print(text);
		});
		interp.Compile();
		interp.RunUntilDone();
		
	}

//  // Called every frame. 'delta' is the elapsed time since the previous frame.
//  public override void _Process(float delta)
//  {
//      
//  }
}
