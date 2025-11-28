// SE 2XC3 Lab 7.2: Electible
// filter.c
// Amanda Wu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/filter.h"

// Helper function to make a string lowercase
static void to_lowercase(char* str, char* result, size_t max_len) {
    size_t i;
    for (i = 0; i < max_len - 1 && str[i] != '\0'; i++) {
        result[i] = (char)tolower((unsigned char)str[i]);
    }
    result[i] = '\0';
}

// Create default filter criteria (no filters)
FilterCriteria create_default_filter_criteria(void) {
    FilterCriteria criteria;
    criteria.subject_area[0] = '\0';
    criteria.min_difficulty = -1;
    criteria.max_difficulty = -1;
    criteria.min_workload = -1;
    criteria.max_workload = -1;
    criteria.has_exam = -1;
    criteria.has_midterm = -1;
    criteria.min_rating = -1.0f;
    return criteria;
}

// Filter courses by subject area
Course* filter_by_subject(Course* courses, int count, const char* subject, int* result_count) {
    if (courses == NULL || count <= 0 || subject == NULL) {
        *result_count = 0;
        return NULL;
    }

    // Count how many courses match
    int matches = 0;
    char subject_lower[50];
    char course_subject_lower[50];
    to_lowercase((char*)subject, subject_lower, sizeof(subject_lower));

    for (int i = 0; i < count; i++) {
        to_lowercase(courses[i].subject_area, course_subject_lower, sizeof(course_subject_lower));
        if (strstr(course_subject_lower, subject_lower) != NULL) {
            matches++;
        }
    }

    if (matches == 0) {
        *result_count = 0;
        return NULL;
    }

    // Allocate array for results
    Course* results = (Course*)malloc(matches * sizeof(Course));
    if (results == NULL) {
        *result_count = 0;
        return NULL;
    }

    // Copy matching courses
    int result_idx = 0;
    for (int i = 0; i < count; i++) {
        to_lowercase(courses[i].subject_area, course_subject_lower, sizeof(course_subject_lower));
        if (strstr(course_subject_lower, subject_lower) != NULL) {
            results[result_idx++] = courses[i];
        }
    }

    *result_count = matches;
    return results;
}

// Filter courses by difficulty range
Course* filter_by_difficulty(Course* courses, int count, int min, int max, int* result_count) {
    if (courses == NULL || count <= 0) {
        *result_count = 0;
        return NULL;
    }

    // Count matches
    int matches = 0;
    for (int i = 0; i < count; i++) {
        if (courses[i].difficulty >= min && courses[i].difficulty <= max) {
            matches++;
        }
    }

    if (matches == 0) {
        *result_count = 0;
        return NULL;
    }

    // Allocate and fill results
    Course* results = (Course*)malloc(matches * sizeof(Course));
    if (results == NULL) {
        *result_count = 0;
        return NULL;
    }

    int result_idx = 0;
    for (int i = 0; i < count; i++) {
        if (courses[i].difficulty >= min && courses[i].difficulty <= max) {
            results[result_idx++] = courses[i];
        }
    }

    *result_count = matches;
    return results;
}

// Filter courses by workload range
Course* filter_by_workload(Course* courses, int count, int min, int max, int* result_count) {
    if (courses == NULL || count <= 0) {
        *result_count = 0;
        return NULL;
    }

    // Count matches
    int matches = 0;
    for (int i = 0; i < count; i++) {
        if (courses[i].workload >= min && courses[i].workload <= max) {
            matches++;
        }
    }

    if (matches == 0) {
        *result_count = 0;
        return NULL;
    }

    // Allocate and fill results
    Course* results = (Course*)malloc(matches * sizeof(Course));
    if (results == NULL) {
        *result_count = 0;
        return NULL;
    }

    int result_idx = 0;
    for (int i = 0; i < count; i++) {
        if (courses[i].workload >= min && courses[i].workload <= max) {
            results[result_idx++] = courses[i];
        }
    }

    *result_count = matches;
    return results;
}

// Filter courses by exam presence
Course* filter_by_exam_presence(Course* courses, int count, int has_exam, int* result_count) {
    if (courses == NULL || count <= 0) {
        *result_count = 0;
        return NULL;
    }

    // Count matches
    int matches = 0;
    for (int i = 0; i < count; i++) {
        if (courses[i].has_exam == has_exam) {
            matches++;
        }
    }

    if (matches == 0) {
        *result_count = 0;
        return NULL;
    }

    // Allocate and fill results
    Course* results = (Course*)malloc(matches * sizeof(Course));
    if (results == NULL) {
        *result_count = 0;
        return NULL;
    }

    int result_idx = 0;
    for (int i = 0; i < count; i++) {
        if (courses[i].has_exam == has_exam) {
            results[result_idx++] = courses[i];
        }
    }

    *result_count = matches;
    return results;
}

// Filter courses by midterm presence
Course* filter_by_midterm_presence(Course* courses, int count, int has_midterm, int* result_count) {
    if (courses == NULL || count <= 0) {
        *result_count = 0;
        return NULL;
    }

    // Count matches
    int matches = 0;
    for (int i = 0; i < count; i++) {
        if (courses[i].has_midterm == has_midterm) {
            matches++;
        }
    }

    if (matches == 0) {
        *result_count = 0;
        return NULL;
    }

    // Allocate and fill results
    Course* results = (Course*)malloc(matches * sizeof(Course));
    if (results == NULL) {
        *result_count = 0;
        return NULL;
    }

    int result_idx = 0;
    for (int i = 0; i < count; i++) {
        if (courses[i].has_midterm == has_midterm) {
            results[result_idx++] = courses[i];
        }
    }

    *result_count = matches;
    return results;
}

// Filter courses by minimum rating
Course* filter_by_rating(Course* courses, int count, float min_rating, int* result_count) {
    if (courses == NULL || count <= 0) {
        *result_count = 0;
        return NULL;
    }

    // Count matches
    int matches = 0;
    for (int i = 0; i < count; i++) {
        if (courses[i].rating >= min_rating) {
            matches++;
        }
    }

    if (matches == 0) {
        *result_count = 0;
        return NULL;
    }

    // Allocate and fill results
    Course* results = (Course*)malloc(matches * sizeof(Course));
    if (results == NULL) {
        *result_count = 0;
        return NULL;
    }

    int result_idx = 0;
    for (int i = 0; i < count; i++) {
        if (courses[i].rating >= min_rating) {
            results[result_idx++] = courses[i];
        }
    }

    *result_count = matches;
    return results;
}

// Apply multiple filters at once
Course* apply_multiple_filters(Course* courses, int count, FilterCriteria criteria, int* result_count) {
    if (courses == NULL || count <= 0) {
        *result_count = 0;
        return NULL;
    }

    // Count matches
    int matches = 0;
    char subject_lower[50];
    char course_subject_lower[50];
    int has_subject_filter = (strlen(criteria.subject_area) > 0);

    if (has_subject_filter) {
        to_lowercase(criteria.subject_area, subject_lower, sizeof(subject_lower));
    }

    for (int i = 0; i < count; i++) {
        int match = 1;

        // Check subject filter
        if (has_subject_filter) {
            to_lowercase(courses[i].subject_area, course_subject_lower, sizeof(course_subject_lower));
            if (strstr(course_subject_lower, subject_lower) == NULL) {
                match = 0;
            }
        }

        // Check difficulty filter
        if (match && criteria.min_difficulty >= 0) {
            if (courses[i].difficulty < criteria.min_difficulty) {
                match = 0;
            }
        }
        if (match && criteria.max_difficulty >= 0) {
            if (courses[i].difficulty > criteria.max_difficulty) {
                match = 0;
            }
        }

        // Check workload filter
        if (match && criteria.min_workload >= 0) {
            if (courses[i].workload < criteria.min_workload) {
                match = 0;
            }
        }
        if (match && criteria.max_workload >= 0) {
            if (courses[i].workload > criteria.max_workload) {
                match = 0;
            }
        }

        // Check exam filter
        if (match && criteria.has_exam >= 0) {
            if (courses[i].has_exam != criteria.has_exam) {
                match = 0;
            }
        }

        // Check midterm filter
        if (match && criteria.has_midterm >= 0) {
            if (courses[i].has_midterm != criteria.has_midterm) {
                match = 0;
            }
        }

        // Check rating filter
        if (match && criteria.min_rating >= 0.0f) {
            if (courses[i].rating < criteria.min_rating) {
                match = 0;
            }
        }

        if (match) {
            matches++;
        }
    }

    if (matches == 0) {
        *result_count = 0;
        return NULL;
    }

    // Allocate and fill results
    Course* results = (Course*)malloc(matches * sizeof(Course));
    if (results == NULL) {
        *result_count = 0;
        return NULL;
    }

    int result_idx = 0;
    for (int i = 0; i < count; i++) {
        int match = 1;

        // Apply all the same filters again
        if (has_subject_filter) {
            to_lowercase(courses[i].subject_area, course_subject_lower, sizeof(course_subject_lower));
            if (strstr(course_subject_lower, subject_lower) == NULL) {
                match = 0;
            }
        }

        if (match && criteria.min_difficulty >= 0 && courses[i].difficulty < criteria.min_difficulty) {
            match = 0;
        }
        if (match && criteria.max_difficulty >= 0 && courses[i].difficulty > criteria.max_difficulty) {
            match = 0;
        }
        if (match && criteria.min_workload >= 0 && courses[i].workload < criteria.min_workload) {
            match = 0;
        }
        if (match && criteria.max_workload >= 0 && courses[i].workload > criteria.max_workload) {
            match = 0;
        }
        if (match && criteria.has_exam >= 0 && courses[i].has_exam != criteria.has_exam) {
            match = 0;
        }
        if (match && criteria.has_midterm >= 0 && courses[i].has_midterm != criteria.has_midterm) {
            match = 0;
        }
        if (match && criteria.min_rating >= 0.0f && courses[i].rating < criteria.min_rating) {
            match = 0;
        }

        if (match) {
            results[result_idx++] = courses[i];
        }
    }

    *result_count = matches;
    return results;
}
