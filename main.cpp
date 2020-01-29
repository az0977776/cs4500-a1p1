//lang::CwC
#include <stdlib.h> 
#include <stdio.h>      /* files */
#include <string.h>     /* strcmp */

#include "sorer.h"
#include "column.h"
#include "helpers.h"

int main(int argc, char** argv) {

    // have these flags appeared
    bool a_file, a_from, a_len;
    a_file = a_from = a_len = false;
    int a_type, a_print, a_missing;
    a_type = a_print = a_missing = 0;
    char *file_name;
    unsigned int from, len;
    unsigned int col_arg1, col_arg2;

    // if user passes in non integers for places where there should be integers
    // just default the value to 0
    int index = 1; // skipping the first argument
    while (index < argc) {
        if (strcmp(argv[index], "-f") == 0) {
            check_in_bounds(argc, index, 1);
            file_name = argv[index + 1];
            a_file = true;
            index+=2;
        }
        else if (strcmp(argv[index], "-from") == 0) {
            check_in_bounds(argc, index, 1);
            from = check_positive(atoi(argv[index + 1]));
            a_from = true;
            index+=2;
        }
        else if (strcmp(argv[index], "-len") == 0) {
            check_in_bounds(argc, index, 1);
            len = check_positive(atoi(argv[index + 1]));
            a_len = true;
            index+=2;
        }
        else if (strcmp(argv[index], "-print_col_type") == 0) {
            check_in_bounds(argc, index, 1);
            col_arg1 = check_positive(atoi(argv[index + 1]));
            a_type = 1;
            index+=2;
        }
        else if (strcmp(argv[index], "-print_col_idx") == 0) {
            check_in_bounds(argc, index, 2);
            col_arg1 = check_positive(atoi(argv[index + 1]));
            col_arg2 = check_positive(atoi(argv[index + 2]));
            a_print = 1;
            index+=3;
        }
        else if (strcmp(argv[index], "-is_missing_idx") == 0) {
            check_in_bounds(argc, index, 2);
            col_arg1 = check_positive(atoi(argv[index + 1]));
            col_arg2 = check_positive(atoi(argv[index + 2]));
            a_missing = 1;
            index+=3;
        }
        else {
            affirm(false, "Invalid input argument");
        }
    }

    affirm(a_file, "Missing file");
    affirm(a_from, "Missing from");
    affirm(a_len, "Missing length");
    affirm((a_type + a_print + a_missing == 1), "Needs one of the following commands: -print_col_type, -is_missing_idx, -print_col_idx\n");

    // opening the file
    FILE *f = fopen(file_name, "r");
    affirm(f != NULL, "File is null pointer");

    SOR* reader = new SOR();
    reader->read(f, from, len);

    if (a_type) {
        switch (reader->get_col_type(col_arg1)) {
            case type_string:
                printf("STRING\n");
                break;
            case type_float:
                printf("FLOAT\n");
                break;
            case type_int:
                printf("INT\n");
                break;
            case type_bool:
                printf("BOOL\n");
                break;
            default:
                printf("Index out of bounds.\n");
                break;
        }

    } else if (a_print) {
        char* temp = reader->get_value(col_arg1, col_arg2);
        if (temp != nullptr) {
            printf("%s\n", temp);
        } 
    } else if (a_missing) {
        printf("%d\n", reader->is_missing(col_arg1, col_arg2));
    }

    delete reader;
    fclose(f);
    return 0;
}
