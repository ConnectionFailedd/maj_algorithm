#include "mahjong_exception.hpp"

#include <string>

using namespace MyMahjong::MyMahjongException;

// tile not found
inline tile_not_found::tile_not_found(Tile src_tile, const Tiles & src_tiles) noexcept : tile(src_tile), tiles(src_tiles) {}

inline const char * tile_not_found::what() const noexcept {
    return (std::string("Tile ") + tile.get_name_in_string() + " not found in tiles <" + tiles.get_tiles_in_string() + ">!").c_str();
}

/* -------------------------------------------------------------------------------- */

// string not closed
inline string_not_closed::string_not_closed(const std::string & src_str) noexcept : str(src_str) {}

inline const char * string_not_closed::what() const noexcept {
    return (std::string("String \"") + str + "\" not end with 'm', 'p', 's' or 'z'!").c_str();
}

/* -------------------------------------------------------------------------------- */

// invalid character
inline invalid_character::invalid_character(char src_c, const std::string & src_str) noexcept : c(src_c), str(src_str) {}

inline const char * invalid_character::what() const noexcept {
    return (std::string("Invalid character '") + c + "' in string \"" + str + "\"!").c_str();
}