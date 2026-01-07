// ds_tetris/main.cpp
#include <array>
#include <vector>
#include <print>
#include <utility>

#include "types.hpp"

namespace ds_tetris {

enum class TetrominoType {
    I,
    O,
    T,
    S,
    Z,
    J,
    L,
    None,
};

constexpr char tetromino_to_char(TetrominoType type) {
    switch (type) {
    case TetrominoType::I:
        return 'I';
    case TetrominoType::O:
        return 'O';
    case TetrominoType::T:
        return 'T';
    case TetrominoType::S:
        return 'S';
    case TetrominoType::Z:
        return 'Z';
    case TetrominoType::J:
        return 'J';
    case TetrominoType::L:
        return 'L';
    case TetrominoType::None:
        return '*';
    }
    std::unreachable();
}

struct Tetromino {
    TetrominoType type;
    usize pos_y;
    usize pos_x;
    int cw_rotations; // Clock_wise
};

template <usize NWidth, usize NHeight>
class Gamestate {
public:
    static constexpr usize width = NWidth;
    static constexpr usize height = NHeight;

    Gamestate() { grid_.fill(TetrominoType::None); }

    TetrominoType at(usize y, usize x) const { return grid_.at(y * width + x); }
    TetrominoType at(usize idx) const { return grid_.at(idx); }
    void set(usize y, usize x, TetrominoType v) { grid_[y * width + x] = v; }
private:
    std::array<TetrominoType, NWidth * NHeight> grid_{};
    std::vector<Tetromino> active_pieces_;
};

template <usize W, usize H>
void draw_gamestate(const Gamestate<W, H> &state) {
    for (usize y = 0; y < H; ++y) {
        for (usize x = 0; x < W; ++x) {
            std::print("{}", tetromino_to_char(state.at(y, x)));
        }
        std::println();
    }
}

} // namespace ds_tetris

int main() {
    ds_tetris::Gamestate<10, 22> gamestate{};
    ds_tetris::draw_gamestate(gamestate);
}