#include "King.h"

namespace Chess
{
  bool King::legal_move_shape(const Position& start, const Position& end) const {
    
    int dx = abs(end.first - start.first);
    int dy = abs(end.second - start.second);

    // dx == dy && dx == 1  - nonzero diagonal movement
    // dx == 0 && dy == 1  - vertical movement
    // dx != 0 && dy == 1  - horizontal movement

    return (dx == dy && dx == 1) || (dx == 1 && dy != 0) || (dx != 0 && dy == 1);

    return false;
  }
}