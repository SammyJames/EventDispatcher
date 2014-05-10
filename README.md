EventDispatcher
===============

Lua event registry / dispatcher

__USAGE__

`` EventManager.RegisterEvent( eventId:Number, scope:Table, callack:Function ) ``
`` EventManager.ReleaseEvent( eventId:Number, scope:Table, callback:Function ) ``
`` EventManager.DispatchEvent( eventId:Number, ... ) ``