#ifndef ROOK_HPP
#define ROOK_HPP

#include "chess_piece.hpp"

namespace chess
{
    
    class rook : public chess_piece
    {
    public:

        rook(color c, const position_type& pos);
        virtual ~rook() = default;
        
        bool can_move(const position_type& new_pos,
                      const has_piece_callback& cb) const override;
        void print(std::ostream& out) const override;
    };
}

#endif

