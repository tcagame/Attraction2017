#include "RockMapBoss.h"
#include "ModelMV1.h"

RockMapBoss::RockMapBoss( ) {
	ModelMV1Ptr model = ModelMV1Ptr( new ModelMV1 );
	model->load( "Resource/Rock/map/streetBoss/room_fire.mv1" );
	model->draw( );
	addModel( model );

	ModelMV1Ptr col_model = ModelMV1Ptr( new ModelMV1 );
	col_model->load( "Resource/Rock/map/streetBoss/room_fire_col.mv1" );
	col_model->setTrans( Matrix::makeTransformTranslation( Vector( 0, 0, 0 ) ) );
	addColModel( col_model );
}

RockMapBoss::~RockMapBoss( ) {
}
