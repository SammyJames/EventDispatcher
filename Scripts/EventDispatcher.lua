print( "EventDispatcher Test" )

local EventDispatcher = EventDispatcher;

meep = {}
function meep:func1( ... )
    print( "func1, callback for event 1" )

    EventDispatcher.ReleaseEvent( 1, self, self.func1 )
end

function meep:func2( ... ) 
    print( "func2, callback for event 1" )

    EventDispatcher.ReleaseEvent( 1, self, self.func2 )
end

EventDispatcher.RegisterEvent( 1, meep, meep.func1 )
EventDispatcher.RegisterEvent( 1, meep, meep.func2 )

x = {}
function x:blorp( ... )
    print( "oh em gee" ) 

    EventDispatcher.ReleaseEvent( 1, self, self.blorp )
    EventDispatcher.DispatchEvent( 2, "hi", ... ) 
end

EventDispatcher.RegisterEvent( 1, x, x.blorp )

y = {}
function y:help( ... )
    print( unpack( { ... } ) )
    print( "help, callback for event 2" )
end


EventDispatcher.RegisterEvent( 2, y, y.help )