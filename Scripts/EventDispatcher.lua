print( "EventDispatcher Test" )

local EventDispatcher = EventDispatcher;

local meep = {}
function meep:func1( ... )
    print( 'func1, callback for event 1' )

    EventDispatcher.ReleaseEvent( 1, meep, meep.func1 )
end

function meep:func2( ... ) 
    print( 'func2, callback for event 1' )

    EventDispatcher.ReleaseEvent( 1, meep, meep.func2 )
end

EventDispatcher.RegisterEvent( 1, meep, meep.func1 )
EventDispatcher.RegisterEvent( 1, meep, meep.func2 )

local x = {}
function x:blorp( ... )
    print( 'oh em gee' ) 

    EventDispatcher.ReleaseEvent( 1, x, x.blorp )

    for i = 1,20 do
        EventDispatcher.DispatchEvent( 2, 'hi', nil, nil, 'meow' ) 
    end
end

EventDispatcher.RegisterEvent( 1, x, x.blorp )

local y = 
{
    calls = 0
}
function y:help( ... )
    self.calls = self.calls + 1
    print( 'y:help called: ' .. self.calls .. ' times' )
    local args = { ... }

    print( 'count: ' .. #args )

    for i=1,#args do
        print( i .. ' = ' .. tostring( args[ i ] ) )
    end
    print( '-------------------' )
end

function y:derp( ... )
end

EventDispatcher.RegisterEvent( 2, y, y.derp )
EventDispatcher.RegisterEvent( 2, y, y.help )