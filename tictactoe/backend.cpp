#include "backend.hpp"

std::uint8_t isDone(const std::array<std::uint8_t,9> &arr) {
    if (arr[0]+arr[4]+arr[8]==Player::white*3 || arr[6]+arr[4]+arr[2]==Player::white *3) { // diagonal check
        return Player::white;
    } else if (arr[0]+arr[4]+arr[8]==Player::black*3 || arr[6]+arr[4]+arr[2]==Player::black*3){
        return Player::black;
    }
    for (int i = 0; i < 3; i++) { // orthoganal check
        std::uint8_t s1=0;
        std::uint8_t s2=0;
        for (int j = 0; j < 3;j++) {
            s1+=arr[j+i*3];
            s2+=arr[i+j*3];
        }
        if (s1==Player::white*3) {
            return Player::white;
        } else if (s1==Player::black*3) {
            return Player::black;
        }
    }
    bool b = true; // Check if full
    for (int i = 0; i < 9;i++) {
        if (!arr[i]) {
            b = false;
        }
    }
    if (b) {
        return Player::tie;
    }
    return Player::goOn;
}

double evaluate(const std::array<std::uint8_t,9> &arr, bool turn) {
    static std::map<std::array<std::uint8_t, 9>, double> map;
    if (isDone(arr)==Player::black) {
        return -1;
    } else if (isDone(arr)==Player::white) {
        return 1;
    }else if (isDone(arr)==Player::tie) {
        return 0;
    } else {
        if (map.find(arr)==map.end()) {
            double s = 0;
            std::vector< std::array<std::uint8_t,9> > moves = generateMoves(arr, turn);
            for (int i = 0; i < moves.size();i++) {
                s+=evaluate(moves[i],!turn);
            }
            map[arr] = s/moves.size();
        }
        return map[arr];
    }
}

std::vector< std::array<std::uint8_t,9> > generateMoves(const std::array<std::uint8_t,9> &arr, bool turn) {
    std::vector< std::array<std::uint8_t,9> > ret;
    for (int i = 0; i < 9;i++) {
        if (arr[i] == Player::goOn) {
            std::array<std::uint8_t,9> t = arr;
            if (turn) {
                t[i] = Player::black;
            } else {
                t[i] = Player::white;
            }
            ret.push_back(t);
        }
    }
    return ret;
}
