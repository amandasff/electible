/**
 * SE 2XC3 Lab 7.2: Electible Test Suite
 * Comprehensive tests for all modules
 * Developer: Amanda Wu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/data.h"
#include "../include/filter.h"
#include "../include/sort.h"

/* Test counters */
static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

/* ANSI colors for test output */
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_RESET   "\033[0m"

/* Helper macro for assertions */
#define TEST_ASSERT(condition, message) do { \
    tests_run++; \
    if (condition) { \
        tests_passed++; \
        printf("  %s✓%s %s\n", COLOR_GREEN, COLOR_RESET, message); \
    } else { \
        tests_failed++; \
        printf("  %s✗%s %s\n", COLOR_RED, COLOR_RESET, message); \
    } \
} while(0)

/* Create sample test data */
Course* create_test_courses(int* count) {
    *count = 5;
    Course* courses = (Course*)malloc(5 * sizeof(Course));

    /* Course 1 */
    strcpy(courses[0].title, "Introduction to Programming");
    strcpy(courses[0].course_code, "CS101");
    strcpy(courses[0].subject_area, "Computer Science");
    courses[0].difficulty = 2;
    courses[0].workload = 3;
    courses[0].has_exam = 1;
    courses[0].has_midterm = 1;
    courses[0].rating = 4.5f;
    strcpy(courses[0].description, "Learn basic programming");
    courses[0].year_offered = 2025;

    /* Course 2 */
    strcpy(courses[1].title, "Calculus I");
    strcpy(courses[1].course_code, "MATH101");
    strcpy(courses[1].subject_area, "Mathematics");
    courses[1].difficulty = 4;
    courses[1].workload = 5;
    courses[1].has_exam = 1;
    courses[1].has_midterm = 1;
    courses[1].rating = 3.8f;
    strcpy(courses[1].description, "Differential calculus");
    courses[1].year_offered = 2025;

    /* Course 3 */
    strcpy(courses[2].title, "Introduction to Business");
    strcpy(courses[2].course_code, "BUS101");
    strcpy(courses[2].subject_area, "Business");
    courses[2].difficulty = 1;
    courses[2].workload = 2;
    courses[2].has_exam = 1;
    courses[2].has_midterm = 0;
    courses[2].rating = 4.2f;
    strcpy(courses[2].description, "Business fundamentals");
    courses[2].year_offered = 2025;

    /* Course 4 */
    strcpy(courses[3].title, "Data Structures");
    strcpy(courses[3].course_code, "CS201");
    strcpy(courses[3].subject_area, "Computer Science");
    courses[3].difficulty = 4;
    courses[3].workload = 4;
    courses[3].has_exam = 1;
    courses[3].has_midterm = 1;
    courses[3].rating = 4.0f;
    strcpy(courses[3].description, "Advanced data structures");
    courses[3].year_offered = 2025;

    /* Course 5 */
    strcpy(courses[4].title, "Philosophy Ethics");
    strcpy(courses[4].course_code, "PHIL101");
    strcpy(courses[4].subject_area, "Humanities");
    courses[4].difficulty = 2;
    courses[4].workload = 2;
    courses[4].has_exam = 0;
    courses[4].has_midterm = 1;
    courses[4].rating = 4.7f;
    strcpy(courses[4].description, "Introduction to ethics");
    courses[4].year_offered = 2025;

    return courses;
}

/* Test: Course validation */
void test_course_validation(void) {
    printf("\n%sTesting Course Validation:%s\n", COLOR_YELLOW, COLOR_RESET);

    Course valid_course;
    strcpy(valid_course.title, "Test Course");
    strcpy(valid_course.course_code, "TEST101");
    strcpy(valid_course.subject_area, "Testing");
    valid_course.difficulty = 3;
    valid_course.workload = 3;
    valid_course.has_exam = 1;
    valid_course.has_midterm = 0;
    valid_course.rating = 4.0f;
    strcpy(valid_course.description, "A test course");
    valid_course.year_offered = 2025;

    TEST_ASSERT(validate_course(valid_course) == DATA_SUCCESS,
                "Valid course passes validation");

    /* Test invalid difficulty */
    Course invalid_course = valid_course;
    invalid_course.difficulty = 6;
    TEST_ASSERT(validate_course(invalid_course) == DATA_ERROR_VALIDATION,
                "Invalid difficulty (6) fails validation");

    /* Test invalid workload */
    invalid_course = valid_course;
    invalid_course.workload = 0;
    TEST_ASSERT(validate_course(invalid_course) == DATA_ERROR_VALIDATION,
                "Invalid workload (0) fails validation");

    /* Test invalid rating */
    invalid_course = valid_course;
    invalid_course.rating = 6.0f;
    TEST_ASSERT(validate_course(invalid_course) == DATA_ERROR_VALIDATION,
                "Invalid rating (6.0) fails validation");
}

/* Test: Filter by subject */
void test_filter_by_subject(void) {
    printf("\n%sTesting Filter by Subject:%s\n", COLOR_YELLOW, COLOR_RESET);

    int count;
    Course* courses = create_test_courses(&count);

    int result_count;
    Course* filtered = filter_by_subject(courses, count, "Computer Science", &result_count);

    TEST_ASSERT(filtered != NULL, "Filter by 'Computer Science' returns results");
    TEST_ASSERT(result_count == 2, "Filter finds 2 Computer Science courses");

    if (filtered != NULL) {
        free(filtered);
    }

    /* Test case-insensitive filtering */
    filtered = filter_by_subject(courses, count, "computer science", &result_count);
    TEST_ASSERT(result_count == 2, "Case-insensitive filtering works");

    if (filtered != NULL) {
        free(filtered);
    }

    /* Test no matches */
    filtered = filter_by_subject(courses, count, "Nonexistent", &result_count);
    TEST_ASSERT(filtered == NULL && result_count == 0, "Filter with no matches returns NULL");

    free(courses);
}

/* Test: Filter by difficulty */
void test_filter_by_difficulty(void) {
    printf("\n%sTesting Filter by Difficulty:%s\n", COLOR_YELLOW, COLOR_RESET);

    int count;
    Course* courses = create_test_courses(&count);

    int result_count;
    Course* filtered = filter_by_difficulty(courses, count, 1, 2, &result_count);

    TEST_ASSERT(filtered != NULL, "Filter by difficulty 1-2 returns results");
    TEST_ASSERT(result_count == 2, "Filter finds 2 courses with difficulty 1-2");

    if (filtered != NULL) {
        free(filtered);
    }

    /* Test difficulty 4-5 */
    filtered = filter_by_difficulty(courses, count, 4, 5, &result_count);
    TEST_ASSERT(result_count == 2, "Filter finds 2 courses with difficulty 4-5");

    if (filtered != NULL) {
        free(filtered);
    }

    free(courses);
}

/* Test: Filter by exam presence */
void test_filter_by_exam(void) {
    printf("\n%sTesting Filter by Exam Presence:%s\n", COLOR_YELLOW, COLOR_RESET);

    int count;
    Course* courses = create_test_courses(&count);

    int result_count;
    Course* filtered = filter_by_exam_presence(courses, count, 1, &result_count);

    TEST_ASSERT(result_count == 4, "Filter finds 4 courses with exams");

    if (filtered != NULL) {
        free(filtered);
    }

    filtered = filter_by_exam_presence(courses, count, 0, &result_count);
    TEST_ASSERT(result_count == 1, "Filter finds 1 course without exam");

    if (filtered != NULL) {
        free(filtered);
    }

    free(courses);
}

/* Test: Multi-criteria filtering */
void test_multi_filter(void) {
    printf("\n%sTesting Multi-Criteria Filtering:%s\n", COLOR_YELLOW, COLOR_RESET);

    int count;
    Course* courses = create_test_courses(&count);

    FilterCriteria criteria = create_default_filter_criteria();
    strcpy(criteria.subject_area, "Computer Science");
    criteria.min_difficulty = 1;
    criteria.max_difficulty = 3;

    int result_count;
    Course* filtered = apply_multiple_filters(courses, count, criteria, &result_count);

    TEST_ASSERT(result_count == 1, "Multi-filter finds 1 easy CS course");

    if (filtered != NULL) {
        free(filtered);
    }

    /* Test with rating filter */
    criteria = create_default_filter_criteria();
    criteria.min_rating = 4.5f;

    filtered = apply_multiple_filters(courses, count, criteria, &result_count);
    TEST_ASSERT(result_count == 2, "Filter finds 2 courses with rating >= 4.5");

    if (filtered != NULL) {
        free(filtered);
    }

    free(courses);
}

/* Test: Sort by difficulty */
void test_sort_by_difficulty(void) {
    printf("\n%sTesting Sort by Difficulty:%s\n", COLOR_YELLOW, COLOR_RESET);

    int count;
    Course* courses = create_test_courses(&count);

    /* Sort ascending */
    sort_by_difficulty(courses, count, 1);
    TEST_ASSERT(courses[0].difficulty <= courses[1].difficulty,
                "Ascending sort: first <= second");
    TEST_ASSERT(courses[count-2].difficulty <= courses[count-1].difficulty,
                "Ascending sort: second-last <= last");

    /* Sort descending */
    sort_by_difficulty(courses, count, 0);
    TEST_ASSERT(courses[0].difficulty >= courses[1].difficulty,
                "Descending sort: first >= second");
    TEST_ASSERT(courses[count-2].difficulty >= courses[count-1].difficulty,
                "Descending sort: second-last >= last");

    free(courses);
}

/* Test: Sort by rating */
void test_sort_by_rating(void) {
    printf("\n%sTesting Sort by Rating:%s\n", COLOR_YELLOW, COLOR_RESET);

    int count;
    Course* courses = create_test_courses(&count);

    /* Sort ascending */
    sort_by_rating(courses, count, 1);
    TEST_ASSERT(courses[0].rating <= courses[1].rating,
                "Ascending sort: first <= second");

    /* Sort descending */
    sort_by_rating(courses, count, 0);
    TEST_ASSERT(courses[0].rating >= courses[1].rating,
                "Descending sort: first >= second");

    free(courses);
}

/* Test: Add course */
void test_add_course(void) {
    printf("\n%sTesting Add Course:%s\n", COLOR_YELLOW, COLOR_RESET);

    int count;
    Course* courses = create_test_courses(&count);

    Course new_course;
    strcpy(new_course.title, "New Course");
    strcpy(new_course.course_code, "NEW101");
    strcpy(new_course.subject_area, "Testing");
    new_course.difficulty = 3;
    new_course.workload = 3;
    new_course.has_exam = 1;
    new_course.has_midterm = 1;
    new_course.rating = 4.0f;
    strcpy(new_course.description, "A new test course");
    new_course.year_offered = 2025;

    int original_count = count;
    int result = add_course(&courses, &count, new_course);

    TEST_ASSERT(result == DATA_SUCCESS, "Add course succeeds");
    TEST_ASSERT(count == original_count + 1, "Course count incremented");
    TEST_ASSERT(strcmp(courses[count-1].course_code, "NEW101") == 0,
                "New course added at end");

    free(courses);
}

/* Test: CSV parsing edge cases */
void test_csv_parsing(void) {
    printf("\n%sTesting CSV Parsing:%s\n", COLOR_YELLOW, COLOR_RESET);

    char test_line[] = "\"Title with, comma\",CODE101,Subject,3,4,1,0,4.5,\"Description\",2025";
    char* fields[10];

    int field_count = parse_csv_line(test_line, fields, 10);

    TEST_ASSERT(field_count == 10, "Parse line with 10 fields");
    TEST_ASSERT(strcmp(fields[0], "Title with, comma") == 0,
                "Quoted field with comma parsed correctly");
    TEST_ASSERT(strcmp(fields[1], "CODE101") == 0,
                "Simple field parsed correctly");
}

/* Main test runner */
int main(void) {
    printf("\n");
    printf("========================================\n");
    printf("  Electible Test Suite\n");
    printf("  SE 2XC3 Lab 7.2\n");
    printf("========================================\n");

    /* Run all tests */
    test_course_validation();
    test_filter_by_subject();
    test_filter_by_difficulty();
    test_filter_by_exam();
    test_multi_filter();
    test_sort_by_difficulty();
    test_sort_by_rating();
    test_add_course();
    test_csv_parsing();

    /* Print summary */
    printf("\n");
    printf("========================================\n");
    printf("  Test Summary\n");
    printf("========================================\n");
    printf("  Total tests:  %d\n", tests_run);
    printf("  %sPassed:%s       %d\n", COLOR_GREEN, COLOR_RESET, tests_passed);
    printf("  %sFailed:%s       %d\n", COLOR_RED, COLOR_RESET, tests_failed);
    printf("========================================\n");

    if (tests_failed == 0) {
        printf("\n%s✓ All tests passed!%s\n\n", COLOR_GREEN, COLOR_RESET);
        return 0;
    } else {
        printf("\n%s✗ Some tests failed.%s\n\n", COLOR_RED, COLOR_RESET);
        return 1;
    }
}
