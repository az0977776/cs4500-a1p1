//lang::CwC
#pragma once
#include <stdlib.h>

// represents an object
class Object {
    public:
        size_t hash_;

        Object() {
            hash_ = 0;
        }

        virtual ~Object() { }

        virtual bool equals(Object *other) {
            return this == other;
        }

        // hash with caching, no need to recalculate
        size_t hash() {
            if (hash_ == 0) { 
                hash_ = hash_me(); 
            }
            return hash_;
        }

        virtual size_t hash_me() {
            return reinterpret_cast<size_t>(this);
        }
};