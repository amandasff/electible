//
// SE 2XC3 Lab 7.2: Electible - First-Year Elective Finder
// Module C: Data Management & Backend
// Developer: Khushi Ved
///

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/data.h"

/* Helper function prototypes */
static void trim_whitespace(char* str);
static void remove_quotes(char* str);

//
// Trim leading and trailing whitespace from a string
///
static void trim_whitespace(char* str) {
    if (str == NULL) return;

    /* Trim leading whitespace */
    char* start = str;
    while (isspace((unsigned char)*start)) start++;

    /* If string is all whitespace */
    if (*start == '\0') {
        *str = '\0';
        return;
    }

    /* Trim trailing whitespace */
    char* end = str + strlen(str) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;

    /* Move trimmed string to beginning and null-terminate */
    size_t len = (end - start) + 1;
    memmove(str, start, len);
    str[len] = '\0';
}

//
// Remove surrounding quotes from a string
///
static void remove_quotes(char* str) {
    if (str == NULL) return;

    size_t len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len-1] == '"') {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}

//
// Parse a CSV line into fields, handling quoted strings with commas
///
int parse_csv_line(char* line, char** fields, int max_fields) {
    int field_count = 0;
    int in_quotes = 0;
    char* field_start = line;
    char* p = line;

    while (*p && field_count < max_fields) {
        if (*p == '"') {
            in_quotes = !in_quotes;
        } else if (*p == ',' && !in_quotes) {
            *p = '\0';
            fields[field_count] = field_start;
            trim_whitespace(fields[field_count]);
            remove_quotes(fields[field_count]);
            field_count++;
            field_start = p + 1;
        }
        p++;
    }

    /* Add the last field */
    if (field_count < max_fields) {
        fields[field_count] = field_start;
        trim_whitespace(fields[field_count]);
        remove_quotes(fields[field_count]);
        field_count++;
    }

    return field_count;
}

//
// Escape special characters for CSV output
///
void escape_csv_field(char* dest, const char* src, int max_len) {
    int needs_quotes = 0;

    /* Check if field needs quotes (contains comma, quote, or newline) */
    for (const char* p = src; *p; p++) {
        if (*p == ',' || *p == '"' || *p == '\n') {
            needs_quotes = 1;
            break;
        }
    }

    if (needs_quotes) {
        int dest_idx = 0;
        dest[dest_idx++] = '"';

        for (const char* p = src; *p && dest_idx < max_len - 3; p++) {
            if (*p == '"') {
                dest[dest_idx++] = '"';  /* Escape quote with double quote */
            }
            dest[dest_idx++] = *p;
        }

        dest[dest_idx++] = '"';
        dest[dest_idx] = '\0';
    } else {
        strncpy(dest, src, max_len - 1);
        dest[max_len - 1] = '\0';
    }
}

//
// Validate a course structure
///
int validate_course(Course course) {
    /* Check course code is not empty */
    if (strlen(course.course_code) == 0) {
        return DATA_ERROR_VALIDATION;
    }

    /* Check title is not empty */
    if (strlen(course.title) == 0) {
        return DATA_ERROR_VALIDATION;
    }

    /* Check subject area is not empty */
    if (strlen(course.subject_area) == 0) {
        return DATA_ERROR_VALIDATION;
    }

    /* Validate difficulty range (1-5) */
    if (course.difficulty < 1 || course.difficulty > 5) {
        return DATA_ERROR_VALIDATION;
    }

    /* Validate workload range (1-5) */
    if (course.workload < 1 || course.workload > 5) {
        return DATA_ERROR_VALIDATION;
    }

    /* Validate boolean fields */
    if (course.has_exam != 0 && course.has_exam != 1) {
        return DATA_ERROR_VALIDATION;
    }

    if (course.has_midterm != 0 && course.has_midterm != 1) {
        return DATA_ERROR_VALIDATION;
    }

    /* Validate rating range (0.0-5.0) */
    if (course.rating < 0.0 || course.rating > 5.0) {
        return DATA_ERROR_VALIDATION;
    }

    /* Validate year */
    if (course.year_offered < 2020 || course.year_offered > 2030) {
        return DATA_ERROR_VALIDATION;
    }

    return DATA_SUCCESS;
}

//
// Load courses from CSV file
///
Course* load_courses(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        *count = 0;
        return NULL;
    }

    /* Initial allocation for courses */
    int capacity = 10;
    Course* courses = (Course*)malloc(capacity * sizeof(Course));
    if (courses == NULL) {
        fclose(file);
        *count = 0;
        return NULL;
    }

    *count = 0;
    char line[2048];
    int line_number = 0;

    /* Skip header line */
    if (fgets(line, sizeof(line), file) != NULL) {
        line_number++;
    }

    /* Read data lines */
    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;

        /* Remove newline */
        line[strcspn(line, "\n")] = '\0';

        /* Skip empty lines */
        if (strlen(line) == 0) continue;

        /* Parse CSV line */
        char* fields[10];
        int field_count = parse_csv_line(line, fields, 10);

        if (field_count < 10) {
            fprintf(stderr, "Warning: Skipping line %d - insufficient fields\n", line_number);
            continue;
        }

        /* Expand array if needed */
        if (*count >= capacity) {
            capacity *= 2;
            Course* temp = (Course*)realloc(courses, capacity * sizeof(Course));
            if (temp == NULL) {
                free(courses);
                fclose(file);
                *count = 0;
                return NULL;
            }
            courses = temp;
        }

        /* Parse fields into course structure */
        Course course;
        strncpy(course.title, fields[0], sizeof(course.title) - 1);
        course.title[sizeof(course.title) - 1] = '\0';

        strncpy(course.course_code, fields[1], sizeof(course.course_code) - 1);
        course.course_code[sizeof(course.course_code) - 1] = '\0';

        strncpy(course.subject_area, fields[2], sizeof(course.subject_area) - 1);
        course.subject_area[sizeof(course.subject_area) - 1] = '\0';

        course.difficulty = atoi(fields[3]);
        course.workload = atoi(fields[4]);
        course.has_exam = atoi(fields[5]);
        course.has_midterm = atoi(fields[6]);
        course.rating = (float)atof(fields[7]);

        strncpy(course.description, fields[8], sizeof(course.description) - 1);
        course.description[sizeof(course.description) - 1] = '\0';

        course.year_offered = atoi(fields[9]);

        /* Validate and add course */
        if (validate_course(course) == DATA_SUCCESS) {
            courses[*count] = course;
            (*count)++;
        } else {
            fprintf(stderr, "Warning: Skipping line %d - invalid course data\n", line_number);
        }
    }

    fclose(file);
    return courses;
}

//
// Save courses to CSV file
///
int save_courses(Course* courses, int count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return DATA_ERROR_WRITE;
    }

    /* Write header */
    fprintf(file, "title,course_code,subject_area,difficulty,workload,has_exam,has_midterm,rating,description,year_offered\n");

    /* Write each course */
    for (int i = 0; i < count; i++) {
        char escaped_title[200];
        char escaped_description[1000];

        escape_csv_field(escaped_title, courses[i].title, sizeof(escaped_title));
        escape_csv_field(escaped_description, courses[i].description, sizeof(escaped_description));

        fprintf(file, "%s,%s,%s,%d,%d,%d,%d,%.1f,%s,%d\n",
                escaped_title,
                courses[i].course_code,
                courses[i].subject_area,
                courses[i].difficulty,
                courses[i].workload,
                courses[i].has_exam,
                courses[i].has_midterm,
                courses[i].rating,
                escaped_description,
                courses[i].year_offered);
    }

    fclose(file);
    return DATA_SUCCESS;
}

//
// Add a new course to the array
///
int add_course(Course** courses, int* count, Course new_course) {
    /* Validate the new course */
    if (validate_course(new_course) != DATA_SUCCESS) {
        return DATA_ERROR_VALIDATION;
    }

    /* Reallocate memory for one more course */
    Course* temp = (Course*)realloc(*courses, (*count + 1) * sizeof(Course));
    if (temp == NULL) {
        return DATA_ERROR_MEMORY;
    }

    *courses = temp;
    (*courses)[*count] = new_course;
    (*count)++;

    return DATA_SUCCESS;
}

//
// Free memory allocated for courses
///
void free_courses(Course* courses) {
    if (courses != NULL) {
        free(courses);
    }
}

//
// Get error message for error code
///
const char* get_data_error_message(int error_code) {
    switch (error_code) {
        case DATA_SUCCESS:
            return "Success";
        case DATA_ERROR_FILE_NOT_FOUND:
            return "File not found";
        case DATA_ERROR_INVALID_FORMAT:
            return "Invalid file format";
        case DATA_ERROR_MEMORY:
            return "Memory allocation failed";
        case DATA_ERROR_VALIDATION:
            return "Course validation failed";
        case DATA_ERROR_WRITE:
            return "Error writing to file";
        default:
            return "Unknown error";
    }
}
