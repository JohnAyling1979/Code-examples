var events = require('events');
var eventEmitter = new events.EventEmitter();

//event handler
var myEventHandler = function()
{
	console.log('I hear a scream!');
}

//assign the event handler
eventEmitter.on('scream',myEventHandler);

//fire the scream
eventEmitter.emit('scream');