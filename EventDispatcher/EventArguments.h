//
//  EventArguments.h
//  EventDispatcher
//
//  Created by Sammy James on 5/10/14.
//  Copyright (c) 2014 pawkette. All rights reserved.
//

#ifndef __EventDispatcher__EventArguments__
#define __EventDispatcher__EventArguments__

#include <stdint.h>
#include <list>

#include "lua.hpp"
#include "EventArgument.h"

namespace Lua
{
    class EventArguments
    {
    public:
        explicit EventArguments() {}
        
        template< typename... T >
        EventArguments( const T&... arguments )
        {
            _init( arguments... );
        }
        
        EventArguments& operator<<( const char* s )
        {
            m_arguments.push_back( EventArgument( s ) );
            return *this;
        }
        
        EventArguments& operator<<( int32_t i )
        {
            m_arguments.push_back( EventArgument( i ) );
            return *this;
        }
        
        EventArguments& operator<<( uint32_t u )
        {
            m_arguments.push_back( EventArgument( u ) );
            return *this;
        }
        
        EventArguments& operator<<( float f )
        {
            m_arguments.push_back( EventArgument( f ) );
            return *this;
        }
        
        EventArguments& operator<<( bool b )
        {
            m_arguments.push_back( EventArgument( b ) );
            return *this;
        }
        
        inline int32_t size() const { return (int32_t)m_arguments.size(); }
        
        void push( lua_State* L ) const
        {
            for( auto itr = m_arguments.begin();
                itr != m_arguments.end();
                ++itr )
            {
                switch ( itr->GetType() )
                {
                    case Type::kType_String:
                        lua_pushstring( L, itr->Get< char* >() );
                        break;
                    case Type::kType_Int:
                        lua_pushinteger( L, itr->Get< int32_t >() );
                        break;
                    case Type::kType_UInt:
                        lua_pushinteger( L, itr->Get< uint32_t >() );
                        break;
                    case Type::kType_Float:
                        lua_pushnumber( L, itr->Get< float >() );
                        break;
                    case Type::kType_Bool:
                        lua_pushboolean( L, itr->Get< bool >() );
                    default:
                        break;
                }
            }
        }
        
    protected:
        template< typename T, typename... U >
        void _init( const T& arg, const U&... arguments )
        {
            _init( arg );
            _init( arguments... );
        }
        
        template< typename T >
        void _init( const T& value )
        {
            *this << value;
        }
            
    private:
        std::list< EventArgument > m_arguments;
    };
}

#endif /* defined(__EventDispatcher__EventArguments__) */
