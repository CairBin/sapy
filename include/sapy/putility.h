#pragma once
#include "sapy/pobject.h"
#include "sapy/pstring.h"
#include "sapy/plist.h"
#include "sapy/pconnection.h"

namespace sapy{

// Determine whether it is the same object (rather than value)
bool is(const PObject &a, const PObject &b);

// hash function
size_t hash(const PObject& obj);

size_t len(const PString &str);


size_t len(const PConnection& container);


class PRange: public PObject{
public:
    PRange(int start, int end, int step = 1)
        : start_(start), end_(end), step_(step) {
        if (step == 0) {
            throw std::invalid_argument("Step cannot be zero");
        }
    }

    class Iterator {
    public:
        Iterator(int current, int step) : current_(current), step_(step) {}

        int operator*() const {
            return current_;
        }

        Iterator& operator++() {
            current_ += step_;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            if (step_ > 0) {
                return current_ < other.current_;
            }
            return current_ > other.current_;
        }

    private:
        int current_;
        int step_;
    };

    Iterator begin() const {
        return Iterator(start_, step_);
    }

    Iterator end() const {
        if (step_ > 0) {
            return Iterator(end_, step_);
        } else {
            return Iterator(end_, step_);
        }
    }
    virtual PString toString() const override{
        if(step_ == 1){
            return PString("range(") + PString(std::to_string(start_)) + ", " + PString(std::to_string(end_)) + ")";
        }
        return PString("range(") + PString(std::to_string(start_)) + ", " + 
            PString(std::to_string(end_)) + ", " + PString(std::to_string(step_)) + ")";
    }
private:
    int start_;
    int end_;
    int step_;
    virtual void _print(std::ostream& os) const override{
        os << toString();
    }
};


PRange range(int end);
PRange range(int start, int end, int step=1);


}