#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;


#define FIRST_HOUR 12
#define FIRST_MINUTE 0
#define LAST_HOUR 20
#define LAST_MINUTE 0
#define MAX_ARRAY_SIZE 100
#define NOT_SET 0
#define EMPTY 0
#define ONE_HOUR 60
#define SAME 0
#define STOP_COMMAND "#"


typedef struct Plan {
    int id;
    int duration;
    int start_hour;
    int start_minute;
    int end_hour;
    int end_minute;
} Plan;


void get_events (char *commands, vector<Plan> &events) {
    char *command_word;
    Plan plan_information;
    command_word = strtok (commands, ":");
    plan_information.start_hour = atof (command_word);
    command_word = strtok (NULL, "-");
    plan_information.start_minute = atof (command_word);
    command_word = strtok (NULL, ":");
    plan_information.end_hour = atof (command_word);
    command_word = strtok (NULL, " ");
    plan_information.end_minute = atof (command_word);
    plan_information.id = NOT_SET;
    plan_information.duration = NOT_SET;
    events.push_back (plan_information);
}

void get_tasks (char *commands, vector<Plan> &tasks) {
    char *command_word;
    Plan plan_information;
    command_word = strtok (commands, " ");
    plan_information.duration = atof (command_word);
    command_word = strtok (NULL, " ");
    plan_information.id = atof (command_word);
    tasks.push_back (plan_information);
}

int find_duration (int start_hour, int start_minute, int end_hour, int end_minute) {
    int duration;
    duration = (end_hour - start_hour) * ONE_HOUR + (end_minute - start_minute);
    return duration;
}

void set_free_times (vector<Plan> &free_times, vector<Plan> &events) {
    int duration;
    int start_hour;
    int start_minute;
    int end_hour;
    int end_minute;
    int free_time_id = 1;
    int i;
    Plan plan_information;
    for (i = 0; i <= events.size (); i++) {
        if (i == 0) {
            duration = find_duration (FIRST_HOUR, FIRST_MINUTE, events[i].start_hour, events[i].start_minute);
            start_hour = FIRST_HOUR;
            start_minute = FIRST_MINUTE;
            end_hour = events[i].start_hour;
            end_minute = events[i].start_minute;
        }
        else if (i == events.size ()) {
            duration = find_duration (events[i - 1].end_hour, events[i - 1].end_minute, LAST_HOUR, LAST_MINUTE);
            start_hour = events[i - 1].end_hour;
            start_minute = events[i - 1].end_minute;
            end_hour = LAST_HOUR;
            end_minute = LAST_MINUTE;
        }
        else {
            duration = find_duration (events[i - 1].end_hour, events[i - 1].end_minute, events[i].start_hour, events[i].start_minute);
            start_hour = events[i - 1].end_hour;
            start_minute = events[i - 1].end_minute;
            end_hour = events[i].start_hour;
            end_minute = events[i].start_minute;
        }
        if (duration > EMPTY) {
            plan_information.id = free_time_id;
            plan_information.start_hour = start_hour;
            plan_information.start_minute = start_minute;
            plan_information.end_hour = end_hour;
            plan_information.end_minute = end_minute;
            plan_information.duration = duration;
            free_times.push_back (plan_information);
            free_time_id = free_time_id + 1;
        }
    }
}

void set_time (Plan &task, int start_hour, int start_minute) {
    task.start_hour = start_hour;
    task.start_minute = start_minute;
    task.end_hour = start_hour + (task.duration / ONE_HOUR);
    task.end_minute = start_minute + (task.duration % ONE_HOUR);
    if (task.end_minute >= ONE_HOUR) {
        task.end_hour = task.end_hour + 1;
        task.end_minute = task.end_minute - ONE_HOUR;
    }
}

void set_tasks_times (vector<Plan> &tasks, vector<Plan> &free_times) {
    int i;
    int j;
    for (i = 0; i < tasks.size (); i++) {
        for (j = 0; j < free_times.size (); j++) {
            if (tasks[i].id == free_times[j].id) {
                set_time (tasks[i], free_times[j].start_hour, free_times[j].start_minute);
                free_times[j].start_hour = tasks[i].end_hour;
                free_times[j].start_minute = tasks[i].end_minute;
                free_times[j].duration = free_times[j].duration - tasks[i].duration;
                break;
            }
        }
    }
}

void print_result (vector<Plan> &tasks) {
    int i;
    for (i = 0; i < tasks.size (); i++) {
        printf ("%d %d:%02d-%d:%02d\n", i + 1, tasks[i].start_hour, tasks[i].start_minute, tasks[i].end_hour, tasks[i].end_minute);
    } 
}


//plan includes events and tasks and free times
int main () {
    char commands[MAX_ARRAY_SIZE];
    char *command_word;
    vector<Plan> events;
    vector<Plan> tasks;
    vector<Plan> free_times;
    cin.getline (commands, MAX_ARRAY_SIZE);

    while (strcmp (commands, STOP_COMMAND) != SAME) {
        get_events (commands, events);
        cin.getline (commands, MAX_ARRAY_SIZE);
    }

    while (cin.getline (commands, MAX_ARRAY_SIZE)) {
        get_tasks (commands, tasks);
    }

    set_free_times (free_times, events);

    set_tasks_times (tasks, free_times);

    print_result (tasks);

    return 0;
}