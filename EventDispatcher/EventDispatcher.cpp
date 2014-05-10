//
//  EventDispatcher.cpp
//  EventDispatcher
//
//  Created by Sammy James on 5/10/14.
//  Copyright (c) 2014 pawkette. All rights reserved.
//

#include "EventDispatcher.h"

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
            luaL_argcheck( L, lua_type( L, 1 ) == LUA_TNUMBER, 1, "Expected an EventId" );
            luaL_argcheck( L, lua_type( L, 2 ) == LUA_TNIL || lua_type( L, 2 ) == LUA_TTABLE, 2, "Expected a table or nil for scope" );
            luaL_argcheck( L, lua_type( L, 3 ) == LUA_TFUNCTION, 3, "Expected a function" );
            
            lua_pushvalue( L, 2 );
            int32_t scope = lua_ref( L, true );
            
            lua_pushvalue( L, 3 );
            int32_t func = lua_ref( L, true );
            
            EventDispatcher::instance->RegisterEvent( (int32_t)lua_tointeger( L, 1 ), Event( scope, func ) );
        }
        
        return 0;
    }
    
    /*static*/ int32_t EventDispatcher::ReleaseEvent( lua_State* L )
    {
        int32_t arg_count = lua_gettop( L );
        if ( arg_count == 3 )
        {
            luaL_argcheck( L, lua_type( L, 1 ) == LUA_TNUMBER, 1, "Expected an EventId" );
            luaL_argcheck( L, lua_type( L, 2 ) == LUA_TNIL || lua_type( L, 2 ) == LUA_TTABLE, 2, "Expected a table or nil for scope" );
            luaL_argcheck( L, lua_type( L, 3 ) == LUA_TFUNCTION, 3, "Expected an a callback function" );

 
            int32_t registry_size = luaL_getn( L, LUA_REGISTRYINDEX );
            int32_t scope = -1;
            for ( int32_t i = 1; i <= registry_size; ++i )
            {
                lua_getref( L, i );
                if ( lua_equal( L, -1, -3 ) )
                {
                    scope = i;
                    break;
                }
                lua_pop( L, 1 );
            }

            int32_t func = -1;
            for ( int32_t i = 1; i <= registry_size; ++i )
            {
                lua_getref( L, i );
                if ( lua_equal( L, -1, -3 ) )
                {
                    func = i;
                    break;
                }
                lua_pop( L, 1 );
            }
            
            EventDispatcher::instance->ReleaseEvent( (int32_t)lua_tointeger( L, 1 ), Event( scope, func ) );
        }
        
        return 0;
    }
    
    /*static*/ int32_t EventDispatcher::DispatchEvent( lua_State* L )
    {
        return 0;
    }
    
    void EventDispatcher::RegisterEvent( int32_t eventId, Event listener )
    {
        auto first = m_eventWatchers.equal_range( eventId ).first;
        auto last = m_eventWatchers.equal_range( eventId ).second;
        
        int32_t scope = listener.GetScope();
        int32_t func = listener.GetFunction();
        
        for ( auto watcher = first; watcher != last; ++watcher )
        {
            const Event& event( watcher->second );
            
            if ( event.GetScope() == scope && event.GetFunction() == func )
            {
                return;
            }
        }
        
        m_eventWatchers.insert( { eventId, listener } );
    }
    
    void EventDispatcher::ReleaseEvent( int32_t eventId, Event listener )
    {
        auto first = m_eventWatchers.equal_range( eventId ).first;
        auto last = m_eventWatchers.equal_range( eventId ).second;
        
        int32_t scope = listener.GetScope();
        int32_t func = listener.GetFunction();

        for ( auto watcher = first; watcher != last; ++watcher )
        {
            const Event& event( watcher->second );
            
            if ( event.GetScope() == scope && event.GetFunction() == func )
            {
                lua_unref( L, scope );
                lua_unref( L, func );
                m_eventWatchers.erase( watcher );
                break;
            }
        }
    }
    
    void EventDispatcher::DispatchEvent_Internal( int32_t eventId )
    {
        auto first = m_eventWatchers.equal_range( eventId ).first;
        auto last = m_eventWatchers.equal_range( eventId ).second;
        
        for ( auto watcher = first; watcher != last; ++watcher )
        {
            const Event& listener( watcher->second );
            
            lua_getref( L, listener.GetScope() );
            lua_getref( L, listener.GetFunction() );
            
            lua_pcall( L, 0, 0, NULL );
        }
    }
    
}