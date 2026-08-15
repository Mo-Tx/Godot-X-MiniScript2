# MoTrix / Godot-X-MiniScript2 (GDXMS2)

An updated and improved version of the unfinished Godot-X-MiniScript wrapper, bridging MiniScript with Godot. This version is built on [MiniScript2](https://github.com/JoeStrout/miniscript2/tree/3579b47cbf616e1c22badf2bc1b87ed25fdd6359) and optimized for web exports.

---

## Progress

This project is in early active development. Features will roll out gradually over time.

### C++ Version (GDExtension) — [`./gdxms2-cpp`](https://github.com/Mo-Tx/Godot-X-MiniScript2/tree/main/gdxms2-cpp)

| Planned | In Progress | Done |
| :--- | :--- | :--- |
| Conversion functions | Polished README | Working first build |
| Intrinsic API | dev.to blog post | Interpreter API |
| Global value API | Class reference docs | Run MiniScript code on web |
| Miscellaneous APIs | REPL API | Bind API to GDScript |

### C# Version (GodotSharp) — [`./gdxms2-cs`](https://github.com/Mo-Tx/Godot-X-MiniScript2/tree/main/gdxms2-cs)
> **Note:** Direct web export is not supported without 3rd-party tools.

| Planned | In Progress | Done |
| :--- | :--- | :--- |
| TBD | None | Working first build |

---

## Building

### C++ (GDExtension)

#### Dependencies
- **SCons** build system
- **a C/C++ compiler** (Clang or GCC recommended; cross-compilation supported)
- **Optional: Emscripten** (required if targeting Web/Wasm—use the version recommended by your Godot release)

#### Build Command

```bash
scons
```

#### References
- [GDExtension Documentation](https://docs.godotengine.org/en/4.4/tutorials/scripting/gdextension/index.html)
- [Godot Engine Development Documentation](https://docs.godotengine.org/en/4.4/contributing/development/index.html#buildsystem-and-work-environment) — *Includes a guide on configuring an IDE and scons documentation.*

### C# (GodotSharp)

#### Dependencies
- **.NET SDK 6.0+** (matching MiniScript2 requirements)
- **Godot Engine 4 (Mono/.NET build)**

---

#### Build Command

```bash
# Use Godot Mono's built-in C# / MSBuild system.
```

## Contributing

Pull requests are welcome! Formal code conventions are not yet defined, but reasonable contributions and bug fixes are generally accepted.

---

## License

Licensed under the **MIT License**—with attribution to [Godot](https://github.com/godotengine/godot), [godot-cpp](https://github.com/godotengine/godot-cpp), and [MiniScript2](https://github.com/joestrout/miniscript2).
