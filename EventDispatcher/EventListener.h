//
//  Event.h
//  EventDispatcher
//
//  Created by Sammy James on 5/10/14.
//  Copyright (c) 2014 pawkette. All rights reserved.
//

#ifndef EventDispatcher_EventListener_h
#define EventDispatcher_EventListener_h

#include <stdint.h>
#include "lua.hpp"

namespace Lua
{
    class EventListener
    {
    public:
        EventListener( int32_t scopeId, int32_t functionId )
        : m_scopeId( scopeId )
        , m_functionId( functionId )
        {
        }
        
        int32_t GetScope() const { return m_scopeId; }
        int32_t GetFunction() const { return m_functionId; }
        
    private:
        int32_t m_scopeId;
        int32_t m_functionId;
    };
}

#endif /* defined(EventDispatcher_EventListener_h) */
