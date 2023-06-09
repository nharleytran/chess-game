#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"

namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board() {}

  Board::Board(const Board &rhs)
  {
    *this = rhs;
  }

  Board &Board::operator=(const Board &rhs)
  {
    // deallocate memory before copy
    for (char r = '8'; r >= '1'; r--)
    {
      for (char c = 'A'; c <= 'H'; c++)
      {
        if (occ.find(Position(c, r)) != occ.end())
        {
          erase_piece(Position(c, r));
        }
      }
    }
    // copy here
    for (std::map<Position, Piece *>::const_iterator it = rhs.occ.begin();
         it != rhs.occ.end();
         it++)
    {
      this->add_piece(it->first, it->second->to_ascii());
    }
    return *this;
  }

  Board ::~Board()
  {
    for (char r = '8'; r >= '1'; r--)
    {
      for (char c = 'A'; c <= 'H'; c++)
      {
        if (occ.find(Position(c, r)) != occ.end())
        {
          erase_piece(Position(c, r));
        }
      }
    }
  }

  Position Board::get_king(const bool white) const
  {
    Position x;
    if (white)
    {
      for (std::map<Position, Piece *>::const_iterator it = occ.begin();
           it != occ.end();
           it++)
      {
        if ((*it->second).to_ascii() == 'K')
        {
          x = it->first;
        }
      }
    }
    else
    {
      for (std::map<Position, Piece *>::const_iterator it = occ.begin();
           it != occ.end();
           it++)
      {
        if ((*it->second).to_ascii() == 'k')
        {
          x = it->first;
        }
      }
    }
    return x;
  }

  const Piece *Board::operator()(const Position &position) const
  {
    if (occ.find(position) != occ.end())
      return occ.at(position);
    else
      return nullptr;
  }

  void Board::promote(const Position &position, const bool white)
  {

    // white piece promotion
    if (white)
    {
      erase_piece(position);
      add_piece(position, 'Q');
    }

    // black piece promotion
    else
    {
      erase_piece(position);
      add_piece(position, 'q');
    }
  }

  void Board::add_piece(const Position &position, const char &piece_designator)
  {

    // invalid designator
    Piece *new_piece = create_piece(piece_designator);
    if (new_piece == nullptr)
    {
      throw Exception("invalid designator\n");
    }
    // invalid position
    int flag = 0;
    for (char r = '8'; r >= '1'; r--)
    {
      if (position.second == r)
      {
        flag++;
      }
    }
    for (char c = 'A'; c <= 'H'; c++)
    {
      if (position.first == c)
      {
        flag++;
      }
    }
    if (flag != 2)
    {
      throw Exception("invalid position\n");
    }

    // position is occupied
    if (occ.find(position) != occ.end())
    {
      throw Exception("position is occupied");
    }

    // create new piece at given position
    occ[position] = new_piece;
  }

  void Board::display() const
  {
    // make output pretty
    Terminal ::color_fg(true, Terminal::RED);
    std::cout << "   A  B  C  D  E  F  G  H"
              << "\n";
    int i = 8;
    Terminal ::color_fg(true, Terminal::RED);
    for (char r = '8'; r >= '1'; r--)
    {
      std::cout << i << " ";
      for (char c = 'A'; c <= 'H'; c++)
      {
        if (occ.find(Position(c, r)) != occ.end())
        {
          Terminal ::color_fg(true, Terminal::RED);

          if (c % 2 != 0 && r % 2 != 0)
          {
            Terminal ::color_bg(Terminal::BLACK);
            switch (occ.at(Position(c, r))->to_ascii())
            {
            case 'R':
              std::cout << " ♖ ";
              break;
            case 'K':
              std::cout << " ♔ ";
              break;
            case 'Q':
              std::cout << " ♕ ";
              break;
            case 'N':
              std::cout << " ♘ ";
              break;
            case 'P':
              std::cout << " ♙ ";
              break;
            case 'B':
              std::cout << " ♗ ";
              break;
            case 'r':
              std::cout << " ♜ ";
              break;
            case 'k':
              std::cout << " ♚ ";
              break;
            case 'q':
              std::cout << " ♛ ";
              break;
            case 'n':
              std::cout << " ♞ ";
              break;
            case 'p':
              std::cout << " ♟ ";
              break;
            case 'b':
              std::cout << " ♝ ";
              break;
            case 'm':
              std::cout << " ? ";
              break;
            case 'M':
              std::cout << " ඞ ";
              break;
            default:
              break;
            }
          }
          if (c % 2 == 0 && r % 2 != 0)
          {
            Terminal ::color_bg(Terminal::WHITE);
            switch (occ.at(Position(c, r))->to_ascii())
            {
            case 'R':
              std::cout << " ♖ ";
              break;
            case 'K':
              std::cout << " ♔ ";
              break;
            case 'Q':
              std::cout << " ♕ ";
              break;
            case 'N':
              std::cout << " ♘ ";
              break;
            case 'P':
              std::cout << " ♙ ";
              break;
            case 'B':
              std::cout << " ♗ ";
              break;
            case 'r':
              std::cout << " ♜ ";
              break;
            case 'k':
              std::cout << " ♚ ";
              break;
            case 'q':
              std::cout << " ♛ ";
              break;
            case 'n':
              std::cout << " ♞ ";
              break;
            case 'p':
              std::cout << " ♟ ";
              break;
            case 'b':
              std::cout << " ♝ ";
              break;
            case 'm':
              std::cout << " ? ";
              break;
            case 'M':
              std::cout << " ඞ ";
              break;
            default:
              break;
            }
          }
          if (c % 2 == 0 && r % 2 == 0)
          {
            Terminal ::color_bg(Terminal::BLACK);
            switch (occ.at(Position(c, r))->to_ascii())
            {
            case 'R':
              std::cout << " ♖ ";
              break;
            case 'K':
              std::cout << " ♔ ";
              break;
            case 'Q':
              std::cout << " ♕ ";
              break;
            case 'N':
              std::cout << " ♘ ";
              break;
            case 'P':
              std::cout << " ♙ ";
              break;
            case 'B':
              std::cout << " ♗ ";
              break;
            case 'r':
              std::cout << " ♜ ";
              break;
            case 'k':
              std::cout << " ♚ ";
              break;
            case 'q':
              std::cout << " ♛ ";
              break;
            case 'n':
              std::cout << " ♞ ";
              break;
            case 'p':
              std::cout << " ♟ ";
              break;
            case 'b':
              std::cout << " ♝ ";
              break;
            case 'm':
              std::cout << " ? ";
              break;
            case 'M':
              std::cout << " ඞ ";
              break;
            default:
              break;
            }
          }
          if (c % 2 != 0 && r % 2 == 0)
          {
            Terminal ::color_bg(Terminal::WHITE);
            switch (occ.at(Position(c, r))->to_ascii())
            {
            case 'R':
              std::cout << " ♖ ";
              break;
            case 'K':
              std::cout << " ♔ ";
              break;
            case 'Q':
              std::cout << " ♕ ";
              break;
            case 'N':
              std::cout << " ♘ ";
              break;
            case 'P':
              std::cout << " ♙ ";
              break;
            case 'B':
              std::cout << " ♗ ";
              break;
            case 'r':
              std::cout << " ♜ ";
              break;
            case 'k':
              std::cout << " ♚ ";
              break;
            case 'q':
              std::cout << " ♛ ";
              break;
            case 'n':
              std::cout << " ♞ ";
              break;
            case 'p':
              std::cout << " ♟ ";
              break;
            case 'b':
              std::cout << " ♝ ";
              break;
            case 'm':
              std::cout << " ? ";
              break;
            case 'M':
              std::cout << " ඞ ";
              break;
            default:
              break;
            }
          }
          Terminal ::set_default();
        }
        else
        {
          if (c % 2 != 0 && r % 2 == 0)
          {
            Terminal ::color_bg(Terminal::WHITE);
            std::cout << "   ";
            Terminal ::set_default();
          }
          if (c % 2 == 0 && r % 2 == 0)
          {
            Terminal ::color_bg(Terminal::BLACK);
            std::cout << "   ";
            Terminal ::set_default();
          }
          if (c % 2 == 0 && r % 2 != 0)
          {
            Terminal ::color_bg(Terminal::WHITE);
            std::cout << "   ";
            Terminal ::set_default();
          }
          if (c % 2 != 0 && r % 2 != 0)
          {
            Terminal ::color_bg(Terminal::BLACK);
            std::cout << "   ";
            Terminal ::set_default();
          }
        }
      }
      Terminal ::color_fg(true, Terminal::RED);
      std::cout << " " << i;
      i--;
      std::cout << std::endl;
    }
    Terminal ::color_fg(true, Terminal::RED);
    std::cout << "   A  B  C  D  E  F  G  H"
              << "\n";
    Terminal ::set_default();
  }

  void Board::erase_piece(const Position &position)
  {
    delete occ.at(position);
    occ.erase(position);
  }

  void Board::move_piece(const Position &start, const Position &end)
  {
    add_piece(end, occ.at(start)->to_ascii());
    erase_piece(start);
    // promote piece if needed
    if (occ.at(end)->to_ascii() == 'P' && end.second == '8')
    { // white pawn
      bool white = true;
      promote(end, white);
    }
    if (occ.at(end)->to_ascii() == 'p' && end.second == '1')
    { // black pawn
      bool white = false;
      promote(end, white);
    }
  }

  bool Board::has_valid_kings() const
  {
    int white_king_count = 0;
    int black_king_count = 0;
    for (std::map<std::pair<char, char>, Piece *>::const_iterator it = occ.begin();
         it != occ.end();
         it++)
    {
      if (it->second)
      {
        switch (it->second->to_ascii())
        {
        case 'K':
          white_king_count++;
          break;
        case 'k':
          black_king_count++;
          break;
        }
      }
    }
    return (white_king_count == 1) && (black_king_count == 1);
  }
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream &operator<<(std::ostream &os, const Board &board)
  {
    for (char r = '8'; r >= '1'; r--)
    {
      for (char c = 'A'; c <= 'H'; c++)
      {
        const Piece *piece = board(Position(c, r));
        if (piece)
        {
          os << piece->to_ascii();
        }
        else
        {
          os << '-';
        }
      }
      os << std::endl;
    }
    return os;
  }
}
