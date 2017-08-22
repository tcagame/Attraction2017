#include "RockMapStreet.h"
#include "ModelMV1.h"

const int STREET_MODEL_NUM = 3;


RockMapStreet::RockMapStreet( ) {
	_filenames = { };
	for ( int i = 0; i < STREET_MODEL_NUM; i++ ) {
		ModelMV1Ptr model = ModelMV1Ptr( new ModelMV1 );
		char filename[ 256 ];
		sprintf_s( filename, "Resource/Rock/map/map02_0%d.mv1", i + 1 );
		model->load( filename );
		
		model->draw( );
		addModel( model );
	}
	ModelMV1Ptr col_model = ModelMV1Ptr( new ModelMV1 );
	col_model->load( "Resource/Rock/map/map02_CL.mv1" );
	col_model->setTrans( Matrix::makeTransformTranslation( Vector( 0, 0, 0 ) ) );
	addColModel( col_model );
}

RockMapStreet::~RockMapStreet( ) {
}

void RockMapStreet::update( ) {
}