#pragma once
#include "Task.h"
#include <string>
#include "mathmatics.h"

PTR( RockCamera );

class RockCamera : public Task {
public:
	static std::string getTag( ) { return "ROCKCAMERA"; };
	static RockCameraPtr getTask( );
public:
	RockCamera( const Vector& pos, const Vector& target );
	virtual ~RockCamera( );
public:
	void initialize( );
	void update( );
	Vector getPos( ) const;
	Vector getTarget( ) const;
protected:
	void setPos( const Vector& pos );
	void setTarget( const Vector& target );
private:
	virtual void setCamera( ) = 0;
private:
	Vector _pos;
	Vector _target;
};