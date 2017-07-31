#include "RockViewer.h"
#include "RockMap.h"
#include "ModelMV1.h"
#include "Drawer.h"

RockViewer::RockViewer( ) {
}


RockViewer::~RockViewer( ) {
}

void RockViewer::update( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->flip( );
	drawMap( );
}

void RockViewer::drawMap( ) const {
	RockMapPtr map( RockMap::getTask( ) );
	ModelMV1Ptr model = map->getModel( );
	model->draw( );
}
