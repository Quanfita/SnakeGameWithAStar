#include "AStarPoint.h"


AStarPoint::AStarPoint(Point p)
	:x(p.first), y(p.second)
{
	;
}

AStarPoint::~AStarPoint()
{
}

std::shared_ptr<AStarPoint> & AStarPoint::parent()
{
	return _parent_point;
}

int & AStarPoint::F()
{
	_f = _g + _h;
	return _f;
}

int & AStarPoint::G()
{
	return _g;
}
int & AStarPoint::H()
{
	return _h;
}

const bool AStarPoint::operator<(AStarPoint & rhs)
{
	return this->F() < rhs.F();
}

AStarPoint::operator Point()
{
	return Point(x, y);
}
