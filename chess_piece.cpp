#include "chess_piece.hpp"

namespace chess
{
    color chess_piece::get_color() const
    {
        return m_color;
    }

    const position_type& chess_piece::get_position() const
    {
        return m_position;
    }

    void chess_piece::move(const position_type& new_pos)
    {
        m_position = new_pos;
    }

    chess_piece::chess_piece(color c, const position_type& pos)
        : m_color(c), m_position(pos)
    {
    }

    std::ostream& operator<<(std::ostream& out, const chess_piece& pce)
    {
        pce.print(out);
        return out;
    }
}

