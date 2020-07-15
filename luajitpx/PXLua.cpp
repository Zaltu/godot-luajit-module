/* PXLua.cpp */

#include "PXLua.h"

#include <stdio.h>
#include <iostream>

PXLua::PXLua() {
}

/**
* Used to send a valid event to the Lua state. Will return
* the value of state.update that resulted from the event.
* 
* :returns: C++ form of state.update after the event was processed
* :rtype: json
*/
String PXLua::sendStateEvent(String event){
    lua_getfield(L, -1, "event");
    lua_pushstring(L, event.utf8());
    int code = lua_pcall(L, 1, 1, 0);
    if (code != 0){
        // There was a problem in the Lua call.
        // It could be a Lua error or it could be a problem with the stack
        // Either way, we should force-quit here... 
        std::cout << lua_tostring(L, -1) << std::endl;
        // TODO force quit or signal godot to force quit
    }
    lua_pop(L, 1);
    return getUpdate();
}


/**
* Fetch the state.update value from the Lua stack.
* This does NOT clear the value of state.update
* 
* :returns: C++ form of state.update, for interpreting
* :rtype: json
*/
String PXLua::getUpdate(){
	lua_getfield(L, -1, "update");
	String update = lua_tostring(L, -1);
	lua_pop(L, 1);
	return update;
}


/**
* Singleton utility to apply the setup to the game.
* i.e. start the game, which means calling
* `require("util/state/start_game")`
* NOT USED FOR LOADING. Calling will essentially reset
* the game state to day 1/default start.
*/
void PXLua::startGame(){
    runPathSet(SETUP_STATE);
}

void PXLua::setupLuaState(
    String LUA_PERSONAX_PATH,
    String MY_LUA_PATH,
    String MY_LUA_CPATH,
    String GLOBAL_DATAPATH
){
    L = lua_open();
    luaL_openlibs(L);
    runPathSet(LUA_PERSONAX_PATH);
    runPathSet(MY_LUA_PATH);
    runPathSet(MY_LUA_CPATH);
    runPathSet(GLOBAL_DATAPATH);
    runPathSet(REQUIRE_STATE);
    lua_getglobal(L, "state");
}

void PXLua::runPathSet(String command){
    int code = luaL_dostring(L, command.utf8());
    if (code != 0){
        // Prob should return the real error code
        std::cout << lua_tostring(L, -1) << std::endl;
    }
}

void PXLua::_bind_methods() {
    ClassDB::bind_method(D_METHOD("sendStateEvent", "event"), &PXLua::sendStateEvent);
    ClassDB::bind_method(D_METHOD("getUpdate"), &PXLua::getUpdate);
    ClassDB::bind_method(D_METHOD("startGame"), &PXLua::startGame);
    ClassDB::bind_method(D_METHOD("setupLuaState", "LUA_PERSONAX_PATH", "MY_LUA_PATH", "MY_LUA_CPATH", "GLOBAL_DATAPATH"), &PXLua::setupLuaState);
}
