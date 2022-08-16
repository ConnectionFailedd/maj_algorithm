#include "tile.hpp"
#include "mahjong_exception.hpp"

using namespace MyMahjong;

// class Tile
inline Tile::Tile(TileName src) noexcept {
    if(src >= _1M && src <= _ERR_TILE_NAME) tile_name = src;
    else tile_name = _ERR_TILE_NAME;
}

inline Tile::~Tile() noexcept {}

inline TileName Tile::get_name() const noexcept {
    return tile_name;
}

inline TileType Tile::get_type() const noexcept {
    if(int(tile_name) < int(P)) return M;
    if(int(tile_name) < int(S)) return P;
    if(int(tile_name) < int(Z)) return S;
    if(int(tile_name) < int(ERR_TILE_TYPE)) return Z;
    return ERR_TILE_TYPE;
}

std::string Tile::get_name_in_string() const {
    std::string res = std::to_string((1 + tile_name) % 10);
    switch(get_type()){
        case M : return res + 'm';
        case P : return res + 'p';
        case S : return res + 's';
        case Z : return res + 'z';
        default: return "ERR_TILE_NAME";
    }
}

inline int Tile::get_distance_with(const Tile & src) const noexcept {
    if(get_type() >= Z || src.get_type() >= Z) return __INT_MAX__;
    if(get_type() != src.get_type()) return __INT_MAX__;
    return tile_name - src.tile_name;
}

Tile Tile::get_tile_having_distance(int distance) const noexcept {
    if(distance == 0) return tile_name;

    if(distance < -8 || distance > 8) return _ERR_TILE_NAME;
    if(get_type() >= Z) return _ERR_TILE_NAME;


    Tile res(TileName(tile_name + distance));
    if(is_red()) res = TileName(tile_name - 5 + distance);

    if(res.get_type() != get_type()) return _ERR_TILE_NAME;
    if(res.is_red()) return _ERR_TILE_NAME;
    return res;
}

inline bool Tile::is_red() const noexcept{
    return tile_name == _0M || tile_name ==_0P || tile_name == _0S;
}

/* -------------------------------------------------------------------------------- */

// class Tiles
inline Tiles::Tiles(const std::vector<Tile> & src) : tiles(src) {}

inline Tiles::Tiles(const Tiles & src) : tiles(src.tiles) {}

Tiles::Tiles(const std::string & src){
    tiles = std::vector<Tile>(0);

    auto iter = src.rbegin();
    while(iter != src.rend()){
        if(*iter == ' ' || *iter == '\t' || *iter == '\n' || *iter == '|') iter ++;
        else if(*iter == 'm' || *iter == 'p' || *iter == 's' || *iter == 'z') break;
        else if(*iter >= '0' && *iter <= '9') throw MyMahjongException::string_not_closed(src);
        else throw MyMahjongException::invalid_character(*iter, src);
    }

    TileType tile_type = Z;
    while(iter != src.rend()){
        switch(*iter){
            case ' ' :
            case '\t' :
            case '\n' :
            case '|' : break;
            case 'm' : {
                tile_type = M;
                break;
            }
            case 'p' : {
                tile_type = P;
                break;
            }
            case 's' : {
                tile_type = S;
                break;
            }
            case 'z' : {
                tile_type = Z;
                break;
            }
            case '1' :
            case '2' :
            case '3' :
            case '4' :
            case '5' :
            case '6' :
            case '7' :
            case '8' :
            case '9' : {
                tiles.insert(tiles.begin(), TileName(*iter - '1' + tile_type));
                break;
            }
            case '0' : {
                tiles.insert(tiles.begin(), TileName(tile_type + 9));
                break;
            }
            default : {
                throw MyMahjongException::invalid_character(*iter, src);
            }
        }
        iter ++;
    }
}

inline Tiles::~Tiles() {}

inline void Tiles::push(const Tile & src){
    tiles.push_back(src);
}

void Tiles::pop(const Tile & src){
    for(auto iter = tiles.begin(); iter != tiles.end(); iter ++){
        if(iter->get_name() == src.get_name()){
            tiles.erase(iter);
            return;
        }
    }

    throw MyMahjongException::tile_not_found(src, *this);
    return;
}

std::vector<Tile> Tiles::get_tiles() const {
    return tiles;
}

std::string Tiles::get_tiles_in_string() const {
    std::string res("");
    for(auto tile : tiles){
        if(tile.get_name() == _ERR_TILE_NAME) return "ERROR TILES";
        res += tile.get_name_in_string();
    }
    return res;
}