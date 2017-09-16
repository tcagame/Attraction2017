#include "Enemy.h"

class EnemyLancer : public Enemy {
public:
	EnemyLancer( const Vector& pos );
	virtual ~EnemyLancer( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

