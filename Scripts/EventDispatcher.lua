print( "EventDispatcher Test" )

local EventDispatcher = EventDispatcher;

do

    local test = {}
    function test:func1()
        print( "func1, callback for event 1" )
    end

    function test:func2() 
        print( "func2, callback for event 1" )

        EventDispatcher.ReleaseEvent( 1, test, test.func1 )
    end

    function blorp()
        print( "oh em gee" ) 
    end



    EventDispatcher.RegisterEvent( 1, test, test.func1 )
    EventDispatcher.RegisterEvent( 1, test, test.func2 )
    EventDispatcher.RegisterEvent( 1, nil, blorp )

end

EventDispatcher.ReleaseEvent( 1, nil, blorp )

local test2 = {}
function test2:help()
    print( "help, callback for event 2" )
end

EventDispatcher.RegisterEvent( 2, test2, test2.help )