#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#include <ostream>

#include "chess_array.hpp"
#include "chess_piece.hpp"

namespace chess
{

    class chess_board
    {
    public:

        chess_board();
        // chess_board is not supposed to be inherited,
        // the destructor is not virtual.
        ~chess_board();

        // Even if chess_board implements value semantic,
        // we're not supposed to have more than one instance
        // of chess board in the program. Let's ensure this by
        // deleting the copy and move constructors and operators.
        // Notice that this may change later, when we implement
        // the undo / redo mechanism.
        chess_board(const chess_board& rhs) = delete;
        chess_board& operator=(const chess_board& rhs) = delete;
        chess_board(chess_board&& rhs) = delete;
        chess_board& operator=(chess_board&& rhs) = delete;

        bool can_move(const position_type& from, const position_type& to) const;
        void move(const position_type& from, const position_type& to);

        void print(std::ostream& out) const;

    private:

        using piece_ptr = chess_piece*;
        using piece_list = std::array<piece_ptr, 16>;

        // Yes, reference on pointer ;). This allows assigning the pointer
        // a different address, making it point to another memory location.
        piece_ptr& piece(const position_type& pos);
        const piece_ptr& piece(const position_type& pos) const;

        bool has_piece(const position_type& pos, color c) const;
        bool check_bounds(const position_type& pos) const;
        // Checks that the king of color opposite to piece is not in check
        // if piece moves to new_pos.
        bool check_in_check(piece_ptr piece, const position_type& new_pos) const;
        // Checkes that king is not in check from one piece in l
        bool check_in_check(const piece_list& l, piece_ptr king) const;

        void print_separator(std::ostream& out) const;

        chess_array<std::array<chess_piece*, 8>> m_board;
        // We store the callback as a member so that we don't have to
        // instantiate it each time we need to call can_move. This is more
        // efficient.
        has_piece_callback m_callback;

        // In order to check the move of a king, we must track
        // the opposite pieces and the king's position
        // Notice that since we store pointers, once the containers
        // are initialized we never need to update them (except
        // when a piece dies, we have to reset the pointer to nullptr).
        piece_list m_white_pieces;
        piece_list m_black_pieces;
        piece_ptr p_white_king;
        piece_ptr p_black_king;

        color m_current_color;
    };
}

#endif

