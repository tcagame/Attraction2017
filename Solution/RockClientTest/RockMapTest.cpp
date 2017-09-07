#include "RockMapTest.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "MessageSender.h"
#include "RockAlter.h"
#include "RockCasket.h"
#include "Movie.h"
#include "Drawer.h"
#include "RockStorage.h"
#include "RockItemRock.h"
#include "RockItemToku.h"
#include "RockItemDango.h"

const Vector ENTRY_POS = Vector( 200, 0, 270 );
const double ENTRY_RADIUS = 40;

RockMapTest::RockMapTest( ) {
	ModelMV1Ptr map01 = ModelMV1Ptr( new ModelMV1 );
	map01->load( "Resource/Rock/map/test/map01.mv1" );
	addModel( map01 );
	
	ModelMV1Ptr col01 = ModelMV1Ptr( new ModelMV1 );
	col01->load( "Resource/Rock/map/test/map01_col.mv1" );
	col01->setTrans( Matrix::makeTransformTranslation( Vector( 0, 10, 0 ) ) );
	col01->draw( );
	addColModel( col01 );

	ModelMV1Ptr obj06 = ModelMV1Ptr( new ModelMV1 );
	obj06->load( "Resource/Rock/object/obj06/obj06.mv1" );
	obj06->setScale( Matrix::makeTransformScaling( Vector( 5, 1, 5 ) ) );
	addModel( obj06 );

	ModelMV1Ptr obj01 = ModelMV1Ptr(new ModelMV1);
	obj01->load("Resource/Rock/object/obj01/obj01.mv1");
	addModel(obj01);

	RockStoragePtr storage( RockStorage::getTask( ) );
	//アイテム
	storage->addItem( RockItemPtr( new RockItemToku( Vector( 200, 50, 0 ) ) ) );
	storage->addItem( RockItemPtr( new RockItemToku( Vector( 100, 50, 0 ) ) ) );
	storage->addItem( RockItemPtr( new RockItemRock( Vector( 0, 50, 0 ) ) ) );
	//ショップアイテム
	storage->addShopItem( RockItemPtr( new RockItemDango( Vector( -50, 50, 0 ) ) ) );
	storage->addAlter( RockAlterPtr( new RockAlter( Vector( 50, 0, 50 ), Vector( 50, 50, 50 ) ) ) );
}


RockMapTest::~RockMapTest( ) {
}

void RockMapTest::update( ) {
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}
		Vector pos = player->getPos( );
		if ( isNext( pos ) ) {
			unsigned int area = AREA_STREET_1;
			MessageSender::getTask( )->sendMessage( i, Message::COMMAND_STATE, &area );
		}
	}
}

bool RockMapTest::isNext( const Vector& pos ) const {
	bool result = false;
	double length = ( pos - ENTRY_POS ).getLength( );
	if ( ENTRY_RADIUS > length ) {
		result = true;
	}
	return result;
}