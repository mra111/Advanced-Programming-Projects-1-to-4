#include <iostream>
#include <vector>
using namespace std;


void print_result (vector<int> nums_list, int number_location) {
    cout << nums_list[number_location - 1] << endl;
}

int replace_num (vector<int> &nums_list, int level, int number_location) {
    int i;

    if (level <= 1) {
        print_result (nums_list, number_location);
        return 0;
    }

    for (i = 0; i < nums_list.size (); i += 2) {
        if (nums_list[i] == 0) {
            nums_list[i] = 0;
            nums_list.insert (nums_list.begin () + i + 1, 1);
        }
        else if (nums_list[i] == 1) {
            nums_list[i] = 1;
            nums_list.insert (nums_list.begin () + i + 1, 0); 
        }
    }

    replace_num (nums_list, level - 1, number_location);

    return 0;
}


int main () {
    int level;
    int number_location;
    vector<int> nums_list;

    cin >> level >> number_location;

    nums_list.push_back (0);

    replace_num (nums_list, level, number_location);

    return 0;
}