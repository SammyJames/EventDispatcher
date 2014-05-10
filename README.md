EventDispatcher
===============

Lua event registry / dispatcher

USAGE
-----

#### Registering Events
`` EventManager.RegisterEvent( eventId:Number, scope:Table, callack:Function ) ``

#### Unregistering Events
`` EventManager.ReleaseEvent( eventId:Number, scope:Table, callback:Function ) ``

#### Dispatching Events
`` EventManager.DispatchEvent( eventId:Number, ... ) ``