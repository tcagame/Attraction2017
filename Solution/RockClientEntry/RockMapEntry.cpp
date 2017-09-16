#include "RockMapEntry.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "MessageSender.h"
#include "RockAlter.h"
#include "RockCasket.h"
#include "RockStorage.h"
#include "Status.h"

const Vector ENTRY_POS = Vector( 200, 0, 270 );
const double ENTRY_RADIUS = 40;

RockMapEntry::RockMapEntry( StatusPtr status ) :
_status( status ) {
}


RockMapEntry::~RockMapEntry( ) {
}

void RockMapEntry::initialize( ) {
	ModelMV1Ptr map01 = ModelMV1Ptr( new ModelMV1 );
	map01->load( "Resource/Rock/map/entry/map01.mv1" );
	addModel( map01 );

	ModelMV1Ptr col01 = ModelMV1Ptr( new ModelMV1 );
	col01->load( "Resource/Rock/map/entry/map01_col.mv1" );
	col01->setTrans( Matrix::makeTransformTranslation( Vector( 0, 10, 0 ) ) );
	col01->draw( );
	addColModel( col01 );
}


void RockMapEntry::update( ) {
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}
		Vector pos = player->getPos( );
		if ( isNext( pos ) &&
			 _status->getPlayer( i ).area != AREA_WAIT ) {
			unsigned int area = AREA_STREET_1;
			MessageSender::getTask( )->sendMessage( i, Message::COMMAND_AREA, &area );
		}
	}
}

bool RockMapEntry::isNext( const Vector& pos ) const {
	bool result = false;
	double length = ( pos - ENTRY_POS ).getLength( );
	if ( ENTRY_RADIUS > length ) {
		result = true;
	}
	return result;
}