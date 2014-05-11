//
//  main.cpp
//  EventDispatcher
//
//  Created by Sammy James on 5/10/14.
//  Copyright (c) 2014 pawkette. All rights reserved.
//

#include <iostream>
#include <stdint.h>
#include <chrono>

#include "lua.hpp"

#include "EventDispatcher.h"
#include "Registry.h"

#define EVENT_ONE 1
#define EVENT_TWO 2

int main(int argc, const char * argv[])
{
    lua_State* L = luaL_newstate();
    Lua::EventDispatcher::instance = new Lua::EventDispatcher( L );
    Lua::Registry::instance = new Lua::Registry();
    
    luaL_openlibs( L );
    Lua::EventDispatcher::Register( L );

    luaL_dofile( L, "Scripts/EventDispatcher.lua" );
    

    DISPATCH_EVENT( EVENT_ONE, 1, 2.5, INT_MAX, 0x11143, false, nullptr );
    
    for ( int i = 0; i < 300; ++i )
    {
        Lua::EventDispatcher::instance->OnUpdate();
        DISPATCH_EVENT( EVENT_TWO, "five", 1.f, nullptr, 0x0001, UINT_MAX );
    }
    
    lua_close( L );
    
    return 0;
}

