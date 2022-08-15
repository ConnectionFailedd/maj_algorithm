#ifndef __MAHJONG_EXCEPTION_HPP__
#define __MAHJONG_EXCEPTION_HPP__

#include "tile.hpp"

#include <exception>

namespace MyMahjong{
    namespace MyMahjongException{
        class tile_not_found: public std::exception {
        private:
            Tile tile;
            Tiles tiles;

        public:
            tile_not_found(Tile, const Tiles &) noexcept;
            const char * what() const noexcept;
        };

        class string_not_closed: public std::exception {
        private:
            std::string str;

        public:
            string_not_closed(const std::string &) noexcept;
            const char * what() const noexcept;
        };

        class invalid_character: public std::exception {
        private:
            char c;
            std::string str;

        public:
            invalid_character(char, const std::string &) noexcept;
            const char * what() const noexcept;
        };
    };
};

#endif