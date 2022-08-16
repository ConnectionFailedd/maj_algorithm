#ifndef __TILE_HPP__
#define __TILE_HPP__

#include <vector>
#include <string>

namespace MyMahjong{
    enum TileName{
        _1M , _2M, _3M, _4M, _5M, _6M, _7M, _8M, _9M, _0M,
        _1P , _2P, _3P, _4P, _5P, _6P, _7P, _8P, _9P, _0P,
        _1S , _2S, _3S, _4S, _5S, _6S, _7S, _8S, _9S, _0S,
        _1Z , _2Z, _3Z, _4Z, _5Z, _6Z, _7Z,
        _ERR_TILE_NAME
    };

    enum TileType{
        M = _1M, P = _1P, S = _1S, Z = _1Z, ERR_TILE_TYPE = _ERR_TILE_NAME
    };

    class Tile{
    private:
        TileName tile_name;

    public:
        Tile(TileName = _ERR_TILE_NAME) noexcept;
        ~Tile() noexcept;

        TileName get_name() const noexcept;
        TileType get_type() const noexcept;
        std::string get_name_in_string() const;

        int get_distance_with(const Tile &) const noexcept;
        Tile get_tile_having_distance(int) const noexcept;

        bool is_red() const noexcept;
    };

    class Tiles{
    private:
        std::vector<Tile> tiles;
    
    public:
        Tiles(const std::vector<Tile> & = std::vector<Tile>(0));
        Tiles(const Tiles &);
        Tiles(const std::string &);
        ~Tiles();

        void push(const Tile &);
        void pop(const Tile &);

        std::vector<Tile> get_tiles() const;
        std::string get_tiles_in_string() const;
    };
}

#endif