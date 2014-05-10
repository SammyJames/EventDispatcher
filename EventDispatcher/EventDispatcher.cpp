//
//  EventDispatcher.cpp
//  EventDispatcher
//
//  Created by Sammy James on 5/10/14.
//  Copyright (c) 2014 pawkette. All rights reserved.
//

#include <iostream>
#include "EventDispatcher.h"
#include "Registry.h"

namespace
{
    static const char* skEventDispatcher = "EventDispatcher";
    static const luaL_reg skEventDispatchFuncs[] =
    {
        { "RegisterEvent",  Lua::EventDispatcher::RegisterEvent },
        { "ReleaseEvent",   Lua::EventDispatcher::ReleaseEvent },
        { "DispatchEvent",  Lua::EventDispatcher::DispatchEvent },
        //end
        { nullptr, nullptr }
    };
}

namespace Lua
{

    /*static*/ EventDispatcher* EventDispatcher::instance = nullptr;
    
    
    EventDispatcher::EventDispatcher( lua_State* L )
    : L( L )
    {
        
    }
    
    /*static*/ void EventDispatcher::Register( lua_State* L )
    {
        luaL_register(  L, skEventDispatcher, skEventDispatchFuncs );
    }
    
    /*static*/ int32_t EventDispatcher::RegisterEvent( lua_State* L )
    {
        int32_t arg_count = lua_gettop( L );
        if ( arg_count == 3 )
        {
            luaL_argcheck( L, lua_type( L, 1 ) == LUA_TNUMBER, 1,   "Expected an EventId" );
            luaL_argcheck( L, lua_type( L, 2 ) == LUA_TTABLE, 2,    "Expected a table or nil for scope" );
            luaL_argcheck( L, lua_type( L, 3 ) == LUA_TFUNCTION, 3, "Expected a function" );
            
            int32_t event = (int32_t)lua_tointeger( L, 1 );
            
            lua_pushvalue( L, 2 );
            int32_t scope = Registry::instance->AddRef( L );
            
            lua_pushvalue( L, 3 );
            int32_t func = Registry::instance->AddRef( L );
            
            EventDispatcher::instance->RegisterEvent( event, scope, func );
        }
        
        return 0;
    }
    
    /*static*/ int32_t EventDispatcher::ReleaseEvent( lua_State* L )
    {
        int32_t arg_count = lua_gettop( L );
        if ( arg_count == 3 )
        {
            luaL_argcheck( L, lua_type( L, 1 ) == LUA_TNUMBER, 1,   "Expected an EventId" );
            luaL_argcheck( L, lua_type( L, 2 ) == LUA_TTABLE, 2,    "Expected a table or nil for scope" );
            luaL_argcheck( L, lua_type( L, 3 ) == LUA_TFUNCTION, 3, "Expected an a callback function" );
            
            int32_t event = (int32_t)lua_tointeger( L, 1 );

            lua_pushvalue( L, 2 );
            int32_t scope = Registry::instance->ReleaseRef( L );
            
            lua_pushvalue( L, 3 );
            int32_t func = Registry::instance->ReleaseRef( L );
            
            
            EventDispatcher::instance->ReleaseEvent( event, scope, func );
        }
        
        return 0;
    }
    
    /*static*/ int32_t EventDispatcher::DispatchEvent( lua_State* L )
    {
        int32_t arg_count = lua_gettop( L );
        if ( arg_count > 0 )
        {
            luaL_argcheck( L, lua_type( L, 1 ) == LUA_TNUMBER, 1, "Expected an EventId" );
            
            EventArguments args;
            if ( arg_count > 1 )
            {
                for ( int32_t i = 2; i <= arg_count; ++i )
                {
                    switch( lua_type( L, i ) )
                    {
                        case LUA_TBOOLEAN:
                            args << (bool)lua_toboolean( L, i );
                            break;
                        case LUA_TNUMBER:
                            args << (float)lua_tonumber( L, i );
                            break;
                        case LUA_TSTRING:
                            args << lua_tostring( L , i );
                            break;
                        case LUA_TNIL:
                            args << nullptr;
                            break;
                        default:
                            break;
                    }
                }
            }
            
            EventDispatcher::instance->DispatchEvent_Internal( (int32_t)lua_tointeger( L, 1 ), args );
        }
        
        return 0;
    }
    
    void EventDispatcher::RegisterEvent( int32_t eventId, int32_t scope, int32_t func )
    {
        const auto range = m_eventWatchers.equal_range( eventId );
        
        for ( auto watcher = range.first; watcher != range.second; ++watcher )
        {
            if ( scope == watcher->second.first && func == watcher->second.second )
            {
                return;
            }
        }
        
        m_eventWatchers.emplace( std::make_pair( eventId, std::make_pair( scope, func ) ) );
    }
    
    void EventDispatcher::ReleaseEvent( int32_t eventId, int32_t scope, int32_t func )
    {
        const auto range = m_eventWatchers.equal_range( eventId );

        for ( auto watcher = range.first; watcher != range.second; ++watcher )
        {
            if ( scope == watcher->second.first && func == watcher->second.second )
            {
                watcher = m_eventWatchers.erase( watcher );
                break;
            }
        }
    }
    
    void EventDispatcher::DispatchEvent_Internal( int32_t eventId, const EventArguments& args )
    {
        const auto range = m_eventWatchers.equal_range( eventId );
        std::list< std::pair< int32_t, int32_t > > temp;
        
        for ( auto watcher = range.first; watcher != range.second; ++watcher )
        {
            temp.emplace_back( watcher->second.first, watcher->second.second );
        }
        
        for ( auto it : temp )
        {
            lua_getref( L, it.first );
            lua_getref( L, it.second );
        
            lua_pushvalue( L, -2 );
            
            args.push( L );
            
            if ( lua_pcall( L, 1 + args.size(), 0, 0 ) != 0 )
            {
                std::cout << "error dispatching event: " << lua_tostring( L, -1 ) << std::endl;
            }
        }
    }
    
}