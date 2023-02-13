#include<iostream>
#include<cmath>
#include "Entity_run.hpp"
#include "Entity.hpp"
Entity_run::Entity_run(float E_x, float E_y, float E_x0, float E_y0)
	:x(E_x), y(E_y), x0(E_x0), y0(E_y0)
{
	float S = sqrt((x0 - x) * (x0 - x) + (y0 - y) * (y0 - y));

}

