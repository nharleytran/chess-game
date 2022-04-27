#include "Rook.h"

namespace Chess
{

  bool Rook::legal_move_shape(const Position& start, const Position& end) const {

    // vertical movement
    if (start.first == end.first && start.second != end.second) {
      return true;
    }

    // horizontal movement
    if (start.first != end.first && start.second == end.second) {
      return true;
    }

    else {
      return false;
    }
    
  }

  // bool Rook::obstruction_check(const Position& start, const Position& end, const Board& board) const {

  //   // vertical movement
  //   if (start.first == end.first) {
  //     if (start.second < end.second) {
  //       for (char row = start.second + 1; row < end.second; row++) {
  //         Position tmp = Position(start.first, row);
  //         if (board(tmp) != nullptr) {
  //           return false;
  //         }
  //       }
  //     }
  //     else {
  //       for (char row = end.second + 1; row < start.second; row++) {
  //         Position tmp = Position(start.first, row);
  //         if (board(tmp) != nullptr) {
  //           return false;
  //         }
  //       }
  //     }
  //   }

  //   // horizontal movement
  //   else {
  //     if (start.first < end.first) {
  //       for (char col = start.first + 1; col < end.first; col++) {
  //         Position tmp = Position(col, start.second);
  //         if (board(tmp) != nullptr) {
  //           return false;
  //         }
  //       }
  //     }
  //     else {
  //       for (char col = end.first + 1; col < start.second; col++) {
  //         Position tmp = Position(col, start.second);
  //         if (board(tmp) != nullptr) {
  //           return false;
  //         }
  //       }
  //     }

  //   }

    return true;

  }

}
