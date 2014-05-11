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
    
    class EventArgument
    {
    public:
        enum
        {
            kType_Invalid = -1,
            kType_String,
            kType_Int,
            kType_UInt,
            kType_Float,
            kType_Double,
            kType_Bool,
            kType_Nil,
        };
        
        template< typename T >
        EventArgument( T value )
        : m_type( kType_Invalid )
        {
            Set< T >( value );
        }
        
        EventArgument()
        : m_type( kType_Invalid )
        {
        }
        
        explicit EventArgument( EventArgument&& rhs )
        {
            *this = std::move( rhs );
        }
        
        explicit EventArgument( const EventArgument& rhs )
        {
            *this = rhs;
        }
        
        ~EventArgument()
        {
            if ( m_type == kType_String )
            {
                delete[] _s;
            }
        }
        
        inline int32_t GetType() const { return m_type; }
        
        template< typename T >
        void Set( T value )
        {
            if ( m_type == kType_String )
            {
                delete[] _s;
            }
            
            SetValue( value );
        }
        
        template< typename T >
        inline T Get() const
        {
            T result;
            GetValue( &result );
            return result;
        }
        
        EventArgument& operator=( const EventArgument& rhs )
        {
            if ( this == &rhs ) { return *this; }
            
            switch ( rhs.GetType() )
            {
                case kType_String:
                    Set( rhs.Get< char* >() );
                    break;
                case kType_Int:
                    Set( rhs.Get< int32_t >() );
                    break;
                case kType_UInt:
                    Set( rhs.Get< uint32_t >() );
                    break;
                case kType_Double:
                    Set( rhs.Get< double >() );
                    break;
                case kType_Float:
                    Set( rhs.Get< float >() );
                    break;
                case kType_Bool:
                    Set( rhs.Get< bool >() );
                    break;
                case kType_Nil:
                    Set( nullptr );
                    break;
                default:
                    m_type = kType_Invalid;
                    break;
            }
            
            return *this;
        }
        
        EventArgument& operator=( EventArgument&& rhs )
        {
            switch ( rhs.GetType() )
            {
                case kType_String:
                    Set( rhs.Get< char* >() );
                    break;
                case kType_Int:
                    Set( rhs.Get< int32_t >() );
                    break;
                case kType_UInt:
                    Set( rhs.Get< uint32_t >() );
                    break;
                case kType_Double:
                    Set( rhs.Get< double >() );
                    break;
                case kType_Float:
                    Set( rhs.Get< float >() );
                    break;
                case kType_Bool:
                    Set( rhs.Get< bool >() );
                    break;
                case kType_Nil:
                    Set( nullptr );
                    break;
                default:
                    m_type = kType_Invalid;
                    break;
            }
            
            return *this;
        }
        
    protected:
        
        void SetValue( const char* s )
        {
            m_type = kType_String;
            
            _s = new char[ strlen( s ) ];
            strcpy( _s, s );
        }
        
        void SetValue( int32_t i )
        {
            m_type = kType_Int;
            _i = i;
        }
        
        void SetValue( uint32_t u )
        {
            m_type = kType_UInt;
            _u = u;
        }
        
        void SetValue( double d )
        {
            m_type = kType_Double;
            _d = d;
        }
        
        void SetValue( float f )
        {
            m_type = kType_Float;
            _f = f;
        }
        
        void SetValue( bool b )
        {
            m_type = kType_Bool;
            _b = b;
        }
        
        void SetValue( std::nullptr_t )
        {
            m_type = kType_Nil;
            _i = 0;
        }
        
        inline void GetValue( char** s )    const { *s = _s; }
        inline void GetValue( int32_t* i )  const { *i = _i; }
        inline void GetValue( uint32_t* u ) const { *u = _u; }
        inline void GetValue( float* f )    const { *f = _f; }
        inline void GetValue( bool* b )     const { *b = _b; }
        inline void GetValue( double* d )   const { *d = _d; }
        
    private:
        int32_t m_type;
        union
        {
            char*       _s;
            int32_t     _i;
            uint32_t    _u;
            float       _f;
            double      _d;
            bool        _b;
        };
    };
}

#endif
