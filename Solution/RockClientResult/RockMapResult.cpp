#include "RockMapResult.h"
#include "ModelMV1.h"
#include "Effect.h"
#include "Drawer.h"
#include "Image.h"
#include "define.h"
#include "Status.h"

RockMapResult::RockMapResult( StatusPtr status ) :
_status( status ) {
}


RockMapResult::~RockMapResult( ) {
}

void RockMapResult::initialize( ) {
	ModelMV1Ptr map01 = ModelMV1Ptr( new ModelMV1 );
	map01->load( "Resource/Rock/map/result/map11_01.mv1" );
	addModel( map01 );
	
	ModelMV1Ptr col01 = ModelMV1Ptr( new ModelMV1 );
	col01->load( "Resource/Rock/map/result/map11_01.mv1" );
	col01->draw( );
	addColModel( col01 );

	//”wŒi
	ModelMV1Ptr map03 = ModelMV1Ptr( new ModelMV1 );
	map03->load( "Resource/Rock/map/result/map11_03.mv1" );
	addModel( map03 );

	ModelMV1Ptr map05 = ModelMV1Ptr( new ModelMV1 );
	map05->load( "Resource/Rock/map/result/map11_05.mv1" );
	addModel( map05 );

	ModelMV1Ptr map04 = ModelMV1Ptr( new ModelMV1 );
	map04->load( "Resource/Rock/map/result/map11_04.mv1" );
	addModel( map04 );

	ModelMV1Ptr map02 = ModelMV1Ptr( new ModelMV1 );
	map02->load( "Resource/Rock/map/result/map11_02.mv1" );
	addModel( map02 );

	EffectPtr effect = Effect::getTask( );
	int handle = effect->loadEffect( "butta.efk" );
	effect->playEffect( handle );
	effect->updateEffectTransform( handle, Vector( 500, 250, 0 ) );

	DrawerPtr drawer = Drawer::getTask( );
	_end_image.push_back( drawer->createImage( "result/heaven_frame.png" ) );
	_end_image.push_back( drawer->createImage( "result/human_frame.png" ) );
	_end_image.push_back( drawer->createImage( "result/damn_frame.png" ) );
	_end_image.push_back( drawer->createImage( "result/hungry_frame.png" ) );
	_end_image.push_back( drawer->createImage( "result/hell_frame.png" ) );
}


void RockMapResult::update( ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		Status::Player player = _status->getPlayer( i );
		if ( player.area == AREA_RESULT ) {
			switch ( player.continue_num ) {
			case 0:
				drawEnding( i, ENDING_HEAVEN );
				break;
			case 1:
			case 2:
				drawEnding( i, ENDING_HUMAN );
				break;
			case 3:
			case 4:
				drawEnding( i, ENDING_BRUET );
				break;
			case 5:
			case 6:
				drawEnding( i, ENDING_BRAD );
				break;
			default:
				drawEnding( i, ENDING_HELL );
				break;
			}
		}
	}
}

void RockMapResult::drawEnding( int player, ENDING ending ) {
	//int idx = ending + player * 5;
	//int idx = ending;
	//_end_image[ idx ]->setPos( 0, 0 );
	//_end_image[ idx ]->draw( );
}
