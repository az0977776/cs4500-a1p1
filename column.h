//lang:CwC
#pragma once
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "string.h"
#include "sorer.h"
#include "helpers.h"

enum ColumnType {
    type_unknown = -1,
    type_bool = 0,
    type_int = 1,
    type_float = 2,
    type_string = 3,
};

// returns the inferred typing of the char*
ColumnType infer_type(char *c) {
    // missing values
    if (c == nullptr) {
        return type_bool;
    }
    // check boolean
    if (strlen(c) == 1) {
        if ((*c == '0') || (*c == '1')) {
            return type_bool;
        }
    }
    // check int
    if (is_int(c)) {
        return type_int;
    }
    // check float
    if (is_float(c)) {
        return type_float;
    }
    return type_string;
}

// represents a column on the SoR
// the elements in a Column should be of the same type
class Column {
    public: 
        size_t len_;
        size_t cap_;
        Column() {
            len_ = 0;
            cap_ = 16;
        }
        virtual ~Column() {}

        virtual void add_nullptr() {}

        virtual void add(String *s) {}

        virtual void add(float *f) {}

        virtual void add(int *i) {}

        virtual void add(bool *b) {}

        virtual void add(char *c) {}

        // checks if the value represented by the char* can be added to this column
        virtual bool can_add(char *c) {
            if (c == nullptr || *c == '\0') {
                return true;
            }
            return infer_type(c) <= get_type();
        }

        // returns a pointer to the object at the ith index
        virtual void* get(size_t i) {
            return nullptr;
        }

        // returns the string representation of the object at the ith index
        virtual char* get_char(size_t i) {
            return nullptr;
        }

        /** Gets the type of this column
         */ 
        virtual ColumnType get_type() {
            return type_unknown;
        }
};

/**
 * Representation of a column of strings
 * owns the strings in the list, deletes strings upon deletion
 */ 
class ColumnString : public Column {
    public:
        String **values_; 
        ColumnString() : Column() {
            values_ = new String*[cap_];
        }
        ~ColumnString() {
            for (size_t i = 0; i < len_; i++) {
                delete values_[i];
            }
            delete[] values_;
        }

        ColumnType get_type() {
            return type_string;
        }

        // checks if the underlying array needs to be reallocated
        // does so if true
        void check_reallocate() {
            if (len_ >= cap_) {
                cap_*=2;
                String **temp = new String*[cap_];
                for (size_t i = 0; i < len_; i++) {
                    temp[i] = values_[i];
                }
                delete[] values_;
                values_ = temp;
            }
        }

        void add_nullptr() {
            check_reallocate();
            values_[len_] = nullptr;
            len_++;
        }

        // adds the string
        void add(String *s) {
            check_reallocate();
            values_[len_] = s;
            len_++;
        }

        void add(char *c) {
            if (c == nullptr) {
                add_nullptr();
            }
            add(new String(c));
        }

        void* get(size_t i) {
            if (i >= len_) {
                return nullptr;
            }
            return values_[i];
        }

        // returns the string representation of the element at the ith index
        char* get_char(size_t i) {
            if (i >= len_ || values_[i] == nullptr) {
                return nullptr;
            }
            size_t str_len = values_[i]->length();
            char* ret = new char[str_len + 3];
            ret[0] = '"';
            for (size_t j = 0; j < str_len; j++) {
                ret[j + 1] = values_[i]->get()[j];
            }
            ret[str_len + 1] = '"';
            ret[str_len + 2] = '\0';
            return ret;
        }
}; 

/**
 * Representation of a column of floats
 * 
 */ 
class ColumnFloat : public Column {
    public:
        float **values_; 
        ColumnFloat() : Column() {
            values_ = new float*[cap_];
        }
        ~ColumnFloat() {
            for (size_t i = 0; i < len_; i++) {
                delete values_[i];
            }
            delete[] values_;
        }

        ColumnType get_type() {
            return type_float;
        }

        // checks if the underlying array needs to be reallocated
        // does so if true
        void check_reallocate() {
            if (len_ >= cap_) {
                cap_*=2;
                float **temp = new float*[cap_];
                for (size_t i = 0; i < len_; i++) {
                    temp[i] = values_[i];
                }
                delete[] values_;
                values_ = temp;
            }
        }

        void add_nullptr() {
            check_reallocate();
            values_[len_] = nullptr;
            len_++;
        }

        // adds a float
        void add(float *f) {
            check_reallocate();
            values_[len_] = f;
            len_++;
        }

        void add(char *c) {
            if (c == nullptr) {
                add_nullptr();
            }
            float *f = new float(atof(c));
            add(f);
        }

        void* get(size_t i) {
            if (i >= len_) {
                return nullptr;
            }
            return values_[i];
        }
        
        // get string rep of element at ith index
        char* get_char(size_t i) {
            if (i >= len_ || values_[i] == nullptr) {
                return nullptr;
            }
            char* ret = new char[512];
            sprintf(ret, "%f", *values_[i]);
            return ret;
        }
};

// represents column of ints
class ColumnInt : public Column {
    public:
        int **values_; 
        ColumnInt() : Column() {
            values_ = new int*[cap_];
        }
        ~ColumnInt() {
            for (size_t i = 0; i < len_; i++) {
                delete values_[i];
            }
            delete[] values_;
        }

        ColumnType get_type() {
            return type_int;
        }

        // checks if the underlying array needs to be reallocated
        // does so if true
        void check_reallocate() {
            if (len_ >= cap_) {
                cap_*=2;
                int **temp = new int*[cap_];
                for (size_t i = 0; i < len_; i++) {
                    temp[i] = values_[i];
                }
                delete[] values_;
                values_ = temp;
            }
        }

        void add_nullptr() {
            check_reallocate();
            values_[len_] = nullptr;
            len_++;
        }

        // adds an int
        void add(int *i) {
            check_reallocate();
            values_[len_] = i;
            len_++;
        }

        void add(char *c) {
            if (c == nullptr) {
                add_nullptr();
            }
            int *i = new int(atoi(c));
            add(i);
        }

        void* get(size_t i) {
            if (i >= len_) {
                return nullptr;
            }
            return values_[i];
        }

        // gets the string representation of the ith element
        char* get_char(size_t i) {
            if (i >= len_ || values_[i] == nullptr) {
                return nullptr;
            }
            char* ret = new char[512];
            sprintf(ret, "%d", *values_[i]);
            return ret;
        }
};

// represents a column of bools
class ColumnBool : public Column {
    public:
        bool **values_; 
        ColumnBool() : Column() {
            values_ = new bool*[cap_];
        }
        ~ColumnBool() {
            for (size_t i = 0; i < len_; i++) {
                delete values_[i];
            }
            delete[] values_;
        }

        ColumnType get_type() {
            return type_bool;
        }

        // reallocates if need be
        void check_reallocate() {
            if (len_ >= cap_) {
                cap_*=2;
                bool **temp = new bool*[cap_];
                for (size_t i = 0; i < len_; i++) {
                    temp[i] = values_[i];
                }
                delete[] values_;
                values_ = temp;
            }
        }

        void add_nullptr() {
            check_reallocate();
            values_[len_] = nullptr;
            len_++;
        }

        // adds a bool
        void add(bool *b) {
            check_reallocate();
            values_[len_] = b;
            len_++;
        }

        void add(char *c) {
            if (c == nullptr) {
                add_nullptr();
            }
            bool *b;
            if (*c == '0') {
                b = new bool(false);
            } else {
                b = new bool(true);
            }
            add(b);
        }

        void* get(size_t i) {
            if (i >= len_) {
                return nullptr;
            }
            return values_[i];
        }

        // get str representation of ith element
        char* get_char(size_t i) {
            if (i >= len_ || values_[i] == nullptr) {
                return nullptr;
            }
            char* ret = new char[512];
            sprintf(ret, "%d", *values_[i]);
            return ret;
        }
};