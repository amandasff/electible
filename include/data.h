// SE 2XC3 Lab 7.2: Electible
// Module C: Data Management
// Khushi Ved

#ifndef DATA_H
#define DATA_H

#include "filter.h"

// Error codes
#define DATA_SUCCESS 0
#define DATA_ERROR_FILE_NOT_FOUND -1
#define DATA_ERROR_INVALID_FORMAT -2
#define DATA_ERROR_MEMORY -3
#define DATA_ERROR_VALIDATION -4
#define DATA_ERROR_WRITE -5

// Load courses from CSV file
// Returns array of courses (you need to free it later)
Course* load_courses(const char* filename, int* count);

// Save courses back to CSV file
int save_courses(Course* courses, int count, const char* filename);

// Add a new course to the array (resizes the array)
int add_course(Course** courses, int* count, Course new_course);

// Check if a course has valid data
int validate_course(Course course);

// Free the memory used by courses
void free_courses(Course* courses);

// Get error message from error code
const char* get_data_error_message(int error_code);

// Handle special characters in CSV fields (like commas)
void escape_csv_field(char* dest, const char* src, int max_len);

// Parse a line from CSV file into separate fields
int parse_csv_line(char* line, char** fields, int max_fields);

#endif
