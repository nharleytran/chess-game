#include "Rook.h"

namespace Chess
{

  bool Rook::legal_move_shape(const Position &start, const Position &end) const
  {

    // vertical movement
    if (start.first == end.first && start.second != end.second)
    {
      return true;
    }

    // horizontal movement
    if (start.first != end.first && start.second == end.second)
    {
      return true;
    }

    else
    {
      return false;
    }
  }

}
