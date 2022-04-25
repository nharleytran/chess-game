#include "Queen.h"

bool Chess::Queen::legal_move_shape(const Position& start, const Position& end) const 
{
    int dx = abs(end.first - start.first);
    int dy = abs(end.second - start.second);

    // dx == dy && dx > 0  - nonzero diagonal movement
    // dx == 0 && dy != 0  - vertical movement
    // dx != 0 && dy == 0  - horizontal movement
    return (dx == dy && dx > 0) || (dx == 0 && dy != 0) || (dx != 0 && dy == 0);
}

