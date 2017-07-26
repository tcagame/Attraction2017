#include "ViewerMilitary.h"
#include "Military.h"


ViewerMilitary::ViewerMilitary( ) {
}


ViewerMilitary::~ViewerMilitary( ) {
}

void ViewerMilitary::draw( ) const {
	MilitaryConstPtr military( Military::getTask( ) );
}
