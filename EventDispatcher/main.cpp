//
//  main.cpp
//  EventDispatcher
//
//  Created by Sammy James on 5/10/14.
//  Copyright (c) 2014 pawkette. All rights reserved.
//

#include <iostream>
#include <stdint.h>

#include "lua.hpp"

#include "EventDispatcher.h"

int main(int argc, const char * argv[])
{
    lua_State* L = lua_open();
    Lua::EventDispatcher::instance = new Lua::EventDispatcher( L );
    
    luaL_openlibs( L );
    Lua::EventDispatcher::Register( L );
    
    luaL_dofile( L, "Scripts/EventDispatcher.lua" );
    
    Lua::EventDispatcher::instance->DispatchEvent( 1, 1, 2, 3, "four" );
    Lua::EventDispatcher::instance->DispatchEvent( 2, nullptr, 3, 2, 1 );

    lua_close( L );
    
    return 0;
}

