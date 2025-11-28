# Electible - McMaster First-Year Elective Finder

[![Build Status](https://github.com/your-username/electible/workflows/CI/badge.svg)](https://github.com/your-username/electible/actions)

A command-line application designed to help McMaster first-year engineering students filter, sort, and explore elective courses based on various criteria including difficulty, workload, subject area, and ratings.

**SE 2XC3 Lab 7.2 Team Assignment - McMaster University, 2025**

## Team Members

| Name | Module | Responsibilities |
|------|--------|------------------|
| Amanda Wu | Module A | Filtering & Category Logic |
| Anshika Patel | Module B | Sorting Algorithm (Merge Sort) |
| Khushi Ved | Module C | Data Management & Backend |
| Yasmine Abdelmalek | Module D | UI & Integration |

## Features

- **Browse All Courses**: View the complete catalog of available elective courses
- **Advanced Filtering**: Filter courses by:
  - Subject area (Computer Science, Math, Business, etc.)
  - Difficulty level (1-5 scale)
  - Workload level (1-5 scale)
  - Exam/midterm requirements
  - Minimum rating
- **Flexible Sorting**: Sort courses by difficulty, workload, rating, course code, or title
- **Multi-Criteria Filtering**: Combine multiple filters simultaneously
- **Crowdsourcing**: Add new courses to the database
- **Smart Recommendations**: Get personalized course suggestions
- **Data Persistence**: Changes are automatically saved to CSV
- **Comprehensive Testing**: Full test suite with edge case coverage

## Project Structure

```
electible/
├── src/
│   ├── main.c          # Main program entry point
│   ├── filter.c        # Module A: Filtering logic
│   ├── sort.c          # Module B: Sorting algorithms
│   ├── data.c          # Module C: Data management
│   └── ui.c            # Module D: User interface
├── include/
│   ├── filter.h        # Filtering function declarations
│   ├── sort.h          # Sorting function declarations
│   ├── data.h          # Data management declarations
│   └── ui.h            # UI function declarations
├── tests/
│   └── test.c          # Comprehensive test suite
├── data/
│   └── courses.csv     # Course database (25+ McMaster courses)
├── Makefile            # Build configuration
├── README.md           # This file
└── .gitignore          # Git ignore rules
```

## Requirements

- **Compiler**: GCC (C99 or later)
- **Operating System**: Linux, macOS, or Windows (with MinGW/WSL)
- **Build Tool**: Make

## Installation

### Clone the Repository

```bash
git clone https://github.com/your-username/electible.git
cd electible
```

### Build the Project

```bash
make
```

This will:
1. Create necessary directories (`obj/`, `bin/`)
2. Compile all source files
3. Link the executable
4. Output: `bin/electible`

## Usage

### Running the Application

```bash
make run
```

Or directly:

```bash
./bin/electible
```

### Using a Custom Data File

```bash
./bin/electible path/to/your/courses.csv
```

### Help Information

```bash
./bin/electible --help
```

## Example Workflow

```
=== ELECTIBLE: McMaster First-Year Elective Finder ===

1. Browse All Courses
2. Filter Courses
3. Sort Courses
4. Add New Course (Crowdsource)
5. View Recommendations
6. Help
7. Exit

Enter choice (1-7): 2

=== Filter Courses ===
Subject area (or press Enter to skip): Computer Science
Minimum difficulty (or press Enter to skip): 1
Maximum difficulty (or press Enter to skip): 3

Filtering complete!
Found 1 course(s):

#    Code       Title                                    Diff   Work   Exam   Midterm   Rating
================================================================================
1    CS1MD3     Introduction to Programming              3/5    4/5    Yes    Yes       4.5/5
```

## Data Format

### CSV Structure

The `courses.csv` file follows this format:

```csv
title,course_code,subject_area,difficulty,workload,has_exam,has_midterm,rating,description,year_offered
```

**Example:**

```csv
Introduction to Programming,COMPSCI 1MD3,Computer Science,3,4,1,1,4.5,Learn fundamental programming concepts using Python.,2025
```

### Field Descriptions

| Field | Type | Range | Description |
|-------|------|-------|-------------|
| `title` | String | 1-100 chars | Course title |
| `course_code` | String | 1-10 chars | Official course code |
| `subject_area` | String | 1-50 chars | Subject category |
| `difficulty` | Integer | 1-5 | Difficulty rating |
| `workload` | Integer | 1-5 | Workload rating |
| `has_exam` | Boolean | 0 or 1 | Exam requirement |
| `has_midterm` | Boolean | 0 or 1 | Midterm requirement |
| `rating` | Float | 0.0-5.0 | Overall rating |
| `description` | String | 1-500 chars | Course description |
| `year_offered` | Integer | 2020-2030 | Year offered |

## Testing

### Run All Tests

```bash
make test
```

### Test Coverage

The test suite (`tests/test.c`) includes:

- **Module C Tests**:
  - Course validation (valid/invalid data)
  - CSV parsing (quoted fields, commas)
  - Add course functionality

- **Module A Tests**:
  - Filter by subject (case-insensitive)
  - Filter by difficulty range
  - Filter by exam/midterm presence
  - Multi-criteria filtering

- **Module B Tests**:
  - Sort by difficulty (ascending/descending)
  - Sort by rating (ascending/descending)
  - Stable sort verification

- **Edge Cases**:
  - Empty arrays
  - NULL pointers
  - Invalid inputs
  - No matches found

### Expected Output

```
========================================
  Electible Test Suite
  SE 2XC3 Lab 7.2
========================================

Testing Course Validation:
  ✓ Valid course passes validation
  ✓ Invalid difficulty (6) fails validation
  ✓ Invalid workload (0) fails validation
  ✓ Invalid rating (6.0) fails validation

...

========================================
  Test Summary
========================================
  Total tests:  25
  Passed:       25
  Failed:       0
========================================

✓ All tests passed!
```

## Makefile Targets

| Target | Description |
|--------|-------------|
| `make` or `make all` | Build the project |
| `make run` | Build and run the application |
| `make test` | Build and run the test suite |
| `make clean` | Remove all build artifacts |
| `make rebuild` | Clean and rebuild everything |
| `make help` | Display available targets |

## Modular Design

### Module A: Filtering (Amanda Wu)

**Files**: `src/filter.c`, `include/filter.h`

Provides functions to filter courses based on:
- Subject area (case-insensitive substring matching)
- Difficulty range (min/max)
- Workload range (min/max)
- Exam/midterm presence
- Minimum rating
- Multi-criteria filtering

**Key Functions**:
- `filter_by_subject()`
- `filter_by_difficulty()`
- `filter_by_workload()`
- `apply_multiple_filters()`

### Module B: Sorting (Anshika Patel)

**Files**: `src/sort.c`, `include/sort.h`

Implements **stable merge sort** for:
- Difficulty
- Workload
- Rating
- Course code (alphabetical)
- Title (alphabetical)
- Multi-criteria sorting

**Algorithm**: Merge sort (O(n log n) time complexity, stable)

**Key Functions**:
- `sort_by_difficulty()`
- `sort_by_rating()`
- `sort_multi_criteria()`

### Module C: Data Management (Khushi Ved)

**Files**: `src/data.c`, `include/data.h`

Handles:
- Loading courses from CSV
- Saving courses to CSV
- Adding new courses dynamically
- Course validation
- CSV parsing (handles quoted fields, commas)
- Memory management

**Key Functions**:
- `load_courses()`
- `save_courses()`
- `add_course()`
- `validate_course()`

### Module D: UI & Integration (Yasmine Abdelmalek)

**Files**: `src/ui.c`, `include/ui.h`, `src/main.c`

Provides:
- Interactive command-line menu
- User input handling with validation
- Formatted table display
- Integration of all modules
- Error handling and user feedback

**Key Functions**:
- `display_menu()`
- `display_courses()`
- `get_filter_preferences()`
- `handle_user_interaction()`

## Technical Specifications

### Data Structures

#### Course Structure
```c
typedef struct {
    char title[100];
    char course_code[10];
    char subject_area[50];
    int difficulty;        // 1-5
    int workload;          // 1-5
    int has_exam;          // 0 or 1
    int has_midterm;       // 0 or 1
    float rating;          // 0.0-5.0
    char description[500];
    int year_offered;      // 2020-2030
} Course;
```

### Algorithms

- **Filtering**: Linear scan with predicate matching - O(n)
- **Sorting**: Stable merge sort - O(n log n)
- **CSV Parsing**: State machine with quote handling - O(m) where m = line length

### Memory Management

All dynamically allocated memory is properly managed:
- Filtered results are allocated on heap (caller must free)
- Courses array is dynamically resized when adding courses
- `free_courses()` function provided for cleanup

## Error Handling

The application handles:
- Missing or invalid CSV files
- Malformed CSV data
- Invalid user input (out of range, non-numeric)
- Memory allocation failures
- Empty filter results
- File write errors

## Continuous Integration

GitHub Actions workflow (`.github/workflows/ci.yml`) automatically:
1. Builds the project on push/pull request
2. Runs the test suite
3. Reports build status

## Contributing

This is a team assignment project. Team members should:

1. Create a feature branch for their module
   ```bash
   git checkout -b module-a-filtering
   ```

2. Make changes and commit
   ```bash
   git add .
   git commit -m "Implement filter_by_subject function"
   ```

3. Push to remote
   ```bash
   git push origin module-a-filtering
   ```

4. Create a pull request for review

## Development Workflow

### Incremental Development

Following SE 2XC3 assignment guidelines, this project was developed incrementally:

**Increment 1** (v1.0): Basic data loading and CLI structure
**Increment 2** (v2.0): Filtering and crowdsourcing features
**Final Delivery** (v2.1+): Full sorting, testing, and polish

Each increment is tagged in Git for version tracking.

## Known Limitations

- ANSI color codes may not work on older Windows terminals (can be disabled in `ui.c`)
- Maximum field lengths are fixed (title: 100 chars, description: 500 chars)
- CSV files must use commas as delimiters (no tab support)

## Future Enhancements

- Export filtered results to new CSV
- Integration with McMaster course API
- Graphical user interface (GUI)
- Course comparison mode
- User preferences persistence
- Advanced search with regex support

## License

This project is submitted as academic work for SE 2XC3 at McMaster University.

## Acknowledgments

- Prof. Sam Scott, McMaster University
- SE 2XC3 Teaching Assistants
- McMaster University Engineering Department

## Contact

For questions or issues, please contact:
- Amanda Wu - [email]
- Anshika Patel - [email]
- Khushi Ved - [email]
- Yasmine Abdelmalek - [email]

---

SE 2XC3 Lab 7.2 - Team Assignment
McMaster University, 2025
