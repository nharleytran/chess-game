#include "Pawn.h"

bool Chess::Pawn::legal_move_shape(const Position& start, const Position& end) const
{
    int dx = end.first - start.first;
    int dy = end.second - start.second;

    if (is_white())
    {
        // pawn in starting cell
        if (start.second == '2' /* starting cell */)
            return (dx == 0 && dy == 1) || (dx == 0 && dy == 2);
        else
            return (dx == 0 && dy == 1);
    }
    else
    {
        // pawn in starting cell
        if (start.second == '7' /* starting cell */)
            return (dx == 0 && dy == -1) || (dx == 0 && dy == -2);
        else
            return (dx == 0 && dy == -1);
    }    
}


bool Chess::Pawn::legal_capture_shape(const Position& start, const Position& end) const 
{
    int dx = end.first - start.first;
    int dy = end.second - start.second;

    if (is_white())
        return abs(dx) == 1 && dy == 1;
    else
        return abs(dx) == 1 && dy == -1;
}