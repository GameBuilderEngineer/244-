
#include "Object.h"

namespace colonyNS {
	enum {
		COLONY1,
		COLONY2,
		COLONY_NUM,
	};
}

class Colony :
	public Object
{
public:
	Colony();
	~Colony();
	//virtual void update()override;
	void update();
};

