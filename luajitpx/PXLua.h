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
String REQUIRE_STATE = "require('state')";
String SETUP_STATE = "require('util/state/start_game')";


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
    void setupLuaState(
        String LUA_PERSONAX_PATH,
        String MY_LUA_PATH,
        String MY_LUA_CPATH,
        String GLOBAL_DATAPATH
    );

    PXLua();

private:
	void runPathSet(String command);
};

#endif