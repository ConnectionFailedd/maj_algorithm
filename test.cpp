#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "hand.hpp"

int main(){
    srand(time(NULL));
    for(int i = 0; i < 20; i ++){
        std::string test_str;
        for(int j = 0; j < 13; j ++){
            switch(rand() % 4){
                case 0 : {
                    test_str.insert(test_str.end(), '0' + rand() % 9);
                    test_str.insert(test_str.end(), 'm');
                    break;
                }
                case 1 : {
                    test_str.insert(test_str.end(), '0' + rand() % 9);
                    test_str.insert(test_str.end(), 'p');
                    break;
                }
                case 2 : {
                    test_str.insert(test_str.end(), '0' + rand() % 9);
                    test_str.insert(test_str.end(), 's');
                    break;
                }
                case 3 : {
                    test_str.insert(test_str.end(), '1' + rand() % 7);
                    test_str.insert(test_str.end(), 'z');
                    break;
                }
            }
        }
        MyMahjong::Hand hand(test_str);
        auto hand_sorted = hand.sort();
        std::cout << "Case " << i + 1 << std::endl;
        std::cout << "Generated hand: " << test_str <<std::endl;
        std::cout << "After sorting: ";
        for(auto iter = hand_sorted.begin(); iter != hand_sorted.end(); iter ++){
            std::cout << (*iter + 1) % 10;
            if(iter + 1 == hand_sorted.end() || MyMahjong::get_type(*iter) != MyMahjong::get_type(*(iter + 1))){
                switch(MyMahjong::get_type(*iter)){
                    case MyMahjong::M : {
                        std::cout << 'm';
                        break;
                    }
                    case MyMahjong::P : {
                        std::cout << 'p';
                        break;
                    }
                    case MyMahjong::S : {
                        std::cout << 's';
                        break;
                    }
                    case MyMahjong::Z : {
                        std::cout << 'z';
                        break;
                    }
                }
            }
        }
        std::cout << std::endl;
        std::cout << "Shanten: " << MyMahjong::Hand(test_str).calc_shanten() << std::endl << std::endl;
    }
}