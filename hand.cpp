#include "hand.hpp"

using namespace MyMahjong;

// Concealed
inline Concealed::Concealed(const std::vector<Tile> & src) : Tiles(src) {}

inline Concealed::Concealed(const Tiles & src) : Tiles(src) {}

inline Concealed::Concealed(const std::string & src) : Tiles(src) {}

inline Concealed::~Concealed() noexcept {}

inline Concealed Concealed::sort() const {
    auto res = get_tiles();

    std::sort(res.begin(), res.end(), [](Tile src1, Tile src2){
        if(src1.is_red()) src1 = TileName(src1.get_name() - 5);
        if(src2.is_red()) src2 = TileName(src2.get_name() - 5);
        return src1.get_name() < src2.get_name();
    });

    return res;
}

void Concealed::draw(const Tile & src){
    push(src);
}

void Concealed::discard(const Tile & src){
    try{
        pop(src);
    }
    catch(std::exception & exception){
        throw exception;
    }
}

int Concealed::calc_shanten() const{
    // todo
}

std::vector<Tile> Concealed::get_concealed() const {
    return get_tiles();
}

std::string Concealed::get_concealed_in_string() const {
    auto tiles = get_tiles();

    std::string res("");
    for(auto iter = tiles.begin(); iter + 1 != tiles.end(); iter ++){
        if(iter->get_name() == _ERR_TILE_NAME) return "ERROR TILES";

        if(iter->get_type() == (iter + 1)->get_type()){
            res += iter->get_name_in_string()[0];
        }
        else res += iter->get_name_in_string();
    }
    if(tiles.end()->get_name() == _ERR_TILE_NAME) return "ERROR TILES";

    res += tiles.end()->get_name_in_string();
    return res;
}

/* -------------------------------------------------------------------------------- */

// Exposed
inline Exposed::Exposed(const std::vector<ExposedBlock> & src) : exposed_list(src) {}

Exposed::Exposed(const std::string & src){
    // todo
}

inline Exposed::~Exposed() noexcept {}

inline std::vector<ExposedBlock> Exposed::get_exposed(){
    return exposed_list;
}

std::string Exposed::get_exposed_in_string(){
    std::string res("");
    for(auto exposed : exposed_list){
        GetTile get(std::get<0>(exposed));
        BaseTile base(std::get<1>(exposed));
        MeldType type(std::get<2>(exposed));
        Giver giver(std::get<3>(exposed));
        IsRed is_red(std::get<4>(exposed));

        if(type == ANKANG){
            res += '+';
            res += is_red ? '0' : base.get_name_in_string()[0];
            res += base.get_name_in_string()[0];
            res += '+';
            res += base.get_name_in_string()[1];
        }
        else if(type == KAKANG){
            bool red_marked = !(base.is_red() || get.is_red());
            for(int i = 0; i < 3; i ++){
                if(i == LEFT - giver){
                    res += '_';
                    res += get.get_name_in_string()[0];
                    res += '^';
                    res += base.get_name_in_string()[0];
                }
                else if(is_red && !red_marked){
                    res += '0';
                }
                else{
                    res += base.is_red() ? '5' : base.get_name_in_string()[0];
                }
            }
        }
        else{
            
        }

        res += '|';
    }
    res.pop_back();
}

/* -------------------------------------------------------------------------------- */