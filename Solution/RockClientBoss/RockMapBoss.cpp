#include "RockMapBoss.h"
#include "ModelMV1.h"

const char * MAP_FILENAME[ ] = {
	"Resource/Rock/map/streetBoss/room_fire.mv1",
	"Resource/Rock/map/streetBoss/room_tree.mv1",
	"Resource/Rock/map/streetBoss/room_rock.mv1",
};
const char * COL_FILENAME[ ] = {
	"Resource/Rock/map/streetBoss/room_fire_col.mv1",
	"Resource/Rock/map/streetBoss/room_tree_col.mv1",
	"Resource/Rock/map/streetBoss/room_rock_col.mv1",
};

RockMapBoss::RockMapBoss( ) {
	for ( int i = 0; i < 3; i++ ) {
		ModelMV1Ptr model = ModelMV1Ptr( new ModelMV1 );
		model->load( MAP_FILENAME[ i ] );
		model->setTrans( Matrix::makeTransformTranslation( Vector( 0, 0, i * -2000 ) ) );
		model->draw( );
		addModel( model );
	}

	for ( int i = 0; i < 3; i++ ) {
		ModelMV1Ptr col_model = ModelMV1Ptr( new ModelMV1 );
		col_model->load( COL_FILENAME[ i ] );
		col_model->setTrans( Matrix::makeTransformTranslation( Vector( i * 100, 0, 0 ) ) );
		addColModel( col_model );
	}
}

RockMapBoss::~RockMapBoss( ) {
}
