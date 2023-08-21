#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


#define STARTED 1
#define NOT_START 0
#define COUNTER_TERRORIST 1
#define TERRORIST 2
#define AFK 0
#define ATK 1
#define MAX_HEALTH 100
#define INITIAL_MONEY 1000
#define KNIFE_COST 0
#define KNIFE_DAMAGE 35
#define KNIFE_LOOT 500
#define PISTOL_COST 400
#define PISTOL_DAMAGE 20
#define PISTOL_LOOT 200
#define HEAVY_COST 3000
#define HEAVY_DAMAGE 45
#define HEAVY_LOOT 100
#define NOT_FIND -1
#define WINNER_GIFT 2700
#define LOSER_GIFT 2400
#define MAX_MONEY 10000
#define KNIFE_NAME "knife"
#define PISTOL_NAME "pistol"
#define HEAVY_NAME "heavy"


class Gun {
    public:
        Gun (string input_name, int input_damage, int input_cost, int input_loot);

        string get_name ();

        int get_damage ();

        int get_gun_loot ();

        int get_cost ();

    private:
        string name;
        int damage;
        int cost;
        int gun_loot;
};

class Player {
    public:
        Player (int input_group, string input_username);

        int get_money ();

        int get_health ();

        string get_username ();

        int get_status ();

        int get_group ();

        int get_kills ();

        int get_deaths ();

        void change_status (int input_status); 

        int find_existed_gun (string gun_name);

        int gun_loot (int gun_index);

        void set_health_max ();

        bool is_in_same_team (Player player2);

        void decrease_health (int input_damage);

        void check_money ();

        void shoot_player (int gun_index, Player &player2);

        void buy_gun (Gun input_gun);

        bool is_alive ();

        void increase_kills ();

        void increase_deaths ();

        void reset_guns ();

        void increase_money (int input_cash);

        void print_scores ();

        bool is_money_enought (int cost);

    private:
        string username;
        int health;
        int money;
        int group;
        int status;
        int kills;
        int deaths;
        vector<Gun> guns;
};


Gun::Gun (string input_name, int input_damage, int input_cost, int input_gun_loot) {
            name = input_name;
            damage = input_damage;
            cost = input_cost;
            gun_loot = input_gun_loot;
}

string Gun::get_name () {
    return name;
}

int Gun::get_damage () {
    return damage;
}

int Gun::get_gun_loot () {
    return gun_loot;
}

int Gun::get_cost () {
    return cost;
}


Player::Player (int input_group, string input_username) {
    health = MAX_HEALTH;
    group = input_group;
    status = ATK;
    username = input_username;
    money = INITIAL_MONEY;
    kills = 0;
    deaths = 0;
    Gun initial_gun (KNIFE_NAME, KNIFE_DAMAGE, KNIFE_COST, KNIFE_LOOT);
    guns.push_back (initial_gun);
}

int Player::get_money () {
    return money;
}

int Player::get_health () {
    return health;
}

string Player::get_username () {
    return username;
}

int Player::get_status () {
    return status;
}

int Player::get_group () {
    return group;
}

int Player::get_kills () {
    return kills;
}

int Player::get_deaths () {
    return deaths;
}

void Player::change_status (int input_status) {
    status = input_status;
}

int Player::find_existed_gun (string gun_name) {
    int i;

    for (i = 0; i < guns.size (); i++) {
        if (gun_name == guns[i].get_name ()) {
            return i;
        }
    }

    return NOT_FIND;
}

int Player::gun_loot (int gun_index) {
    return guns[gun_index].get_gun_loot ();
}

void Player::set_health_max () {
    health = MAX_HEALTH;
}

bool Player::is_in_same_team (Player player2) {
    if (group == player2.group) {
        return true;
    }
    else {
        return false;
    }
}

void Player::decrease_health (int input_damage) {
    health = health - input_damage;
    if (health < 0) {
        health = 0;
    }
}

void Player::check_money () {
    if (money > MAX_MONEY) {
        money = MAX_MONEY;
    }
}

void Player::shoot_player (int gun_index, Player &player2) {
    player2.decrease_health (guns[gun_index].get_damage ());
}

void Player::buy_gun (Gun input_gun) {
    guns.push_back (input_gun);
    money = money - input_gun.get_cost ();
}

bool Player::is_alive () {
    if (health > 0) {
        return true;
    }
    else {
        return false;
    }
}

void Player::increase_kills () {
    kills = kills + 1;
}

void Player::increase_deaths () {
    deaths = deaths + 1;
}

void Player::reset_guns () {
    Gun initial_gun (KNIFE_NAME, KNIFE_DAMAGE, KNIFE_COST, KNIFE_LOOT);

    guns.clear ();
    guns.push_back (initial_gun);
}

void Player::increase_money (int input_cash) {
    money = money + input_cash;
    check_money ();
}

void Player::print_scores () {
    cout << username << " " << kills << " " << deaths << endl;
}

bool Player::is_money_enought (int cost) {
    if (money >= cost) {
        return true;
    }
    else {
        return false;
    }
}


vector<string> separate_command (string commands) {
    vector<string> command_words;
    string word;

    istringstream ss (commands);

    while (ss >> word) {
        command_words.push_back (word);
    }

    return command_words;    
}

vector<Gun> add_guns () {
    vector<Gun> guns_list;
    Gun gun1 (KNIFE_NAME, KNIFE_DAMAGE, KNIFE_COST, KNIFE_LOOT);
    guns_list.push_back (gun1);

    Gun gun2 (PISTOL_NAME, PISTOL_DAMAGE, PISTOL_COST, PISTOL_LOOT);
    guns_list.push_back (gun2);

    Gun gun3 (HEAVY_NAME, HEAVY_DAMAGE, HEAVY_COST, HEAVY_LOOT);
    guns_list.push_back (gun3);

    return guns_list;
}

void start (int &game_status) {
    game_status = STARTED;

    cout << "fight!" << endl;
}

int find_player (string username, vector<Player> players_list) {
    int i;

    for (i = 0; i < players_list.size (); i++) {
        if (players_list[i].get_username () == username) {
            return i;
        }
    }

    return NOT_FIND;
}

int find_gun (string gun_name, vector<Gun> guns_list) {
    int i;

    for (i = 0; i < guns_list.size (); i++) {
        if (guns_list[i].get_name () == gun_name) {
            return i;
        }
    }

    return NOT_FIND;
}

void add_user (string username, int group, vector<Player> &players_list) {
    Player player (group, username);

    players_list.push_back (player);

    cout << "ok" << endl;
}

void get_money (string username, vector<Player> players_list) {
    int index = find_player (username, players_list);

    cout << players_list[index].get_money () << endl;
}

void get_health (string username, vector<Player> players_list) {
    int index = find_player (username, players_list);

    cout << players_list[index].get_health () << endl;
}

void go_afk (string username, vector<Player> &players_list) {
    int index = find_player (username, players_list);

    players_list[index].change_status (AFK);

    cout << "ok" << endl;
}

void go_atk (string username, vector<Player> &players_list) {
    int index = find_player (username, players_list);

    players_list[index].change_status (ATK);

    cout << "ok" << endl;
}

int is_shoot_possiable (int attacker_index, int attacked_index, int gun_index, string gun_name, vector<Player> players_list) {
    if (attacker_index == NOT_FIND || attacked_index == NOT_FIND) {
        cout << "user not available" << endl;
        return false;
    }

    if (players_list[attacker_index].get_status () == AFK || players_list[attacked_index].get_status () == AFK) {
        cout << "user not available" << endl;
        return false;
    }

    if (players_list[attacker_index].is_alive () == false) {
        cout << "attacker is dead" << endl;
        return false;
    }

    if (players_list[attacked_index].is_alive () == false) {
        cout << "attacked is dead" << endl;
        return false;
    }

    if (gun_index == NOT_FIND) {
        cout << "attacker doesn't have this gun" << endl;
        return false;
    }

    if (players_list[attacker_index].is_in_same_team (players_list[attacked_index]) == true) {
        cout << "you can't shoot this player" << endl;
        return false;
    }

    return true;
}

void shoot (string attacker, string attacked, string gun_name, vector<Player> &players_list) {
    int attacker_index;
    int attacked_index;
    int gun_index;

    attacker_index = find_player (attacker, players_list);
    attacked_index = find_player (attacked, players_list);

    if (attacker_index != NOT_FIND) {
        gun_index = players_list[attacker_index].find_existed_gun (gun_name);
    }

   if (is_shoot_possiable (attacker_index, attacked_index, gun_index, gun_name, players_list) == true) {
       players_list[attacker_index].shoot_player (gun_index, players_list[attacked_index]);

       cout << "nice shot" << endl;

       if (players_list[attacked_index].is_alive () == false) {
           players_list[attacker_index].increase_kills ();
           players_list[attacked_index].increase_deaths ();
           players_list[attacker_index].increase_money (players_list[attacker_index].gun_loot (gun_index));
       }
   }
}

bool is_buy_possible (int player_index, int gun_index, string gun_name, vector<Gun> guns_list, vector<Player> players_list) {
    if (player_index == NOT_FIND) {
        cout << "user not available" << endl;
        return false;
    }

    if (players_list[player_index].get_status () == AFK) {
        cout << "user not available" << endl;
        return false;
    }

    if (gun_index == NOT_FIND) {
        cout << "weapon not available" << endl;
        return false;
    }

    if (players_list[player_index].find_existed_gun (gun_name) != NOT_FIND) {
        cout << "you already have this weapon" << endl;
        return false;
    }

    if (players_list[player_index].is_money_enought (guns_list[gun_index].get_cost ()) == false) {
        cout << "insufficient money" << endl;
        return false;
    }

    return true;
}

void buy (string username, string gun_name, vector<Gun> guns_list, vector<Player> &players_list) {
    int player_index;
    int gun_index;

    player_index = find_player (username, players_list);
    gun_index = find_gun (gun_name, guns_list);

    if (is_buy_possible (player_index, gun_index, gun_name, guns_list, players_list) == true) {
        players_list[player_index].buy_gun (guns_list[gun_index]);
        cout << "weapon bought successfully" << endl;
    }

}

void find_deaths_count (int &counter_terrorist_deaths, int &terrorist_deaths, vector<Player> players_list) {
    int i;

    for (i = 0; i < players_list.size (); i++) {
        if (players_list[i].is_alive () == false || players_list[i].get_status () == AFK) {
            if (players_list[i].get_group () == COUNTER_TERRORIST) {
                counter_terrorist_deaths = counter_terrorist_deaths + 1;
            }
            else {
                terrorist_deaths = terrorist_deaths + 1;
            }
        }
    }
}

int define_winner (int counter_terrorists_count, int terrorists_count, vector<Player> players_list) {
    int winner;
    int counter_terrorist_deaths = 0;
    int terrorist_deaths = 0;
    int i;

    find_deaths_count (counter_terrorist_deaths, terrorist_deaths, players_list);

    if (terrorist_deaths == terrorists_count) {
        winner = COUNTER_TERRORIST;
        cout << "counter-terrorist won" << endl;
    }

    else if (counter_terrorist_deaths == counter_terrorists_count) {
        winner = TERRORIST;
        cout << "terrorist won" << endl;
    }

    else {
        winner = COUNTER_TERRORIST;
        cout << "counter-terrorist won" << endl;
    }

    return winner;
}

void reset_game (int winner, int &game_status, vector<Player> &players_list) {
    int i;

    game_status = NOT_START;
    
    for (i = 0; i < players_list.size (); i++) {
        if (players_list[i].is_alive () == false) {
            players_list[i].reset_guns ();
        }

        if (players_list[i].get_group () == winner) {
            players_list[i].increase_money (WINNER_GIFT);
        }
        else {
            players_list[i].increase_money (LOSER_GIFT);
        }

        players_list[i].set_health_max ();
    }
}

void sort_players (vector<Player> &players_list) {
    int i;
    int j;
    string player1_username;
    string player2_username;

    for (i = 0; i < players_list.size (); i++) {
        for (j = i; j < players_list.size (); j++) {
            if (players_list[i].get_kills () < players_list[j].get_kills ()) {
                swap (players_list[i], players_list[j]);
            }

            else if (players_list[i].get_kills () == players_list[j].get_kills ()) {
                if (players_list[i].get_deaths () > players_list[j].get_deaths ()) {
                    swap (players_list[i], players_list[j]);
                }

                else if (players_list[i].get_deaths () == players_list[j].get_deaths ()) {
                    player1_username = players_list[i].get_username ();
                    player2_username = players_list[j].get_username ();

                    if (player1_username.compare (player2_username) > 0) {
                        swap (players_list[i], players_list[j]);
                    }
                }
            }
        }
    }
}

void print_group_scores (int group, vector<Player> players_list) {
    int i;

    if (group == COUNTER_TERRORIST) {
        cout << "counter-terrorist players:" << endl;
    }

    else if (group == TERRORIST) {
        cout << "terrorist players:" << endl;
    }

    for (i = 0; i < players_list.size (); i++) {
        if (players_list[i].get_group () == group) {
            players_list[i].print_scores ();
        }
    }
}

void show_scores (vector<Player> &players_list) {
    sort_players (players_list);

    print_group_scores (COUNTER_TERRORIST, players_list);

    print_group_scores (TERRORIST, players_list);
}

void play_round (int round_commands_count, int &game_status, int &counter_terrorists_count, int &terrorists_count, 
                 vector<Player> &players_list, vector<Gun> guns_list) {
    int winner;
    int i;
    string commands;
    vector<string> commands_word;

    for (i = 0; i < round_commands_count; i++) {
        getline (cin, commands);
        
        commands_word = separate_command (commands);

        if (commands_word[0] == "start") {
            start (game_status);
        }

        else if (commands_word[0] == "shoot") {
            if (game_status == STARTED) {
                shoot (commands_word[1], commands_word[2], commands_word[3], players_list);
            }
            else {
                cout << "The game hasn't started yet" << endl;
            }
        }

        else if (commands_word[0] == "buy") {
            if (game_status == NOT_START) {
                buy (commands_word[1], commands_word[2], guns_list, players_list);
            }
            else {
                cout << "you can't buy weapons anymore" << endl;
            }
        }

        else if (commands_word[0] == "get-money") {
            get_money (commands_word[1], players_list);
        }

        else if (commands_word[0] == "get-health") {
            get_health (commands_word[1], players_list);
        }

        else if (commands_word[0] == "go-afk") {
            go_afk (commands_word[1], players_list);
        }

        else if (commands_word[0] == "go-atk") {
            go_atk (commands_word[1], players_list);
        }

        else if (commands_word[0] == "score-board") {
            show_scores (players_list);
        }        
    }

    winner = define_winner (counter_terrorists_count, terrorists_count, players_list);

    reset_game (winner, game_status, players_list);
}


int main () {
    int rounds_count;
    int round_commands_count;
    int game_status = NOT_START;
    int counter_terrorists_count = 0;
    int terrorists_count = 0;
    string commands;
    vector<string> commands_word;
    vector<Player> players_list;
    vector<Gun> guns_list;

    guns_list = add_guns ();

    getline (cin, commands);
    rounds_count = stoi (commands);
    
    while (getline (cin, commands)) {
        
        commands_word = separate_command (commands);

        if (commands_word[0] == "add-user") {
            if (commands_word[2] == "counter-terrorist") {
                add_user (commands_word[1], COUNTER_TERRORIST, players_list);
                counter_terrorists_count = counter_terrorists_count + 1;
            }
            else {
                add_user (commands_word[1], TERRORIST, players_list);
                terrorists_count = terrorists_count + 1;
            }
        }

        else if (commands_word[0] == "round") {
            round_commands_count = stoi (commands_word[1]);
            play_round (round_commands_count, game_status, counter_terrorists_count, terrorists_count, players_list, guns_list);
        }

        else if (commands_word[0] == "score-board") {
            show_scores (players_list);
        }
    }

    return 0;
}