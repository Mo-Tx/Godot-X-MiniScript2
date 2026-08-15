# MoTrix/Godot-X-MiniScript2 (GDXMS2)

An updated and improved version of the unfinished Godot-X-MiniScript wrapper, a MiniScript wrapper for Godot. Now based on newer and better MiniScript2([here](https://github.com/JoeStrout/miniscript2/tree/3579b47cbf616e1c22badf2bc1b87ed25fdd6359)) and optimized for web.

# Progress:
This project is still under development in its very early stages. There are a lot of planned features expected to eventaully land in a couple of years (I am busy with life, and I'm the only one working on this)

## Plans for the C++ version([./gdxms2-cpp](https://github.com/Mo-Tx/Godot-X-MiniScript2/edit/main/gdxms2-cpp)) (GDExtnesion-based)
| Planned                    | In Progress                    | Done                         |  
|----------------------------|--------------------------------|------------------------------|  
| - Add conversion functions | - Add polished README          | - Add working first build    |  
| - Add intrinsic API        | - Post the first dev.to blog   | - Add interepreter API       |  
| - Add global value API     | - Add class reference docs     | - Run MiniScript code on web |  
| - Add misc. APIs           | - Add REPL API                 | - Bind API to GDScript       |  

## Plans for the C# version([./gdxms2-cs](https://github.com/Mo-Tx/Godot-X-MiniScript2/edit/main/gdxms2-cs)) (GodotSharp-based) 
#### (DOES _NOT_ SUPPORT WEB EXPORT WITHOUT 3RD-PARTY TOOLS)
| Planned                    | In Progress                    | Done                         | 
|----------------------------|--------------------------------|------------------------------|
| - Currently none           | - Nothing                      | - Add working first build    |

# Building:
## C++:
### Dependencies:
- Scons build system
- A C/C++ compiler for your platform (Clang or GCC are recommended, others are supported, cross-compilation also supported if the compiler has it)
  
  **Note**: for targeting the web(wasm), you need to use Emscripten with the recommended compiler version for your Godot version

### Build command:
`$ scons <scons arguments>`

**See:**
- [GDExtension documentation](https://docs.godotengine.org/en/4.4/tutorials/scripting/gdextension/index.html)
- [Godot Engine development doccumentation](https://docs.godotengine.org/en/4.4/contributing/development/index.html#buildsystem-and-work-environment) (Includes a guide on configuring an IDE and documentation 

## C++:
### Dependencies:
- .NET SDK 6.0 or newer (whichever one MiniScript2 uses)
-  Godot Engine 4 Mono (Latest version)

### Build command:
**_Use Godot Mono's C# MSBuild build system_**

# Contribution:
Contributions are welcome but there isn't really a standard for how to write the code yet. So it's mainly going to be arbitrary when deciding to accept a PR or not--but it will likely be accepted.

# License:
This project is licensed under the MIT license with attribution to [godot](https://github.com/godotengine/godot), [godot-cpp](https://github.com/godotengine/godot-cpp) and [miniscript2](https://github.com/joestrout/miniscript2)
