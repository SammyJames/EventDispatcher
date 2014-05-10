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
#include "Event.h"

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
            DispatchEvent_Internal( eventId );
        }
        
        template< typename T_0 >
        void DispatchEvent( int32_t eventId, const T_0& _0 )
        {
            DispatchEvent_Internal( eventId );
        }
        
        template< typename T_0, typename T_1  >
        void DispatchEvent( int32_t eventId, const T_0& _0, const T_1& _1 )
        {
            DispatchEvent_Internal( eventId );
        }
        
        template< typename T_0, typename T_1, typename T_2  >
        void DispatchEvent( int32_t eventId, const T_0& _0, const T_1& _1, const T_2& _2 )
        {
            DispatchEvent_Internal( eventId );
        }
        
    private:
        void DispatchEvent_Internal( int32_t eventId );
        void RegisterEvent( int32_t eventId, Event listener );
        void ReleaseEvent( int32_t eventId, Event listener );
        
        std::multimap< int32_t, Event > m_eventWatchers;
        lua_State* L;
    };
}

#endif /* defined(__EventDispatcher__EventDispatcher__) */
