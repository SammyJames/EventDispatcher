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
    struct PendingEvent
    {
        PendingEvent( int32_t id, const EventArguments& args )
        : eventId( id )
        , args( args )
        {
            
        }
        
        int32_t eventId;
        EventArguments args;
    };
    
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
        
        void OnUpdate();
        
    private:
        void DispatchEvent_Internal( int32_t eventId, const EventArguments& args );
        void RegisterEvent( int32_t eventId, int32_t scope, int32_t func );
        void ReleaseEvent( int32_t eventId, int32_t scope, int32_t func );
        
        std::multimap< int32_t, std::pair< int32_t, int32_t > > m_eventWatchers;
        std::list< std::pair< int32_t, int32_t > > m_dispatching;
        std::list< PendingEvent > m_pending;
        lua_State* L;
    };
}

#define DISPATCH_EVENT( EventId, ... ) \
    Lua::EventDispatcher::instance->DispatchEvent( EventId, __VA_ARGS__ );

#endif /* defined(__EventDispatcher__EventDispatcher__) */
