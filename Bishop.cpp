#include "Bishop.h"
#include <stdlib.h>
namespace Chess
{
  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {

    int dx = abs(end.first - start.first);
    int dy = abs(end.second - start.second);
    // dx == dy && dx > 0  - nonzero diagonal movement
    return (dx == dy && dx > 0);

}
}
