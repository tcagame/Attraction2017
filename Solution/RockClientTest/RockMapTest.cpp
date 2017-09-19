#include "RockMapTest.h"
#include "MessageSender.h"
#include "RockAlter.h"
#include "RockCasket.h"
#include "Movie.h"
#include "Drawer.h"
//Player
#include "RockFamily.h"
#include "RockPlayer.h"
//Item
#include "RockStorage.h"
#include "RockItemRock.h"
#include "RockItemToku.h"
#include "RockItemDango.h"
#include "RockItemEnhancePower.h"
#include "RockItemMoney.h"
//Enemy
#include "RockMilitary.h"
#include "RockEnemyGhost.h"
#include "RockEnemyRedBard.h"
#include "RockEnemyWaterGhost.h"
#include "RockEnemyBossRock.h"
#include "RockEnemyFaceAndHand.h"
#include "RockEnemyCloud.h"
#include "RockEnemyBat.h"
#include "RockEnemyKimono.h"
#include "RockEnemyBossTree.h"

const Vector ENTRY_POS = Vector( 200, 0, 270 );
const double ENTRY_RADIUS = 40;

RockMapTest::RockMapTest( ) {
}


RockMapTest::~RockMapTest( ) {
}

void RockMapTest::initialize( ) {
	ModelMV1Ptr map01 = ModelMV1Ptr( new ModelMV1 );
	map01->load( "Resource/Rock/map/test/map01.mv1" );
	addModel( map01 );
	
	ModelMV1Ptr col01 = ModelMV1Ptr( new ModelMV1 );
	col01->load( "Resource/Rock/map/test/map01_col.mv1" );
	col01->setTrans( Matrix::makeTransformTranslation( Vector( 0, 10, 0 ) ) );
	col01->draw( );
	addColModel( col01 );

	//ModelMV1Ptr obj06 = ModelMV1Ptr( new ModelMV1 );
	//obj06->load( "Resource/Rock/object/obj06/obj06.mv1" );
	//obj06->setScale( Matrix::makeTransformScaling( Vector( 5, 1, 5 ) ) );
	//addModel( obj06 );

	//ModelMV1Ptr obj01 = ModelMV1Ptr(new ModelMV1);
	//obj01->load("Resource/Rock/object/obj01/obj01.mv1");
	//addModel(obj01);

	RockStoragePtr storage( RockStorage::getTask( ) );
	//アイテム
	//storage->addItem( RockItemPtr( new RockItemToku( Vector( 100, 50, 0 ) ) ) );
	//storage->addItem( RockItemPtr( new RockItemRock( Vector( 0, 50, 0 ) ) ) );
	storage->addItem( RockItemPtr( new RockItemMoney( Vector( 0, 50, 0 ), 500 ) ) );
	////ショップアイテム
	//storage->addShopItem( RockItemPtr( new RockItemDango( Vector( -50, 50, 0 ) ) ) );
	//storage->addShopItem( RockItemPtr( new RockItemEnhancePower( Vector( 200, 50, 0 ) ) ) );
	//祭壇
	storage->addAlter( RockAlterPtr( new RockAlter( Vector( 50, 0, 50 ), Vector( 50, 50, 50 ) ) ) );
	//エネミー
	genarateEnemies( );
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
			MessageSender::getTask( )->sendMessage( i, Message::COMMAND_AREA, &area );
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


void RockMapTest::genarateEnemies( ) {
	RockMilitaryPtr military = RockMilitary::getTask( );
	military->addEnemy( RockEnemyPtr( new RockEnemyBossTree( Vector( 0, 0, 0 ) ) ) );
	///military->add( RockEnemyPtr( new RockEnemyGhost( Vector( 0, 40, 0 ) ) ) );
	///military->add( RockEnemyPtr( new RockEnemyRedBard( Vector( 10, 30, 10 ) ) ) );
	///military->add( RockEnemyPtr( new RockEnemyWaterGhost( Vector( -10, 30, 30 ) ) ) );
	///military->add( RockEnemyPtr( new RockEnemyBossRock( Vector( -50, 50, 50 ) ) ) );
	///military->add( RockEnemyPtr( new RockEnemyFaceAndHand( Vector( -50, 50, 50 ) ) ) );
	///military->add( RockEnemyPtr( new RockEnemyCloud( Vector( -50, 50, 50 ) ) ) );
	///military->add( RockEnemyPtr( new RockEnemyBat( Vector( -50, 50, -50 ) ) ) );
	///military->add( RockEnemyPtr( new RockEnemyKimono( Vector( 50, 50, 50 ) ) ) );
}