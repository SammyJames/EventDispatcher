//
//  EventDispatcher.h
//  EventDispatcher
//
//  Created by Sammy James on 5/10/14.
//  Copyright (c) 2014 pawkette. All rights reserved.
//

#ifndef __EventDispatcher__EventDispatcher__
#define __EventDispatcher__EventDispatcher__

#include <stdint.h>
#include <map>

#include "lua.hpp"
#include "EventListener.h"
#include "EventArguments.h"

namespace Lua
{
    class EventDispatcher
    {
    public:
        static EventDispatcher* instance;
        
        EventDispatcher( lua_State* L );
        
        static void Register( lua_State* L );
        static int32_t RegisterEvent( lua_State* L );
        static int32_t ReleaseEvent( lua_State* L );
        static int32_t DispatchEvent( lua_State* L );
        
        void DispatchEvent( int32_t eventId )
        {
            DispatchEvent_Internal( eventId, EventArguments() );
        }
        
        template< typename... T >
        void DispatchEvent( int32_t eventId, const T&... args )
        {
            DispatchEvent_Internal( eventId, EventArguments( args... ) );
        }
        
    private:
        void DispatchEvent_Internal( int32_t eventId, const EventArguments& args );
        void RegisterEvent( int32_t eventId, EventListener listener );
        void ReleaseEvent( int32_t eventId, EventListener listener );
        
        std::multimap< int32_t, EventListener > m_eventWatchers;
        lua_State* L;
    };
}

#endif /* defined(__EventDispatcher__EventDispatcher__) */
