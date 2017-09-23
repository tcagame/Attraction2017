#include "EventCall.h"


EventCall::EventCall( ) :
Event( EVENT_CALL, DIR_LEFT ) {
}


EventCall::~EventCall( ) {
}

void EventCall::update( ) {
	escape( );
}

void EventCall::join( PLAYER target ) {

}