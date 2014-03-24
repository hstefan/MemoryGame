#pragma once

namespace util
{
template <class T>
T clamp(T n, T lower, T upper) {
	if (n > upper)
		return upper;
	else if (n < lower)
		return lower;
	else
		return n;
}
}