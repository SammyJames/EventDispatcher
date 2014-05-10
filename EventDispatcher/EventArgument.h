//
//  EventArgument.h
//  EventDispatcher
//
//  Created by Sammy James on 5/10/14.
//  Copyright (c) 2014 pawkette. All rights reserved.
//

#ifndef EventDispatcher_EventArgument_h
#define EventDispatcher_EventArgument_h

namespace Lua
{
    enum Type
    {
        kType_Invalid = -1,
        kType_String,
        kType_Int,
        kType_UInt,
        kType_Float,
        kType_Bool
    };
    
    class EventArgument
    {
    public:
        template< typename T >
        EventArgument( T value )
        : _s( NULL )
        {
            Set< T >( value );
        }
        
        EventArgument()
        : m_type( Type::kType_Invalid )
        , _s( NULL )
        {
        }
        
        Type GetType() const { return m_type; }
        
        template< typename T >
        void Set( T value )
        {
            Type last = m_type;
            SetValue( value );
            
            if ( last == Type::kType_String &&
                m_type != Type::kType_String )
            {
                delete[] _s;
                _s = NULL;
            }
        }
        
        template< typename T >
        T Get() const
        {
            T result;
            GetValue( &result );
            return result;
        }
        
    protected:
        
        void SetValue( const char* s )
        {
            m_type = Type::kType_String;
            
            size_t len = strlen( s );
            _s = new char[ len + 1 ];
            strcpy( _s, s );
        }
        
        void SetValue( int32_t i )
        {
            m_type = Type::kType_Int;
            _i = i;
        }
        
        void SetValue( uint32_t u )
        {
            m_type = Type::kType_UInt;
            _u = u;
        }
        
        void SetValue( float f )
        {
            m_type = Type::kType_Float;
            _f = f;
        }
        
        void SetValue( bool b )
        {
            m_type = Type::kType_Bool;
            _b = b;
        }
        
        void GetValue( char** s ) const
        {
            *s = _s;
        }
        
        void GetValue( int32_t* i ) const
        {
            *i = _i;
        }
        
        void GetValue( uint32_t* u ) const
        {
            *u = _u;
        }
        
        void GetValue( float* f ) const
        {
            *f = _f;
        }
        
        void GetValue( bool* b ) const
        {
            *b = _b;
        }
        
    private:
        Type m_type;
        
        union
        {
            char*       _s;
            int32_t     _i;
            uint32_t    _u;
            float       _f;
            bool        _b;
        };
    };
}

#endif
