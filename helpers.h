// lang::CwC

#pragma once

#include <stdlib.h>
#include <stdio.h>

void affirm(bool test, const char* msg) {
    if (!(test)){ 
        fprintf(stderr, "%s\n", msg); 
        abort(); 
    }
}

void check_in_bounds(int argc, int index, int arguments) {
    affirm((index + arguments < argc), "Missing argument");
}

unsigned int check_positive(int i) {
    affirm((i >= 0), "Only positive integers allowed");
    return i;
}

bool is_int(char *c) {
    if (*c == '\0') {
        return false;
    }
    for (int i = 0; c[i] != '\0'; i++) {
        if (i == 0 && (c[i] == '+' || c[i] == '-')) {
            continue;
        } else if (!isdigit(c[i])) {
            return false;
        }
    }
    return true;
}

bool is_float(char *c) {
    if (*c == '\0') {
        return false;
    }
    bool has_decimal = false;
    for (int i = 0; c[i] != '\0'; i++) {
        if (i == 0 && (c[i] == '+' || c[i] == '-')) {
            continue;
        } else if (c[i] == '.' && has_decimal) {
            return false;
        } else if (c[i] == '.') {
            has_decimal = true;
        } else if (!isdigit(c[i])) {
            return false;
        }
    }
    return true;
}