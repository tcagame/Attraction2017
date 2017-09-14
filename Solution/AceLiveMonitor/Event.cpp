#include "Event.h"



Event::Event( EVENT type ) :
_type( type ) {
}


Event::~Event( ) {
}

EVENT Event::getType( ) const {
	return _type;
}
