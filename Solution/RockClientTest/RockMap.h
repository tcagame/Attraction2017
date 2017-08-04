#pragma once
#include "Task.h"
#include <string>
#include "ModelMV1.h"

PTR( RockMap );

class RockMap : public Task {
public:
	static std::string getTag( ) { return "ROCKMAP"; };
	static RockMapPtr getTask( );
public:
	RockMap( );
	virtual ~RockMap( );
public:
	void initialize( );
	void update( );
	ModelMV1Ptr getModel( ) const;
	ModelMV1Ptr getColModel( ) const;
private:
	ModelMV1Ptr _model;
	ModelMV1Ptr _col_model;
};

