//
// SE 2XC3 Lab 7.2: Electible - First-Year Elective Finder
// Module D: User Interface & Integration
// Developer: Yasmine Abdelmalek
///

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/ui.h"
#include "../include/filter.h"
#include "../include/sort.h"
#include "../include/data.h"

/* ANSI color codes for terminal output (optional, can be disabled for Windows compatibility) */
#define COLOR_RESET   "\033[0m"
#define COLOR_BOLD    "\033[1m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"

/* Disable colors on Windows by default (uncomment if colors don't work) */
/* #define COLOR_RESET ""
#define COLOR_BOLD ""
#define COLOR_CYAN ""
#define COLOR_GREEN ""
#define COLOR_YELLOW ""
#define COLOR_BLUE "" */

//
// Clear input buffer
///
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//
// Print a separator line
///
void print_separator(void) {
    printf("================================================================================\n");
}

//
// Pause and wait for user
///
void pause_for_user(void) {
    printf("\nPress Enter to continue...");
    getchar();
}

//
// Get integer input within a range
///
int get_int_input(const char* prompt, int min, int max) {
    int value;
    int valid = 0;

    while (!valid) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            clear_input_buffer();
            if (value >= min && value <= max) {
                valid = 1;
            } else {
                printf("Invalid input. Please enter a value between %d and %d.\n", min, max);
            }
        } else {
            clear_input_buffer();
            printf("Invalid input. Please enter a number.\n");
        }
    }

    return value;
}

//
// Get float input within a range
///
float get_float_input(const char* prompt, float min, float max) {
    float value;
    int valid = 0;

    while (!valid) {
        printf("%s", prompt);
        if (scanf("%f", &value) == 1) {
            clear_input_buffer();
            if (value >= min && value <= max) {
                valid = 1;
            } else {
                printf("Invalid input. Please enter a value between %.1f and %.1f.\n", min, max);
            }
        } else {
            clear_input_buffer();
            printf("Invalid input. Please enter a number.\n");
        }
    }

    return value;
}

//
// Get string input
///
void get_string_input(const char* prompt, char* buffer, int max_length) {
    printf("%s", prompt);
    if (fgets(buffer, max_length, stdin) != NULL) {
        /* Remove newline character */
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

//
// Display main menu
///
void display_menu(void) {
    print_separator();
    printf("%s%s=== ELECTIBLE: McMaster First-Year Elective Finder ===%s\n", COLOR_BOLD, COLOR_CYAN, COLOR_RESET);
    print_separator();
    printf("\n");
    printf("%s1.%s Browse All Courses\n", COLOR_GREEN, COLOR_RESET);
    printf("%s2.%s Filter Courses\n", COLOR_GREEN, COLOR_RESET);
    printf("%s3.%s Sort Courses\n", COLOR_GREEN, COLOR_RESET);
    printf("%s4.%s Add New Course (Crowdsource)\n", COLOR_GREEN, COLOR_RESET);
    printf("%s5.%s View Recommendations\n", COLOR_GREEN, COLOR_RESET);
    printf("%s6.%s Help\n", COLOR_GREEN, COLOR_RESET);
    printf("%s7.%s Exit\n", COLOR_GREEN, COLOR_RESET);
    printf("\n");
}

//
// Display a course in table row format
///
static void display_course_row(Course course, int index) {
    printf("%-4d %-10s %-40s %4d/5  %4d/5  %s     %s         %.1f/5\n",
           index + 1,
           course.course_code,
           course.title,
           course.difficulty,
           course.workload,
           course.has_exam ? "Yes" : "No ",
           course.has_midterm ? "Yes" : "No ",
           course.rating);
}

//
// Display list of courses in table format
///
void display_courses(Course* courses, int count) {
    if (courses == NULL || count <= 0) {
        printf("\n%sNo courses to display.%s\n", COLOR_YELLOW, COLOR_RESET);
        return;
    }

    printf("\n%s%sFound %d course(s):%s\n\n", COLOR_BOLD, COLOR_BLUE, count, COLOR_RESET);

    /* Table header */
    printf("%-4s %-10s %-40s %-6s %-6s %-6s %-9s %-6s\n",
           "#", "Code", "Title", "Diff", "Work", "Exam", "Midterm", "Rating");
    print_separator();

    /* Display each course */
    for (int i = 0; i < count; i++) {
        display_course_row(courses[i], i);
    }

    printf("\n");
}

//
// Display detailed information for a single course
///
void display_course_detail(Course course) {
    print_separator();
    printf("%s%s%s%s\n", COLOR_BOLD, COLOR_CYAN, course.title, COLOR_RESET);
    printf("Course Code:     %s\n", course.course_code);
    printf("Subject Area:    %s\n", course.subject_area);
    printf("Difficulty:      %d/5\n", course.difficulty);
    printf("Workload:        %d/5\n", course.workload);
    printf("Has Exam:        %s\n", course.has_exam ? "Yes" : "No");
    printf("Has Midterm:     %s\n", course.has_midterm ? "Yes" : "No");
    printf("Rating:          %.1f/5\n", course.rating);
    printf("Year Offered:    %d\n", course.year_offered);
    printf("\nDescription:\n%s\n", course.description);
    print_separator();
}

//
// Get filter preferences from user
///
FilterCriteria get_filter_preferences(void) {
    FilterCriteria criteria = create_default_filter_criteria();

    printf("\n%s%s=== Filter Courses ===%s\n", COLOR_BOLD, COLOR_CYAN, COLOR_RESET);
    printf("Leave filters blank or enter -1 to skip.\n\n");

    /* Subject area filter */
    printf("Filter by subject area? (e.g., Computer Science, Math, Business)\n");
    get_string_input("Subject area (or press Enter to skip): ", criteria.subject_area, sizeof(criteria.subject_area));

    /* Difficulty filter */
    printf("\nFilter by difficulty? (1-5 scale)\n");
    char response[10];
    get_string_input("Minimum difficulty (or press Enter to skip): ", response, sizeof(response));
    if (strlen(response) > 0) {
        criteria.min_difficulty = atoi(response);
        if (criteria.min_difficulty < 1 || criteria.min_difficulty > 5) {
            criteria.min_difficulty = -1;
        }
    }

    get_string_input("Maximum difficulty (or press Enter to skip): ", response, sizeof(response));
    if (strlen(response) > 0) {
        criteria.max_difficulty = atoi(response);
        if (criteria.max_difficulty < 1 || criteria.max_difficulty > 5) {
            criteria.max_difficulty = -1;
        }
    }

    /* Workload filter */
    printf("\nFilter by workload? (1-5 scale)\n");
    get_string_input("Minimum workload (or press Enter to skip): ", response, sizeof(response));
    if (strlen(response) > 0) {
        criteria.min_workload = atoi(response);
        if (criteria.min_workload < 1 || criteria.min_workload > 5) {
            criteria.min_workload = -1;
        }
    }

    get_string_input("Maximum workload (or press Enter to skip): ", response, sizeof(response));
    if (strlen(response) > 0) {
        criteria.max_workload = atoi(response);
        if (criteria.max_workload < 1 || criteria.max_workload > 5) {
            criteria.max_workload = -1;
        }
    }

    /* Exam filter */
    printf("\nFilter by exam presence?\n");
    printf("1. Courses with exams\n");
    printf("2. Courses without exams\n");
    printf("3. No preference\n");
    int exam_choice = get_int_input("Choice: ", 1, 3);
    if (exam_choice == 1) {
        criteria.has_exam = 1;
    } else if (exam_choice == 2) {
        criteria.has_exam = 0;
    }

    /* Midterm filter */
    printf("\nFilter by midterm presence?\n");
    printf("1. Courses with midterms\n");
    printf("2. Courses without midterms\n");
    printf("3. No preference\n");
    int midterm_choice = get_int_input("Choice: ", 1, 3);
    if (midterm_choice == 1) {
        criteria.has_midterm = 1;
    } else if (midterm_choice == 2) {
        criteria.has_midterm = 0;
    }

    /* Rating filter */
    printf("\nFilter by minimum rating? (0.0-5.0)\n");
    get_string_input("Minimum rating (or press Enter to skip): ", response, sizeof(response));
    if (strlen(response) > 0) {
        criteria.min_rating = (float)atof(response);
        if (criteria.min_rating < 0.0f || criteria.min_rating > 5.0f) {
            criteria.min_rating = -1.0f;
        }
    }

    return criteria;
}

//
// Get sort preferences from user
///
void get_sort_preferences(SortCriteria** criteria, int* num_criteria) {
    printf("\n%s%s=== Sort Courses ===%s\n", COLOR_BOLD, COLOR_CYAN, COLOR_RESET);
    printf("Select sort field:\n");
    printf("1. Difficulty\n");
    printf("2. Workload\n");
    printf("3. Rating\n");
    printf("4. Course Code\n");
    printf("5. Title\n");

    int field_choice = get_int_input("Sort by: ", 1, 5);

    printf("\nSort order:\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    int order_choice = get_int_input("Order: ", 1, 2);

    *criteria = (SortCriteria*)malloc(sizeof(SortCriteria));
    if (*criteria == NULL) {
        *num_criteria = 0;
        return;
    }

    (*criteria)[0].field = (SortField)(field_choice - 1);
    (*criteria)[0].order = (order_choice == 1) ? ASCENDING : DESCENDING;
    *num_criteria = 1;
}

//
// Get new course input from user
///
Course get_new_course_input(void) {
    Course course;

    printf("\n%s%s=== Add New Course ===%s\n", COLOR_BOLD, COLOR_CYAN, COLOR_RESET);

    get_string_input("Course title: ", course.title, sizeof(course.title));
    get_string_input("Course code (e.g., COMPSCI 1MD3): ", course.course_code, sizeof(course.course_code));
    get_string_input("Subject area: ", course.subject_area, sizeof(course.subject_area));

    course.difficulty = get_int_input("Difficulty (1-5): ", 1, 5);
    course.workload = get_int_input("Workload (1-5): ", 1, 5);

    printf("Has exam? (1=Yes, 0=No): ");
    course.has_exam = get_int_input("", 0, 1);

    printf("Has midterm? (1=Yes, 0=No): ");
    course.has_midterm = get_int_input("", 0, 1);

    course.rating = get_float_input("Rating (0.0-5.0): ", 0.0f, 5.0f);

    get_string_input("Description: ", course.description, sizeof(course.description));

    course.year_offered = get_int_input("Year offered (e.g., 2025): ", 2020, 2030);

    return course;
}

//
// Display help information
///
void display_help(void) {
    print_separator();
    printf("%s%s=== HELP ===%s\n\n", COLOR_BOLD, COLOR_CYAN, COLOR_RESET);

    printf("%sWelcome to Electible!%s\n\n", COLOR_BOLD, COLOR_RESET);

    printf("This application helps McMaster first-year engineering students find and\n");
    printf("explore elective courses based on their preferences.\n\n");

    printf("%sFeatures:%s\n", COLOR_BOLD, COLOR_RESET);
    printf("1. %sBrowse All Courses%s - View the complete list of available electives\n", COLOR_GREEN, COLOR_RESET);
    printf("2. %sFilter Courses%s - Narrow down courses by subject, difficulty, workload, etc.\n", COLOR_GREEN, COLOR_RESET);
    printf("3. %sSort Courses%s - Organize courses by various criteria\n", COLOR_GREEN, COLOR_RESET);
    printf("4. %sAdd New Course%s - Contribute new course information to the database\n", COLOR_GREEN, COLOR_RESET);
    printf("5. %sRecommendations%s - Get course suggestions based on ratings and difficulty\n\n", COLOR_GREEN, COLOR_RESET);

    printf("%sRating Scale:%s\n", COLOR_BOLD, COLOR_RESET);
    printf("- Difficulty: 1 (easiest) to 5 (most challenging)\n");
    printf("- Workload: 1 (lightest) to 5 (heaviest)\n");
    printf("- Rating: 0.0 (lowest) to 5.0 (highest)\n\n");

    print_separator();
}

//
// Display recommended courses
///
void display_recommendations(Course* courses, int count) {
    printf("\n%s%s=== Recommended Courses ===%s\n", COLOR_BOLD, COLOR_CYAN, COLOR_RESET);
    printf("Based on high ratings and moderate difficulty.\n\n");

    /* Filter for highly rated courses (rating >= 4.0) with moderate difficulty (1-3) */
    FilterCriteria criteria = create_default_filter_criteria();
    criteria.min_rating = 4.0f;
    criteria.min_difficulty = 1;
    criteria.max_difficulty = 3;

    int rec_count;
    Course* recommendations = apply_multiple_filters(courses, count, criteria, &rec_count);

    if (recommendations != NULL && rec_count > 0) {
        /* Sort by rating (descending) */
        sort_by_rating(recommendations, rec_count, 0);

        /* Display top 10 or all if fewer */
        int display_count = (rec_count < 10) ? rec_count : 10;
        display_courses(recommendations, display_count);

        free(recommendations);
    } else {
        printf("No recommendations found.\n");
    }
}

//
// Main user interaction handler
///
void handle_user_interaction(Course** courses, int* count, const char* filename) {
    int running = 1;
    Course* working_set = *courses;  /* Current working set (may be filtered) */
    int working_count = *count;
    int is_filtered = 0;  /* Track if working set is filtered */

    while (running) {
        display_menu();

        int choice = get_int_input("Enter choice (1-7): ", 1, 7);

        switch (choice) {
            case MENU_BROWSE: {
                /* Reset to full dataset */
                if (is_filtered && working_set != *courses) {
                    free(working_set);
                }
                working_set = *courses;
                working_count = *count;
                is_filtered = 0;

                display_courses(working_set, working_count);
                pause_for_user();
                break;
            }

            case MENU_FILTER: {
                FilterCriteria criteria = get_filter_preferences();

                /* Free previous filtered set if exists */
                if (is_filtered && working_set != *courses) {
                    free(working_set);
                }

                int filtered_count;
                Course* filtered = apply_multiple_filters(*courses, *count, criteria, &filtered_count);

                if (filtered != NULL && filtered_count > 0) {
                    working_set = filtered;
                    working_count = filtered_count;
                    is_filtered = 1;

                    printf("\n%sFiltering complete!%s\n", COLOR_GREEN, COLOR_RESET);
                    display_courses(working_set, working_count);
                } else {
                    printf("\n%sNo courses match your filters.%s\n", COLOR_YELLOW, COLOR_RESET);
                    working_set = *courses;
                    working_count = *count;
                    is_filtered = 0;
                }

                pause_for_user();
                break;
            }

            case MENU_SORT: {
                SortCriteria* sort_criteria;
                int num_criteria;
                get_sort_preferences(&sort_criteria, &num_criteria);

                if (sort_criteria != NULL && num_criteria > 0) {
                    sort_multi_criteria(working_set, working_count, sort_criteria, num_criteria);
                    printf("\n%sSorting complete!%s\n", COLOR_GREEN, COLOR_RESET);
                    display_courses(working_set, working_count);
                    free(sort_criteria);
                } else {
                    printf("\n%sSort operation failed.%s\n", COLOR_YELLOW, COLOR_RESET);
                }

                pause_for_user();
                break;
            }

            case MENU_ADD: {
                Course new_course = get_new_course_input();

                int result = add_course(courses, count, new_course);

                if (result == DATA_SUCCESS) {
                    printf("\n%sCourse added successfully!%s\n", COLOR_GREEN, COLOR_RESET);

                    /* Save to file */
                    if (save_courses(*courses, *count, filename) == DATA_SUCCESS) {
                        printf("%sChanges saved to %s.%s\n", COLOR_GREEN, filename, COLOR_RESET);
                    } else {
                        printf("%sWarning: Could not save to file.%s\n", COLOR_YELLOW, COLOR_RESET);
                    }

                    /* Reset working set if we're viewing all courses */
                    if (!is_filtered) {
                        working_set = *courses;
                        working_count = *count;
                    }
                } else {
                    printf("\n%sError adding course: %s%s\n", COLOR_YELLOW,
                           get_data_error_message(result), COLOR_RESET);
                }

                pause_for_user();
                break;
            }

            case MENU_RECOMMENDATIONS: {
                display_recommendations(*courses, *count);
                pause_for_user();
                break;
            }

            case MENU_HELP: {
                display_help();
                pause_for_user();
                break;
            }

            case MENU_EXIT: {
                printf("\n%sThank you for using Electible! Good luck with your electives!%s\n",
                       COLOR_GREEN, COLOR_RESET);
                running = 0;

                /* Clean up filtered set if exists */
                if (is_filtered && working_set != *courses) {
                    free(working_set);
                }
                break;
            }
        }
    }
}
