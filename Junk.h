#include "Object.h"

#define JUNK_MAX (10)			//ガラクタの数

class Junk :
	public Object
{
public:
	Junk();
	~Junk();
	void update();
};

