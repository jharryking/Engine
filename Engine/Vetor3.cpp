#include "Vector3.h"

Vector3::Vector3(int _x, int _y, int _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void Vector3::add(Vector3 b) {
	x += b.x;
	y += b.y;
	z += b.z;
}
