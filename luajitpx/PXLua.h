/* PXLua.h */
#ifndef PXLUA_H
#define PXLUA_H

extern "C"{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "core/reference.h"
#include "core/ustring.h"

/*Defines runtime Lua import paths, and imports the state, which instantiates the game state
and sets it as global variable. Defined for explicit runtime. Currently checks for the paths
in my personal clone of the lua src.*/
const char * const LUA_PERSONAX_PATH = "package.path = package.path..';K:/Git/personax-lua-src/model/?.lua'";
const char * const MY_LUA_PATH = "package.path = package.path..';K:/Git/personax-lua-src/extlib/lua_path/?.lua'";
const char * const MY_LUA_CPATH = "package.cpath = package.cpath..';K:/Git/personax-lua-src/extlib/lua_cpath/?.dll'";
const char * const GLOBAL_DATAPATH = "_G.DATAPATH = 'K:/Git/personax-lua-src/model/data/'";
const char * const REQUIRE_STATE = "require('state')";
const char * const SETUP_STATE = "require('util/state/start_game')";


class PXLua : public Reference {
    GDCLASS(PXLua, Reference);

    lua_State *L;

protected:
    static void _bind_methods();

public:
    // Send event to the GSV
	String sendStateEvent(String event);
	String getUpdate();
    void startGame();

    PXLua();

private:
	void setupLuaState();
	void runPathSet(const char* command);
};

#endif