// SE 2XC3 Lab 7.2: Electible
// Module D: User Interface
// Yasmine Abdelmalek

#ifndef UI_H
#define UI_H

#include "filter.h"
#include "sort.h"

// Menu options
typedef enum {
    MENU_BROWSE = 1,
    MENU_FILTER = 2,
    MENU_SORT = 3,
    MENU_ADD = 4,
    MENU_RECOMMENDATIONS = 5,
    MENU_HELP = 6,
    MENU_EXIT = 7
} MenuOption;

// Show the main menu
void display_menu(void);

// Show a list of courses in a nice table
void display_courses(Course* courses, int count);

// Show all details for one course
void display_course_detail(Course course);

// Ask user what they want to filter by
FilterCriteria get_filter_preferences(void);

// Ask user how they want to sort
void get_sort_preferences(SortCriteria** criteria, int* num_criteria);

// Get info for a new course from user
Course get_new_course_input(void);

// Main loop that handles user menu choices
void handle_user_interaction(Course** courses, int* count, const char* filename);

// Show help info
void display_help(void);

// Show recommended courses
void display_recommendations(Course* courses, int count);

// Clear leftover input
void clear_input_buffer(void);

// Get an integer from user (with validation)
int get_int_input(const char* prompt, int min, int max);

// Get a float from user (with validation)
float get_float_input(const char* prompt, float min, float max);

// Get a string from user
void get_string_input(const char* prompt, char* buffer, int max_length);

// Print a line separator
void print_separator(void);

// Wait for user to press Enter
void pause_for_user(void);

#endif
