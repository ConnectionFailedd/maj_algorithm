#ifndef __HAND_HPP__
#define __HAND_HPP__

#include <vector>
#include <string>
#include <tuple>

#include "tile.hpp"

namespace MyMahjong{
    enum BlockType{
        SHUNTSU, KOUTSU,
        RYANMEN, PENCHAN, KANCHAN, TOITSU
    };

    enum MeldType{
        ANSHUN, ANKOU, ANKANG,
        MINSHUN, MINKOU, MINKANG, KAKANG,
        ERR_MELD_TYPE
    };

    enum Player{
        SELF, RIGHT, OPPOSITE, LEFT
    };

    class Concealed: private Tiles {
    private:
        /*
         * Serial:
         * for example
         * 3p1123666s will be interpreted to
         * [ [(1, __INT_MAX__, _3P)] [(2, 1, _1S), (1, 1, _2S), (1, 3, _3S)] [(3, 0, _6S)] ]
         * every sub-vector is a independent part
         * the struct of the tuple: (int num_tiles, int distance, Tile tile_name)
         */
        typedef std::vector<std::vector<std::tuple<int, int, Tile>>> Serial;


    public:
        Concealed(const std::vector<Tile> & = std::vector<Tile>(0));
        Concealed(const Tiles &);
        Concealed(const std::string &);
        ~Concealed() noexcept;

        Concealed sort() const;

        void draw(const Tile &);
        void discard(const Tile &);

        int calc_shanten() const;

        std::vector<Tile> get_concealed() const;
        std::string get_concealed_in_string() const;
    };

    typedef bool IsRed;
    typedef Tile BaseTile, GetTile;
    typedef Player Giver;
    typedef std::tuple<GetTile, BaseTile, MeldType, Giver, IsRed> ExposedBlock;

    class Exposed{
    private:
        std::vector<ExposedBlock> exposed_list;

    public:
        Exposed(const std::vector<ExposedBlock> & = std::vector<ExposedBlock>(0));
        Exposed(const std::string &);
        ~Exposed() noexcept;

        std::vector<ExposedBlock> get_exposed();
        std::string get_exposed_in_string();
    };
};

#endif