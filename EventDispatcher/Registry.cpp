//
//  Registry.cpp
//  EventDispatcher
//
//  Created by Sammy James on 5/10/14.
//  Copyright (c) 2014 pawkette. All rights reserved.
//

#include "Registry.h"

namespace Lua
{
    /*static*/ Registry* Registry::instance = nullptr;
    
    Registry::Registry()
    {
        
    }
    
    Registry::~Registry()
    {
        
    }
    
    int32_t Registry::AddRef( lua_State* L )
    {
        int32_t result = -1;
        const int32_t registry_size = luaL_getn( L, LUA_REGISTRYINDEX );
        
        if ( registry_size )
        {
            for( auto itr = m_entries.begin(); itr != m_entries.end(); ++itr )
            {
                lua_getref( L, itr->m_registryIndex );
                if ( lua_equal( L, -1, -2 ) )
                {
                    result = itr->m_registryIndex;
                    itr->m_refCount++;
                    break;
                }
                
                lua_pop( L, 1 );
            }
        }

        if ( result == -1 )
        {
            RegEntry entry;
            entry.m_registryIndex = lua_ref( L, true );
            entry.m_refCount++;
            
            m_entries.push_back( entry );
            
            result = entry.m_registryIndex;
        }
        
        return result;
    }
    
    int32_t Registry::ReleaseRef( lua_State *L )
    {
        int32_t result = -1;
        const int32_t registry_size = luaL_getn( L, LUA_REGISTRYINDEX );
        
        if ( registry_size )
        {
            for( auto itr = m_entries.begin(); itr != m_entries.end(); ++itr )
            {
                lua_getref( L, itr->m_registryIndex );
                if ( lua_equal( L, -1, -2 ) )
                {
                    result = itr->m_registryIndex;
                    if ( --itr->m_refCount == 0 )
                    {
                        lua_unref( L, itr->m_registryIndex );
                        m_entries.erase( itr );
                    }
                    
                    break;
                }
                lua_pop( L, 1 );
            }
        }
        
        return result;
    }
}