#include "RockCamera.h"
#include "Application.h"
#include "Drawer.h"
#include "RockFamily.h"

const Vector INIT_POS = Vector( 0, 100, -150 );

RockCameraPtr RockCamera::getTask( ) {
	return std::dynamic_pointer_cast<RockCamera>( Application::getInstance( )->getTask( getTag( ) ) );
}


RockCamera::RockCamera( ) {
}


RockCamera::~RockCamera( ) {
}

void RockCamera::initialize( ) {
	_pos = INIT_POS;
	RockFamilyPtr family( RockFamily::getTask( ) );
	_target = family->getCameraPos( STATE_TEST );
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->setCameraUp( Vector( 0, 1, 0 ) );
	drawer->setCamera( _pos, _target );
}

void RockCamera::update( ) {
	RockFamilyPtr family( RockFamily::getTask( ) );
	_target = family->getCameraPos( STATE_TEST );
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->setCamera( _pos, _target );
}
