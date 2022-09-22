//
// Created by max on 22/09/22.
//

// NOTE(Max): I am adding this, so you can see that I had to make a bunch of
// tests.
//#define TESTS_ON

#include <stdio.h>
#include <memory.h>

static const size_t MARGIN = 1;



static void find_column_widths(
        size_t num_headers,
        size_t num_entries,
        char *headers[num_headers],
        char *data[num_entries][num_headers],
        size_t column_widths[num_headers]
) {
    // Init the array to the width of the headers.
    for (int i = 0; i < num_headers; i++) {
        column_widths[i] = strlen(headers[i]);
    }

    // Find the width of each data entry.
    for (int header_index = 0; header_index < num_headers; header_index++) {
        size_t max_width = column_widths[header_index];
        for (int entry_index = 0; entry_index < num_entries; entry_index++) {
            size_t value_len = strlen(data[entry_index][header_index]);
            if (max_width < value_len) {
                max_width = value_len;
            }
        }
        column_widths[header_index] = max_width;
    }

#ifdef false
    // This is slower than the above because it may do multiple writes to an
    // address with `column_widths[header_index] = value_len` where as the fast
    // version will only ever make one per `header_index`. (Noted by Julian, ty)
    for (int entry_index = 0; entry_index < num_entries; entry_index++) {
        for (int header_index = 0; header_index < num_headers; header_index++) {
            size_t value_len = strlen(data[entry_index][header_index]);
            if (column_widths[header_index] < value_len) {
                column_widths[header_index] = value_len;
            }
        }
    }
#endif

#ifdef TESTS_ON
    printf("Column widths: ");
    for (int i = 0; i < num_headers; i++) {
        printf("%zu, ", column_widths[i]);
    }
    printf("\n");
#endif
}


/** Print `charter` `reputations` times. */
static void repeat(char charter, size_t reputations) {
    for (int i = 0; i < reputations; i++) {
        printf("%c", charter);
    }
}


/** Prints the full horizontal lines. */
static void print_line(size_t num_headers, size_t column_widths[num_headers]) {
    printf("+");
    for (int i = 0; i < num_headers; i++) {
        repeat('-', column_widths[i] + (2 * MARGIN));
        printf("+");
    }
    printf("\n");
}


/** Prints a row. A row can be either the headers or a entry from `data`. */
static void print_row(
        size_t num_items,
        char *row[num_items],
        const size_t column_widths[num_items]
) {
    printf("|");
    for (int i = 0; i < num_items; ++i) {
        repeat(' ', MARGIN);
        printf("%s", row[i]);
        size_t remaining_space = column_widths[i] - strlen(row[i]);
        repeat(' ', remaining_space + MARGIN);
        printf("|");
    }
    printf("\n");
}


static void print_header(
        size_t num_headers,
        char *headers[num_headers],
        const size_t column_widths[num_headers]
) {
    print_row(num_headers, headers, column_widths);
}


static void print_data(
        size_t num_headers,
        size_t num_entries,
        char *data[num_entries][num_headers],
        const size_t column_widths[num_headers]
) {
    for (int i = 0; i < num_entries; i++) {
        print_row(num_headers, data[i], column_widths);
    }
}


/**
 * This function will pretty print a table of data.     <br><br>
 *
 * Example:
 * <pre>
 *  +-------+----------+---------+                      <br>
 *  | Name  | Language | OS      |                      <br>
 *  +-------+----------+---------+                      <br>
 *  | Max   | Java     | Windows |                      <br>
 *  | Adam  | C++      | Linux   |                      <br>
 *  | James | Python   | Windows |                      <br>
 *  | Josh  | Python   | Linux   |                      <br>
 *  +-------+----------+---------+
 *  <\pre>
 */
void prettyPrint(
        size_t num_headers,
        size_t num_entries,
        char *headers[num_headers],
        char *data[num_entries][num_headers]
) {
    size_t column_widths[num_headers];
    find_column_widths(num_headers, num_entries, headers, data, column_widths);

    print_line(num_headers, column_widths);
    print_header(num_headers, headers, column_widths);
    print_line(num_headers, column_widths);
    print_data(num_headers, num_entries, data, column_widths);
    print_line(num_headers, column_widths);
}


int main () {
    char *headers[3] = {"Name", "Language", "OS"};
    char *data[4][3] = {
            {"Max", "Java", "Windows"},
            {"Adam", "C++", "Linux"},
            {"James", "Python", "Windows"},
            {"Josh", "Python", "Linux"}
    };

    prettyPrint(
            sizeof(headers) / sizeof(*headers),
            sizeof(data) / sizeof(*data),
            headers,
            data
    );


#ifdef TESTS_ON
    repeat('?', 5);
    printf("\n");
#endif
}
