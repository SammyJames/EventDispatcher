//
//  EventArguments.h
//  EventDispatcher
//
//  Created by Sammy James on 5/10/14.
//  Copyright (c) 2014 pawkette. All rights reserved.
//

#ifndef EventDispatcher_EventArguments_h
#define EventDispatcher_EventArguments_h

#include <stdint.h>
#include <list>

#include "lua.hpp"
#include "EventArgument.h"

namespace Lua
{
    class EventArguments
    {
    public:
        EventArguments() {}
        
        template< typename... T >
        EventArguments( const T&... arguments )
        {
            _init( arguments... );
        }
        
        EventArguments( EventArguments&& other )
        {
            *this = std::move( other );
        }
        
        EventArguments( const EventArguments& other )
        {
            *this = other;
        }
        
        inline EventArguments& operator<<( const char* s )
        {
            m_arguments.emplace_back( s );
            return *this;
        }
        
        inline EventArguments& operator<<( int32_t i )
        {
            m_arguments.emplace_back( i );
            return *this;
        }
        
        inline EventArguments& operator<<( uint32_t u )
        {
            m_arguments.emplace_back( u );
            return *this;
        }
        
        inline EventArguments& operator<<( float f )
        {
            m_arguments.emplace_back( f );
            return *this;
        }
        
        inline EventArguments& operator<<( bool b )
        {
            m_arguments.emplace_back( b );
            return *this;
        }
        
        inline EventArguments& operator<<( std::nullptr_t )
        {
            m_arguments.emplace_back(); //we'll use null to represent nil in lua :)
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
                    case Type::kType_Invalid:
                    default:
                        lua_pushnil( L );
                        break;
                }
            }
        }
        
        EventArguments& operator=( EventArguments&& rhs )
        {
            for ( auto& it : rhs.m_arguments )
            {
                m_arguments.emplace_back( it );
            }
            
            return *this;
        }
        
        EventArguments& operator=( const EventArguments& rhs )
        {
            for ( auto& it : rhs.m_arguments )
            {
                m_arguments.emplace_back( it );
            }
            
            return *this;
        }
        
    protected:
        template< typename T, typename... U >
        void _init( const T& arg, const U&... arguments )
        {
            _init( arg );
            _init( arguments... );
        }
        
        template< typename T >
        inline void _init( const T& value )
        {
            *this << value;
        }
            
    private:
        std::list< EventArgument > m_arguments;
    };
}

#endif /* defined(EventDispatcher_EventArguments_h) */
