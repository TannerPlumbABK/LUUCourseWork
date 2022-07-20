#pragma once

template <typename Type>
struct Point
{
	Type x;
	Type y;

	Point(Type x = 0, Type y = 0) : x(x), y(y) { }
};