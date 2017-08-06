#pragma once
#include "Task.h"
#include <string>
#include <array>
#include "ModelMV1.h"

PTR( RockStreet );

class RockStreet : public Task {
private:
	static const int STREET_MODEL_NUM = 3;
public:
	static std::string getTag( ) { return "ROCKSTREET"; };
	static RockStreetPtr getTask( );
public:
	RockStreet( );
	virtual ~RockStreet( );
public:
	void initialize( );
	void update( );
	void draw( );
private:
	std::array<ModelMV1Ptr, STREET_MODEL_NUM> _model;
};
