// SE 2XC3 Lab 7.2: Electible
// Main Program
// Team: Amanda Wu, Anshika Patel, Khushi Ved, Yasmine Abdelmalek
// McMaster University, 2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/data.h"
#include "../include/ui.h"

#define DEFAULT_DATA_FILE "data/courses.csv"

// Show usage info when user types --help
void display_usage(const char* program_name) {
    printf("Electible - McMaster First-Year Elective Finder\n");
    printf("SE 2XC3 Lab 7.2 Team Assignment\n\n");
    printf("Usage: %s [data_file]\n\n", program_name);
    printf("Arguments:\n");
    printf("  data_file    Path to CSV file (default: %s)\n\n", DEFAULT_DATA_FILE);
    printf("Options:\n");
    printf("  --help       Show this help message\n\n");
    printf("Description:\n");
    printf("  This program helps first-year McMaster engineering students\n");
    printf("  filter and sort elective courses.\n\n");
    printf("Features:\n");
    printf("  - Browse all courses\n");
    printf("  - Filter by subject, difficulty, workload, etc.\n");
    printf("  - Sort courses\n");
    printf("  - Add new courses\n");
    printf("  - Get recommendations\n\n");
    printf("Examples:\n");
    printf("  %s\n", program_name);
    printf("  %s data/my_courses.csv\n", program_name);
    printf("  %s --help\n\n", program_name);
}

int main(int argc, char* argv[]) {
    const char* data_file = DEFAULT_DATA_FILE;

    // Check if user wants help
    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            display_usage(argv[0]);
            return 0;
        }
        data_file = argv[1];
    }

    // Load courses from file
    printf("Loading courses from %s...\n", data_file);
    int count = 0;
    Course* courses = load_courses(data_file, &count);

    if (courses == NULL || count == 0) {
        fprintf(stderr, "Error: Failed to load courses from %s\n", data_file);
        fprintf(stderr, "Make sure the file exists and is formatted correctly.\n");
        fprintf(stderr, "Run '%s --help' for more info.\n", argv[0]);
        return 1;
    }

    printf("Successfully loaded %d courses.\n\n", count);

    // Start main menu loop
    handle_user_interaction(&courses, &count, data_file);

    // Clean up memory
    free_courses(courses);

    return 0;
}
