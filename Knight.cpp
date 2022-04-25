#include "Knight.h"

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {

    if (start.first == end.first + 1 || start.first == end.first - 1) {
      if (start.second == end.second + 2 || start.second == end.second - 2) {
        return true;
      }
    }

    if (start.first == end.first + 2 || start.first == end.first - 2) {
      if (start.second == end.second + 1 || start.second == end.second - 1) {
        return true;
      }
    }

    return false;
    
  }
}
