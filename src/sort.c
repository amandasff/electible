// SE 2XC3 Lab 7.2: Electible
// Module B: Sorting
// Anshika Patel
// Uses merge sort algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sort.h"

// Helper function declarations
static void merge_sort_generic(Course* courses, int count, int ascending,
                                int (*compare)(Course*, Course*, int));
static void merge(Course* courses, int left, int mid, int right, int ascending,
                  int (*compare)(Course*, Course*, int));
static int compare_difficulty(Course* a, Course* b, int ascending);
static int compare_workload(Course* a, Course* b, int ascending);
static int compare_rating(Course* a, Course* b, int ascending);
static int compare_course_code(Course* a, Course* b, int ascending);
static int compare_title(Course* a, Course* b, int ascending);
static int compare_multi_criteria(Course* a, Course* b, SortCriteria* criteria, int num_criteria);

// Compare two courses by difficulty
static int compare_difficulty(Course* a, Course* b, int ascending) {
    int diff = a->difficulty - b->difficulty;
    return ascending ? diff : -diff;
}

// Compare two courses by workload
static int compare_workload(Course* a, Course* b, int ascending) {
    int diff = a->workload - b->workload;
    return ascending ? diff : -diff;
}

// Compare two courses by rating
static int compare_rating(Course* a, Course* b, int ascending) {
    float diff = a->rating - b->rating;
    if (diff < 0) return ascending ? -1 : 1;
    if (diff > 0) return ascending ? 1 : -1;
    return 0;
}

// Compare two courses by course code (alphabetically)
static int compare_course_code(Course* a, Course* b, int ascending) {
    int cmp = strcmp(a->course_code, b->course_code);
    return ascending ? cmp : -cmp;
}

// Compare two courses by title (alphabetically)
static int compare_title(Course* a, Course* b, int ascending) {
    int cmp = strcmp(a->title, b->title);
    return ascending ? cmp : -cmp;
}

// Merge two sorted subarrays
static void merge(Course* courses, int left, int mid, int right, int ascending,
                  int (*compare)(Course*, Course*, int)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Make temp arrays
    Course* left_array = (Course*)malloc(n1 * sizeof(Course));
    Course* right_array = (Course*)malloc(n2 * sizeof(Course));

    if (left_array == NULL || right_array == NULL) {
        free(left_array);
        free(right_array);
        return;
    }

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++) {
        left_array[i] = courses[left + i];
    }
    for (int j = 0; j < n2; j++) {
        right_array[j] = courses[mid + 1 + j];
    }

    // Merge the temp arrays back
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        // If equal, keep original order (stable sort)
        if (compare(&left_array[i], &right_array[j], ascending) <= 0) {
            courses[k] = left_array[i];
            i++;
        } else {
            courses[k] = right_array[j];
            j++;
        }
        k++;
    }

    // Copy any leftover elements
    while (i < n1) {
        courses[k] = left_array[i];
        i++;
        k++;
    }

    while (j < n2) {
        courses[k] = right_array[j];
        j++;
        k++;
    }

    free(left_array);
    free(right_array);
}

// Recursive merge sort
static void merge_sort_recursive(Course* courses, int left, int right, int ascending,
                                  int (*compare)(Course*, Course*, int)) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort both halves
        merge_sort_recursive(courses, left, mid, ascending, compare);
        merge_sort_recursive(courses, mid + 1, right, ascending, compare);

        // Merge them
        merge(courses, left, mid, right, ascending, compare);
    }
}

// Generic merge sort wrapper
static void merge_sort_generic(Course* courses, int count, int ascending,
                                int (*compare)(Course*, Course*, int)) {
    if (courses == NULL || count <= 1) {
        return;
    }
    merge_sort_recursive(courses, 0, count - 1, ascending, compare);
}

// Sort by difficulty
void sort_by_difficulty(Course* courses, int count, int ascending) {
    merge_sort_generic(courses, count, ascending, compare_difficulty);
}

// Sort by workload
void sort_by_workload(Course* courses, int count, int ascending) {
    merge_sort_generic(courses, count, ascending, compare_workload);
}

// Sort by rating
void sort_by_rating(Course* courses, int count, int ascending) {
    merge_sort_generic(courses, count, ascending, compare_rating);
}

// Sort by course code
void sort_by_course_code(Course* courses, int count, int ascending) {
    merge_sort_generic(courses, count, ascending, compare_course_code);
}

// Sort by title
void sort_by_title(Course* courses, int count, int ascending) {
    merge_sort_generic(courses, count, ascending, compare_title);
}

// Compare courses using multiple criteria
static int compare_multi_criteria(Course* a, Course* b, SortCriteria* criteria, int num_criteria) {
    for (int i = 0; i < num_criteria; i++) {
        int cmp = 0;
        int ascending = (criteria[i].order == ASCENDING) ? 1 : 0;

        switch (criteria[i].field) {
            case SORT_BY_DIFFICULTY:
                cmp = compare_difficulty(a, b, ascending);
                break;
            case SORT_BY_WORKLOAD:
                cmp = compare_workload(a, b, ascending);
                break;
            case SORT_BY_RATING:
                cmp = compare_rating(a, b, ascending);
                break;
            case SORT_BY_COURSE_CODE:
                cmp = compare_course_code(a, b, ascending);
                break;
            case SORT_BY_TITLE:
                cmp = compare_title(a, b, ascending);
                break;
        }

        // If not equal, return result
        if (cmp != 0) {
            return cmp;
        }
        // If equal, try next criterion
    }

    // All criteria equal
    return 0;
}

// Merge function for multi-criteria
static void merge_multi(Course* courses, int left, int mid, int right,
                        SortCriteria* criteria, int num_criteria) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Make temp arrays
    Course* left_array = (Course*)malloc(n1 * sizeof(Course));
    Course* right_array = (Course*)malloc(n2 * sizeof(Course));

    if (left_array == NULL || right_array == NULL) {
        free(left_array);
        free(right_array);
        return;
    }

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++) {
        left_array[i] = courses[left + i];
    }
    for (int j = 0; j < n2; j++) {
        right_array[j] = courses[mid + 1 + j];
    }

    // Merge the arrays
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (compare_multi_criteria(&left_array[i], &right_array[j], criteria, num_criteria) <= 0) {
            courses[k] = left_array[i];
            i++;
        } else {
            courses[k] = right_array[j];
            j++;
        }
        k++;
    }

    // Copy any leftover elements
    while (i < n1) {
        courses[k] = left_array[i];
        i++;
        k++;
    }

    while (j < n2) {
        courses[k] = right_array[j];
        j++;
        k++;
    }

    free(left_array);
    free(right_array);
}

// Recursive merge sort for multi-criteria
static void merge_sort_multi_recursive(Course* courses, int left, int right,
                                        SortCriteria* criteria, int num_criteria) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort_multi_recursive(courses, left, mid, criteria, num_criteria);
        merge_sort_multi_recursive(courses, mid + 1, right, criteria, num_criteria);

        merge_multi(courses, left, mid, right, criteria, num_criteria);
    }
}

// Sort by multiple criteria
void sort_multi_criteria(Course* courses, int count, SortCriteria* criteria, int num_criteria) {
    if (courses == NULL || count <= 1 || criteria == NULL || num_criteria <= 0) {
        return;
    }
    merge_sort_multi_recursive(courses, 0, count - 1, criteria, num_criteria);
}
