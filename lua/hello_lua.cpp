// g++ hello_lua.cpp -o hello -llua

#include <iostream>
#include <lua.hpp>

int main() {
    // Create a new Lua state
    lua_State* L = luaL_newstate();

    // Load Lua standard libraries
    luaL_openlibs(L);

    // Run a Lua command
    if (luaL_dostring(L, "print('Hello, World from Lua!')")) {
        std::cerr << "Error: " << lua_tostring(L, -1) << std::endl;
    }

    // Close Lua state
    lua_close(L);

    return 0;
}