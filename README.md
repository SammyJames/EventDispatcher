EventDispatcher
===============

Lua event registry / dispatcher

Lua Usage
----------

#### Registering Events
`` EventDispatcher.RegisterEvent( eventId:Number, scope:Table, callack:Function ) ``

#### Unregistering Events
`` EventDispatcher.ReleaseEvent( eventId:Number, scope:Table, callback:Function ) ``

#### Dispatching Events
`` EventDispatcher.DispatchEvent( eventId:Number, ... ) ``

C++ Usage
----------

#### Dispatching Events
`` DISPATCH_EVENT( eventId:int, ... ) ``