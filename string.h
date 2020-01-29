//lang::CwC
#pragma once
#include <string.h>
#include <stdio.h>
#include "object.h"

/**                                                                              
 * An immutable string class. Values passed in are copied and deleted            
 * upon destruction.                                                             
 * author: aaron                                        
 */         
class String: public Object {
    public:
        char *str_;
        size_t size_;

        String(const char* str) {
            size_ = strlen(str);

            str_ = new char[size_ + 1]; 
            strcpy(str_, str);
        }

        ~String() {
            delete[] str_;
        }

        size_t length() {
            return size_;
        }

        bool equals(Object *other) {
            if (this == other) {
                return true;
            }

            String *other1 = dynamic_cast<String *>(other);
            if (other1 == nullptr) {
                return false;
            }
            return !strcmp(this->str_, other1->str_); // strcmp returns 0 if equal
        }

        // returns a new concatenated string: this + o
        virtual String* concat(String *o) {
            char *t = new char[size_ + o->length()];
            strcpy(t, str_);
            strcat(t, o->str_);
            String *out = new String(t);
            delete[] t;
            return out;
        }

        virtual void print_info() {
            printf("string: %s, size: %lu\n", str_, size_);
        }

        virtual void print() {
            printf("%s", str_);
        }

        /** Returns 0 if strings are equal, >0 if this string is larger,               
         *  <0 otherwise */                      
        // From Professor Vitek                                      
        virtual int compare(String* tgt) { 
            return strcmp(str_, tgt->str_); 
        }

        virtual char* get() {
            return str_;
        }

        // From Professor Vitek
        size_t hash_me_() {                                                            
            size_t hash = 0;                                                             
            for (size_t i = 0; i < size_; ++i) {                                   
                hash = str_[i] + (hash << 6) + (hash << 16) - hash;
            }                   
            return hash;                                                                 
        }                                                                              
};