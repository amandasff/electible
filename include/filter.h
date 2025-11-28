// SE 2XC3 Lab 7.2: Electible
// filter.h
// Amanda Wu

#ifndef FILTER_H
#define FILTER_H

// struct holds all the info about a course
typedef struct {
    char title[100];
    char course_code[10];
    char subject_area[50];
    int difficulty;        // 1-5 scale
    int workload;          // 1-5 scale
    int has_exam;          // 1 = yes, 0 = no
    int has_midterm;       // 1 = yes, 0 = no
    float rating;          // 0.0-5.0
    char description[500];
    int year_offered;
} Course;

// FilterCriteria filters by multiple things at once
typedef struct {
    char subject_area[50];    // empty string = no filter
    int min_difficulty;       // -1 = no min
    int max_difficulty;       // -1 = no max
    int min_workload;         // -1 = no min
    int max_workload;         // -1 = no max
    int has_exam;             // -1 = no filter
    int has_midterm;          // -1 = no filter
    float min_rating;         // -1.0 = no min
} FilterCriteria;

// Filter courses by subject area (case-insensitive)
Course* filter_by_subject(Course* courses, int count, const char* subject, int* result_count);

// Filter courses by difficulty range
Course* filter_by_difficulty(Course* courses, int count, int min, int max, int* result_count);

// Filter courses by workload range
Course* filter_by_workload(Course* courses, int count, int min, int max, int* result_count);

// Filter courses that have/don't have exams
Course* filter_by_exam_presence(Course* courses, int count, int has_exam, int* result_count);

// Filter courses that have/don't have midterms
Course* filter_by_midterm_presence(Course* courses, int count, int has_midterm, int* result_count);

// Filter courses by minimum rating
Course* filter_by_rating(Course* courses, int count, float min_rating, int* result_count);

// Apply multiple filters at the same time
Course* apply_multiple_filters(Course* courses, int count, FilterCriteria criteria, int* result_count);

// Create a default FilterCriteria with no filters set
FilterCriteria create_default_filter_criteria(void);

#endif
