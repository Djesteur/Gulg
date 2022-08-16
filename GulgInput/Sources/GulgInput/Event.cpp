#include "GulgInput/Event.hpp"

namespace Gg {

namespace Input {


bool operator==(const Event &firstEvent, const Event &secondEvent) { 

	return firstEvent.handledInput == secondEvent.handledInput 
	&&     firstEvent.eventType == secondEvent.eventType; 
}

}
}