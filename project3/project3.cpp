#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;


#define MATCH 1
#define NOT_MATCH 0
#define FOUND 1
#define NOT_FIND 0
#define ONE_HOUR 60


typedef struct Time {
    int start_hour;
    int start_minute;
    int start_time_minute;
    int end_hour;
    int end_minute;
    int end_time_minute;
} Time;

typedef struct Language {
    string name;
    int translators_count;
    string translator;
} Language;

typedef struct Translator {
    string name;
    vector<Time> free_times;
    vector<string> languages;
} Translator;

typedef struct Event {
    string name;
    Time event_time;
    vector<Language> languages;
} Event;


int find_time_minute (int hour, int minute) {
    int result;

    result = (hour * ONE_HOUR) + minute;
    
    return result;
}

void read_file (string file_name, vector<Translator> &translators_list, vector<Event> &events_list) {
    fstream input_file (file_name);
    int translators_count;
    int events_count;
    int num;
    Translator translator_information;
    Event event_information;
    Time time_information;
    Language language_information;
    string line;
    string word;

    getline (input_file, line);
    translators_count = stoi (line);

    while (translators_count > 0) {
        getline (input_file, line);
        num = line.find (" ");
        word = line.substr (0, num);
        translator_information.name = word;
        line.erase (0, num + 1);

        num = line.find (":");
        word = line.substr (0, num);
        time_information.start_hour = stoi (word);
        line.erase (0, num + 1);

        num = line.find (" ");
        word = line.substr (0, num);
        time_information.start_minute = stoi (word);
        time_information.start_time_minute = find_time_minute (time_information.start_hour, time_information.start_minute);
        line.erase (0, num + 1);

        num = line.find (":");
        word = line.substr (0, num);
        time_information.end_hour = stoi (word);
        line.erase (0, num + 1);

        num = line.find (" ");
        word = line.substr (0, num);
        time_information.end_minute = stoi (word);
        time_information.end_time_minute = find_time_minute (time_information.end_hour, time_information.end_minute);
        translator_information.free_times.push_back (time_information);
        line.erase (0, num + 1);

        istringstream str (line);
        while (getline (str, word, ' ')) {
            translator_information.languages.push_back (word);
        }

        translators_list.push_back (translator_information);
        translator_information.languages.clear ();
        translator_information.free_times.clear ();
        translators_count = translators_count - 1;
    }

    getline (input_file, line);
    events_count = stoi (line);

    while (events_count > 0) {
        getline (input_file, line);
        num = line.find (" ");
        word = line.substr (0, num);
        event_information.name = word;
        line.erase (0, num + 1);

        num = line.find (":");
        word = line.substr (0, num);
        event_information.event_time.start_hour = stoi (word);
        line.erase (0, num + 1);

        num = line.find (" ");
        word = line.substr (0, num);
        event_information.event_time.start_minute = stoi (word);
        event_information.event_time.start_time_minute = find_time_minute (event_information.event_time.start_hour,
                                                                           event_information.event_time.start_minute);
        line.erase (0, num + 1);

        num = line.find (":");
        word = line.substr (0, num);
        event_information.event_time.end_hour = stoi (word);
        line.erase (0, num + 1);

        num = line.find (" ");
        word = line.substr (0, num);
        event_information.event_time.end_minute = stoi (word);
        event_information.event_time.end_time_minute = find_time_minute (event_information.event_time.end_hour,
                                                                         event_information.event_time.end_minute);
        line.erase (0, num + 1);

        istringstream str (line);
        while (getline (str, word, ' ')) {
            language_information.name = word;
            language_information.translators_count = 0;
            language_information.translator = "";
            event_information.languages.push_back (language_information);
        }

        events_list.push_back (event_information);
        event_information.languages.clear ();
        events_count = events_count - 1;
    }

    input_file.close ();
}

int find_language (string language, vector<string> languages_list) {
    int result = NOT_FIND;
    int i;

    for (i = 0; i < languages_list.size (); i++) {
        if (languages_list[i] == language) {
            result = FOUND;
            break;
        }
    }

    return result;
}

void find_translators_count (vector<Translator> translators_list, vector<Event> &events_list) {
    int i;
    int j;
    int k;

    for (i = 0; i < events_list.size (); i++) {
        for (j = 0; j < events_list[i].languages.size (); j++) {
            for (k = 0; k < translators_list.size (); k++) {
                if (find_language (events_list[i].languages[j].name, translators_list[k].languages) == FOUND) {
                    events_list[i].languages[j].translators_count = events_list[i].languages[j].translators_count + 1;
                }
            }
        }
    }
}

int check_translator_language (string language, Translator translator) {
    int result = NOT_FIND;
    int i;

    for (i = 0; i < translator.languages.size (); i++) {
        if (translator.languages[i] == language) {
            result = FOUND;
            break;
        }
    }

    return result;
}

int check_translator_time (Event event, Translator translator) {
    int result = NOT_MATCH;
    int i;

    for (i = 0; i < translator.free_times.size (); i++) {
        if (event.event_time.start_time_minute >= translator.free_times[i].start_time_minute &&
            event.event_time.end_time_minute <= translator.free_times[i].end_time_minute) {
            result = MATCH;
            break;
        }
    }

    return result;
}

int find_min_language_count (Event event, Language language, vector<Translator> translators_list) {
    int min_count;
    int first_match = NOT_FIND;
    int i;

    for (i = 0; i < translators_list.size (); i++) {
        if (check_translator_language (language.name, translators_list[i]) == FOUND && 
            check_translator_time (event, translators_list[i]) == MATCH) {
            if (first_match == NOT_FIND) {
                min_count = translators_list[i].languages.size ();
                first_match = FOUND;
    }
            else {
                if (min_count > translators_list[i].languages.size ()) {
                    min_count = translators_list[i].languages.size ();
                }
            }
        }
    }

    return min_count;
}

void set_translator_time (Translator &translator, Event event) {
    int i;
    Time free_time;

    for (i = 0; i < translator.free_times.size (); i++) {
        if (event.event_time.start_time_minute >= translator.free_times[i].start_time_minute &&
            event.event_time.end_time_minute <= translator.free_times[i].end_time_minute) {
            break;
        }
    }

    if (translator.free_times[i].start_time_minute < event.event_time.start_time_minute) {
        free_time.start_hour = translator.free_times[i].start_hour;
        free_time.start_minute = translator.free_times[i].start_minute;
        free_time.start_time_minute = translator.free_times[i].start_time_minute;
        free_time.end_hour = event.event_time.start_hour;
        free_time.end_minute = event.event_time.start_minute;
        free_time.end_time_minute = event.event_time.start_time_minute;
        translator.free_times.push_back (free_time);
    }
    if (translator.free_times[i].end_time_minute > event.event_time.end_time_minute) {
        free_time.start_hour = event.event_time.end_hour;
        free_time.start_minute = event.event_time.end_minute;
        free_time.start_time_minute = event.event_time.end_time_minute;
        free_time.end_hour = translator.free_times[i].end_hour;
        free_time.end_minute = translator.free_times[i].end_minute;
        free_time.end_time_minute = translator.free_times[i].end_time_minute;
        translator.free_times.push_back (free_time);
    }

    translator.free_times.erase (translator.free_times.begin () + i);
}

void sort_translators (vector<Translator> &translators_list) {
    int i;

    for (i = 0; i < translators_list.size (); i++) {
        if (translators_list[0].name.compare (translators_list[i].name) > 0) {
            swap (translators_list[0], translators_list[i]);
        }
    }
}

int find_translator (string name, vector<Translator> translators_list) {
    int i;

    for (i = 0; i < translators_list.size (); i++) {
        if (translators_list[i].name == name) {
            break;
        }
    }

    return i;
}

void set_language_translator (int language_pos, Event &event, vector<Translator> &translators_list) {
    int min_count;
    int translator_pos;
    int i;
    vector<Translator> found_translators;

    min_count = find_min_language_count (event, event.languages[language_pos], translators_list);

    for (i = 0; i < translators_list.size (); i++) {
        if (check_translator_language (event.languages[language_pos].name, translators_list[i]) == FOUND && 
            translators_list[i].languages.size () == min_count && check_translator_time (event, translators_list[i]) == MATCH) {
            found_translators.push_back (translators_list[i]);
        }
    }

    if (found_translators.size () > 0) {
        sort_translators (found_translators);
        set_translator_time (found_translators[0], event);
        translator_pos = find_translator (found_translators[0].name, translators_list);
        translators_list[translator_pos] = found_translators[0];
        event.languages[language_pos].translator = found_translators[0].name;

    }
    else {
        event.languages[language_pos].translator = "Not Found";
    }
}

void set_event_translator (Event &event, vector<Translator> &translators_list) {
    int i;
    int j;
    vector<int> translators_count_list;

    for (i = 0; i < event.languages.size (); i++) {
        translators_count_list.push_back (event.languages[i].translators_count);
    }

    sort (translators_count_list.begin (), translators_count_list.end ());

    for (i = 0; i < translators_count_list.size (); i++) {
        for (j = 0; j < event.languages.size (); j++) {
            if (translators_count_list[i] == event.languages[j].translators_count && event.languages[j].translator == "") {
                set_language_translator (j, event, translators_list);
            }
        }
    }
}

void set_translators (vector<Translator> &translators_list, vector<Event> &events_list) {
    int i;

    for (i = 0; i < events_list.size (); i++) {
        set_event_translator (events_list[i], translators_list);
    }
}

void print_result (vector<Event> events_list) {
    int i;
    int j;

    for (i = 0; i < events_list.size (); i++) {
        cout << events_list[i].name << endl;
        for (j = 0; j < events_list[i].languages.size (); j++) {
            cout << events_list[i].languages[j].name << ": " << events_list[i].languages[j].translator << endl;
        }
    }
}


int main (int argc, char *argv[]) {
    vector<Translator> translators_list;
    vector<Event> events_list;
    string file_name = argv[1];

    read_file (file_name, translators_list, events_list);

    find_translators_count (translators_list, events_list);

    set_translators (translators_list, events_list);

    print_result (events_list);

    return 0;
}