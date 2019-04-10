/* summator.cpp */

#include "PXLua.h"

PXLua::PXLua() {
    setupLuaState();
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
    lua_pcall(L, 1, 1, 0);
    //std::string returncode = lua_tostring(L, -1);
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

void PXLua::setupLuaState(){
    L = lua_open();
    luaL_openlibs(L);
    //UE_LOG(LogTemp, Warning, TEXT("Forcing re-evaluation of Lua paths."));
    runPathSet(LUA_PERSONAX_PATH);
    runPathSet(MY_LUA_PATH);
    runPathSet(MY_LUA_CPATH);
    runPathSet(GLOBAL_DATAPATH);
    runPathSet(REQUIRE_STATE);
    lua_getglobal(L, "state");
}

void PXLua::runPathSet(const char* command){
    int code = luaL_dostring(L, command);
    if (code != 0){
        //std::string luaerror = lua_tostring(L, -1);
        //UE_LOG(LogTemp, Error, TEXT("Error initializing Lua State:\n%s"), *FString(luaerror.c_str()));
    }
}

void PXLua::_bind_methods() {
    ClassDB::bind_method(D_METHOD("sendStateEvent", "event"), &PXLua::sendStateEvent);
    ClassDB::bind_method(D_METHOD("getUpdate"), &PXLua::getUpdate);
}
