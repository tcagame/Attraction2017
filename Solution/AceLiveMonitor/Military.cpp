#include "Military.h"
#include "Application.h"

MilitaryPtr Military::getTask( ) {
	return std::dynamic_pointer_cast< Military >( Application::getInstance( )->getTask( getTag( ) ) );
}


Military::Military( ) {
}


Military::~Military( ) {
}
