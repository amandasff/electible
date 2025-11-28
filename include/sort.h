// SE 2XC3 Lab 7.2: Electible
// Module B: Sorting
// Anshika Patel

#ifndef SORT_H
#define SORT_H

#include "filter.h"

// Sort order options
typedef enum {
    ASCENDING = 0,
    DESCENDING = 1
} SortOrder;

// What field to sort by
typedef enum {
    SORT_BY_DIFFICULTY = 0,
    SORT_BY_WORKLOAD = 1,
    SORT_BY_RATING = 2,
    SORT_BY_COURSE_CODE = 3,
    SORT_BY_TITLE = 4
} SortField;

// Struct for sorting by multiple things
typedef struct {
    SortField field;
    SortOrder order;
} SortCriteria;

// Sort courses by difficulty (uses merge sort)
void sort_by_difficulty(Course* courses, int count, int ascending);

// Sort courses by workload (uses merge sort)
void sort_by_workload(Course* courses, int count, int ascending);

// Sort courses by rating (uses merge sort)
void sort_by_rating(Course* courses, int count, int ascending);

// Sort courses by course code alphabetically
void sort_by_course_code(Course* courses, int count, int ascending);

// Sort courses by title alphabetically
void sort_by_title(Course* courses, int count, int ascending);

// Sort by multiple criteria (e.g., difficulty then rating)
void sort_multi_criteria(Course* courses, int count, SortCriteria* criteria, int num_criteria);

#endif
