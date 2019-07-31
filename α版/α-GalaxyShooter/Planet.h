#pragma once
#include "Object.h"
#include "BoundingSphere.h"
class Planet :public Object
{
public:
	Planet();
	~Planet();
	void update();

};

