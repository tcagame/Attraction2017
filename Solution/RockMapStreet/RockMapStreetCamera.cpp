#include "RockMapStreetCamera.h"
#include "Application.h"
#include "Drawer.h"
#include "RockFamily.h"
#include "RockPlayer.h"

const Vector INIT_POS = Vector( 0, 300, -450 ) * 2;
const Vector INIT_TARGET = Vector( 0, 60, 0 );
//const Vector INIT_POS = Vector( 10000, 15000, -5000 );
//const Vector INIT_TARGET = Vector( 10000, 0, 0 );

RockMapStreetCameraPtr RockMapStreetCamera::getTask( ) {
	return std::dynamic_pointer_cast<RockMapStreetCamera>( Application::getInstance( )->getTask( getTag( ) ) );
}


RockMapStreetCamera::RockMapStreetCamera( ) {
}


RockMapStreetCamera::~RockMapStreetCamera( ) {
}

void RockMapStreetCamera::initialize( ) {
	_pos = INIT_POS;
	_target = INIT_TARGET;
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->setCameraUp( Vector( 0, 1, 0 ) );
	drawer->setCamera( _pos, _target );
}

void RockMapStreetCamera::update( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	Vector target = RockFamily::getTask( )->getCameraPos( );
	_pos += target - _target;
	_target = target;
	drawer->setCamera( _pos, _target );
}
