#include "backend.hpp"
#include <exception>
#include <limits>

void printBoard(const std::array<std::uint8_t,9> &arr) {
    for (int i = 1; i <= 9; i++) {
        if (!((i-1)%3)) {
            std::cout << "\t";
        }
        if (arr[i-1] == Player::white) {
            std::cout << 'x';
        } else if (arr[i-1]==Player::black) {
            std::cout << 'o';
        } else {
            std::cout << '.';
        }
        if (!(i%3)) {
            std::cout << std::endl;;
        }
    }
}

void printHelp() {
    std::cout <<
    "\texit - to exit\n"
    "\tshow - to show the board\n"
    "\tturn - to check the current turn\n"
    "\tplay \"x\" - to put a stone as shown here:\n"
    "\t1 2 3\n"
    "\t4 5 6\n"
    "\t7 8 9"
    << std::endl;
}

void playMove(std::array<std::uint8_t,9> &arr, bool &turn, bool isAi) {
    std::string s; std::cin >> s;
    try {
        int a = std::stoi(s);
        if (a>0 && a<=9 && (arr[a-1]==Player::goOn)) {
            if (turn) {
                arr[a-1] = Player::black;
            } else {
                arr[a-1] = Player::white;
            }
            std::cout << "\tmove registered" << std::endl;
            if (!isAi) {
                turn = !turn;
            }
        } else {
            throw std::exception();
        }
    }
    catch(std::exception e) {
        std::cout << "\tinvalid move: try again" << std::endl;
    }
}

void playMoveAi(std::array<std::uint8_t,9> &arr, bool turn) {
    std::vector< std::array<std::uint8_t,9> > moves = generateMoves(arr, turn);
    std::vector<double> evals;
    int index = 0;
    for (int i = 0; i < moves.size();i++) {
        evals.push_back(evaluate(moves[i], turn));
    }
    if (!turn) {
        double max=std::numeric_limits<double>::min();
        for (int i = 0; i < evals.size();i++) {
            if (evals[i]>max) {
                max=evals[i];
                index=i;
            }
        }
    } else {
        double min = std::numeric_limits<double>::max();
        for (int i = 0; i <evals.size();i++) {
            if (evals[i]<min) {
                min=evals[i];
                index=i;
            }
        }
    }
    arr = moves[index];
    std::cout << "\tThe AI played " << std::endl;
}

void playLocal() {
    std::array<std::uint8_t,9> arr;
    bool turn = false;
    std::fill(arr.begin(), arr.end(),0);

    printHelp();
    do {
        std::string n; std::cin >> n;
        if (n=="exit") {
            std::exit(0);
        }
        else if (n=="help") {
            printHelp();
        }
        else if (n=="turn") {
            if (turn) {
                std::cout << "\tblack" << std::endl;
            } else {
                std::cout << "\twhite" << std::endl;
            }
        }
        else if (n=="play") {
            playMove(arr, turn, false);
        }
        else if (n=="show") {
            printBoard(arr);
        }
        else {
            std::cout << "\tunknown command: try again" << std::endl;
        }
    } while (isDone(arr)==Player::goOn);
    if (isDone(arr)==Player::black) {
        std::cout << "\n\tblack won!\n" << std::endl;
    }
    else if (isDone(arr)==Player::white) {
        std::cout << "\n\twhite won!\n" << std::endl;
    } else {
        std::cout << "\n\tit's a tie!\n";
    }
    printBoard(arr);
}

void playAi() {
    std::array<std::uint8_t,9> arr;
    bool turn;
    std::fill(arr.begin(), arr.end(),0);
    
    while (true) {
        std::cout << "What color are you playing as? [white/black]" << std::endl;
        std::string n; std::cin >> n;
        if (n == "white") {
            turn = false;
            break;
        } else if (n=="black"){
            turn = true;
            break;
        }
    }
    printHelp();
    if (turn) {
        playMoveAi(arr, false);
    }
    do {
        std::string n; std::cin >> n;
        if (n=="exit") {
            std::exit(0);
        }
        else if (n=="help") {
            printHelp();
        }
        else if (n=="turn") {
            if (turn) {
                std::cout << "\tblack" << std::endl;
            } else {
                std::cout << "\twhite" << std::endl;
            }
        }
        else if (n=="play") {
            playMove(arr, turn, true);
            turn=!turn;
            playMoveAi(arr, !turn);
        }
        else if (n=="show") {
            printBoard(arr);
        }
        else {
            std::cout << "\tunknown command: try again" << std::endl;
        }
    } while (isDone(arr)==Player::goOn);
    if (isDone(arr)==Player::black) {
        std::cout << "\n\tblack won!\n" << std::endl;
    }
    else if (isDone(arr)==Player::white) {
        std::cout << "\n\twhite won!\n" << std::endl;
    } else {
        std::cout << "\n\tit's a tie!\n";
    }
    printBoard(arr);
}

int main(int argc, const char * argv[]) {
    if (argc>1) {
        if ((std::string)argv[1]=="free") {
            playLocal();
        } else if ((std::string)argv[1]=="ai") {
            playAi();
        } else {
            std::cout <<
            "usage:\n"
            "\tfree - to play by yourself or with a friend\n"
            "\tai - to play with the ai"
            << std::endl;
        }
    } else {
        std::cout <<
        "usage:\n"
        "\tfree - to play by yourself or with a friend\n"
        "\tai - to play with the ai"
        << std::endl;
    }
    return 0;
}
