# Overview
This repo contains a version of the PersonaX LuaJIT C++ bridge that can function as a module for the Godot game engine. The functionality of the module is limited to the standard context of PersonaX Engine VS Model implementation whereby only two functions are exposed to the Godot runtime environment, i.e. `sendStateEvent` and `getUpdate`.

## Building
`luajitpx` is configured as a Godot C++ module, as defined in the Godot doc that can be found [here](https://docs.godotengine.org/en/3.1/development/cpp/custom_modules_in_cpp.html). This means that you must compile Godot from source with the `lujitpx/` folder included in order to be able to access the object in the editor and via GDScript.

Note that SCons, the build system used by Godot, seems to not recognize symlinked folders as potential subdirectories during build time. The easiest way is there for to manually copy-paste the files into the modules section. Your Godot directory should therefore include:  
`godot/modules/luajitpx/PXLua.h`

### Library Type
This is mostly a reminder to myself, because apparently no matter how long I fight with integrating Lua into build systems I'll never git gud. This is compiled as a static library because the code contained *here* can be compiled and linked statically. The lua51 DLL that is refered to in this build *is still a DLL and is still linked dynamically* you dingus. It will need to be in your runtime path.

### SCsub Notes
The `luajitpx/SCsub` file is used by the Godot build system to include this module in the final build and is unique to each individual module. it is where the LuaJIT header files and static library (see [my custom luajit build](https://github.com/Zaltu/luajit205-52-libdll)) are indentified. By default, they assume both can be found in `C:/LUA`. Change those lines to the appropriate location for you.

## Use
Followning general Godot mentality, this module adds a single Object class to the GDScript runtime environment, that is **`PXLua`**. This object contains two accessible functions, which are:
- `sendStateEvent`: Send an event to the Lua state
- `getUpdate`: Get the value of Lua's state.update

As with other PersonaX Lua/C++ integrations, the instatiation of the PXLua object *initializes the Lua state*. This includes creating the shared stack and also setting the Lua path/cpath/dofile directories to the correct location relative to system runtime (currently always based on Aigis filesystem locations). This means that you should most certainly, at all times, only have a *single PXLua object initialized in Godot*. Or you'll be running multiple states of the game, which may conflict as per explanations in the [PersonaX Lua source documentation](https://github.com/Zaltu/personax-lua-src). This means that the PXLua object should probably be loaded as a Godot singleton/Autoload and maintained separately from level and context switching.

## Reverse Lua -> C++ Functionality
TODO
