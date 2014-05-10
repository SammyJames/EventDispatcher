//
//  Registry.h
//  EventDispatcher
//
//  Created by Sammy James on 5/10/14.
//  Copyright (c) 2014 pawkette. All rights reserved.
//

#ifndef __EventDispatcher__Registry__
#define __EventDispatcher__Registry__

#include <stdint.h>
#include <list>

#include "lua.hpp"

namespace Lua
{
    struct RegEntry
    {
        int32_t m_registryIndex;
        uint32_t m_refCount;
    };
    
    class Registry
    {
    public:
        static Registry* instance;
        
        Registry();
        ~Registry();
        
        int32_t AddRef( lua_State* L );
        int32_t ReleaseRef( lua_State* L );
        
    private:
        std::list< RegEntry > m_entries;
    };
}

#endif /* defined(__EventDispatcher__Registry__) */
