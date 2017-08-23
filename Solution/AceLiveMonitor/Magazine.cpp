#include "Magazine.h"
#include "Application.h"
#include "Impact.h"
#include "Family.h"

MagazinePtr Magazine::getTask( ) {
	return std::dynamic_pointer_cast< Magazine >( Application::getInstance( )->getTask( getTag( ) ) );
}




Magazine::Magazine( ) {
}


Magazine::~Magazine( ) {
}

void Magazine::update( ) {
	std::list< ImpactPtr >::iterator ite = _impacts.begin( );
	while( ite != _impacts.end( ) ) {
		if ( !( *ite ) ) {
			ite++;
			continue;
		}

		ImpactPtr impact = *ite;
		if ( impact->isFinished( ) ) {
			ite = _impacts.erase( ite );
			continue;
		}
		impact->update( );
		impact->setSynchronousData( ( int )Family::getTask( )->getCameraPos( ) );
		ite++;
	}
}

void Magazine::add( ImpactPtr impact ) {
	_impacts.push_back( impact );
}

std::list< ImpactPtr > Magazine::getImpactList( ) const {
	return _impacts;
}