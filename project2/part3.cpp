#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define UP 4
#define TURNED 1
#define NOT_TURNED 0
#define START_X 0
#define START_Y 0
#define EMPTY 0
#define PATH_FOUND 1
#define NO_PATH 0
#define STONE '#'
#define BAMBO '*'
#define GONE_WAY '1'


void get_board (string line, vector<vector<char>> &board) {
    int i;
    vector<char> row;

    for (i = 0; i < line.size (); i++) {
            row.push_back (line[i]);
        }

    board.push_back (row);
    row.clear ();
}

bool check_move (int x, int y, vector<vector<char>> board) {
    if (x >= board[0].size () || y >= board.size ()) {
        return false;
    }
    else if (board[y][x] == STONE) {
        return false;
    }
    else {
        return true;
    }
}

bool is_move_possiable (int panda_x, int panda_y, int move_direction, vector<vector<char>> board) {
    if (move_direction == RIGHT) {
        if (check_move (panda_x + 1, panda_y, board) == false && check_move (panda_x, panda_y - 1, board) == false && 
            check_move (panda_x, panda_y + 1, board) == false) {
            return false;
        }
        else {
            return true;
        }
    }

    else if (move_direction == DOWN) {
        if (check_move (panda_x, panda_y + 1, board) == false && check_move (panda_x + 1, panda_y, board) == false && 
            check_move (panda_x - 1, panda_y, board) == false) {
            return false;
        }
        else {
            return true;
        }
    }

    else if (move_direction == LEFT) {
        if (check_move (panda_x - 1, panda_y, board) == false && check_move (panda_x, panda_y - 1, board) == false && 
            check_move (panda_x, panda_y + 1, board) == false) {
            return false;
        }
        else {
            return true;
        }
    }

    else if (move_direction == UP) {
        if (check_move (panda_x, panda_y - 1, board) == false && check_move (panda_x + 1, panda_y, board) == false && 
            check_move (panda_x - 1, panda_y, board) == false) {
            return false;
        }
        else {
            return true;
        }
    }

    return false;
}

void move_up (int &x, int &y) {
    y = y - 1;
}

void move_down (int &x, int &y) {
    y = y + 1;
}

void move_right (int &x, int &y) {
    x = x + 1;
}

void move_left (int &x, int &y) {
    x = x - 1;
}

int count_moves (vector<vector<char>> board) {
    int count = 0;
    int i;
    int j;

    for (i = 0; i < board.size (); i++) {
        for (j = 0; j < board[i].size (); j++) {
            if (board[i][j] == GONE_WAY) {
                count = count + 1;
            }
        }
    }

    return count;
}

int move_panda (int panda_x, int panda_y, int move_direction, int &turn, vector<vector<char>> &board, vector<int> &ways) {
    int count;
    vector<vector<char>> board_copy;
     
    while (true) {
        if (board[panda_y][panda_x] == BAMBO) {
            count = count_moves (board);
            ways.push_back (count);
            return PATH_FOUND;
        }

        if (move_direction == RIGHT) {
            if (check_move (panda_x + 1, panda_y, board) == true) {
                board[panda_y][panda_x] = GONE_WAY;
                move_right (panda_x, panda_y);
                turn = NOT_TURNED;
            }
            else {
                break;
            }
        }

        else if (move_direction == DOWN) {
           if (check_move (panda_x, panda_y + 1, board) == true) {
               board[panda_y][panda_x] = GONE_WAY;
               move_down (panda_x, panda_y);
               turn = NOT_TURNED;
           }
           else {
               break;
           }
        }

        else if (move_direction == LEFT) {
           if (check_move (panda_x - 1, panda_y, board) == true) {
               board[panda_y][panda_x] = GONE_WAY;
               move_left (panda_x, panda_y);
               turn = NOT_TURNED;
           }
           else {
               break;
           }
        }

        else if (move_direction == UP) {
           if (check_move (panda_x, panda_y - 1, board) == true) {
               board[panda_y][panda_x] = GONE_WAY;
               move_up (panda_x, panda_y);
               turn = NOT_TURNED;
           }
           else {
               break;
           }
        }
    }

    if (is_move_possiable (panda_x, panda_y, move_direction, board) == false || board[panda_y][panda_x] == GONE_WAY) {
       return NO_PATH;
    }

    if (turn == NOT_TURNED) {
        if (move_direction == RIGHT) {
            move_direction = DOWN;
            board_copy = board;
            turn = TURNED;
            move_panda (panda_x, panda_y, move_direction, turn, board_copy, ways);

            move_direction = UP;
            board_copy = board;
            turn = TURNED;
            move_panda (panda_x, panda_y, move_direction, turn, board_copy, ways);
        }

        else if (move_direction == DOWN) {
            move_direction = RIGHT;
            board_copy = board;
            turn = TURNED;
            move_panda (panda_x, panda_y, move_direction, turn, board_copy, ways);

            move_direction = LEFT;
            board_copy = board;
            turn = TURNED;
            move_panda (panda_x, panda_y, move_direction, turn, board_copy, ways);
        }

        else if (move_direction == LEFT) {
            move_direction = DOWN;
            board_copy = board;
            turn = TURNED;
            move_panda (panda_x, panda_y, move_direction, turn, board_copy, ways);

            move_direction = UP;
            board_copy = board;
            turn = TURNED;
            move_panda (panda_x, panda_y, move_direction, turn, board_copy, ways);
        }

        else if (move_direction == UP) {
            move_direction = RIGHT;
            board_copy = board;
            turn = TURNED;
            move_panda (panda_x, panda_y, move_direction, turn, board_copy, ways);

            move_direction = LEFT;
            board_copy = board;
            turn = TURNED;
            move_panda (panda_x, panda_y, move_direction, turn, board_copy, ways);
        }
    }

    return NO_PATH;
}

void print_result (vector<int> ways) {
    int min_count;
    if (ways.size () > EMPTY) {
        min_count = *min_element (ways.begin (), ways.end ());
        cout << min_count << endl;
    }
    else {
        cout << "No path found" << endl;
    }
}

int main () {
    int panda_x;
    int panda_y;
    int move_direction;
    int min_count;
    int turn = NOT_TURNED;
    int i;
    vector<vector<char>> board;
    vector<vector<char>> board_copy;
    vector<int> ways;
    string line;
    
    while (cin >> line) {
        get_board (line, board);
    }
    
    panda_x = START_X;
    panda_y = START_Y;

    move_direction = DOWN;
    board_copy = board;
    move_panda (panda_x, panda_y, move_direction, turn, board_copy, ways);

    move_direction = RIGHT;
    board_copy = board;
    move_panda (panda_x, panda_y, move_direction, turn, board_copy, ways);

    print_result (ways);
    
    return 0;
}