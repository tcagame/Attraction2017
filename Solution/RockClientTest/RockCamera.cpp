#include "RockCamera.h"
#include "Application.h"
#include "Drawer.h"

const Vector INIT_POS = Vector( 0, 100, -150 );
const Vector INIT_TARGET = Vector( 0, 20, 0 );

RockCameraPtr RockCamera::getTask( ) {
	return std::dynamic_pointer_cast<RockCamera>( Application::getInstance( )->getTask( getTag( ) ) );
}


RockCamera::RockCamera( ) {
}


RockCamera::~RockCamera( ) {
}

void RockCamera::initialize( ) {
	_pos = INIT_POS;
	_target = INIT_TARGET;
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->setCameraUp( Vector( 0, 1, 0 ) );
	drawer->setCamera( _pos, _target );
}

void RockCamera::update( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->setCamera( _pos, _target );
}
