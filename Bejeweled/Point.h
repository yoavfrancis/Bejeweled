#ifndef __GameTest_Point_h__
#define __GameTest_Point_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <utility>

namespace game {

/// Represents a 2d point/coordinate.
typedef std::pair<int, int> Point;

} // namespace game

#endif // __GameTest_Point_h__