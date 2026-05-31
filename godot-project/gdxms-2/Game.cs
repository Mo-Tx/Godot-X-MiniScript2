using Godot;
using System;
using MiniScript;

public partial class Game : Node //Game singleton
{
	// Called when the node enters the scene tree for the first time.
	public override void _Ready()
	{
		//MiniScript intializations
		GCManager.Init();
		ErrorType.Init();
		ShellIntrinsics.Init(); 
	}

	// Called every frame. 'delta' is the elapsed time since the previous frame.
	public override void _Process(double delta)
	{
	}
}
