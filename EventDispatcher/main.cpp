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

#define EVENT_ONE 1
#define EVENT_TWO 2

int main(int argc, const char * argv[])
{
    lua_State* L = lua_open();
    Lua::EventDispatcher::instance = new Lua::EventDispatcher( L );
    
    luaL_openlibs( L );
    Lua::EventDispatcher::Register( L );
    
    luaL_dofile( L, "Scripts/EventDispatcher.lua" );
    
    
    DISPATCH_EVENT( EVENT_ONE, 1, 2, 3, "four", 0.5f, true, INT_MAX );
    DISPATCH_EVENT( EVENT_TWO, "five", nullptr, 0x0001, UINT_MAX, 0 );
    
    lua_close( L );
    
    return 0;
}

