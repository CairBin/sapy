#include "sapy/pset.h"


namespace sapy {

size_t PSet::hash() const {
    size_t result = 0;
    for (auto it = cbegin(); it != cend(); ++it) {
        result ^= it->hash();
    }
    return result;
}



PString PSet::toString() const {
    if(this->count() == 0)
        return "set()";

    PString result = "{";
    for (auto it = cbegin(); it != cend(); ++it) {
        result += (it->isString()?  "\"" + it->toString() + "\"" : it->toString());
        if (it+1 != cend()) {
            result += ", ";
        }
    }
    result += "}";
    return result;
}

void PSet::_print(std::ostream& os) const {
    os << toString();
}


PSet PSet::copy() const {
    PSet result;
    for (auto it = cbegin(); it != cend(); ++it) {
        result.add(*it);
    }
    return result;
}

PSet PSet::difference(const PSet& other) const {
    PSet result(*this);
    result.exceptWith(other);
    return result;
}

void PSet::difference_update(const PSet& other) {
    this->exceptWith(other);
}

void PSet::discard(const PAnyWrapper& elem) {
    this->remove(elem);
}

PSet PSet::intersection(const PSet& other) const {
    PSet result(*this);
    result.intersectWith(other);
    return result;
}

void PSet::intersection_update(const PSet& other) {
    this->intersectWith(other);
}

bool PSet::isdisjoint(const PSet& other) const {
    return this->overlaps(other);
}


bool PSet::issubset(const PSet& other) const {
    return this->isSubsetOf(other);
}

bool PSet::issuperset(const PSet& other) const {
    return this->isSupersetOf(other);
}

PSet PSet::union_(const PSet& other) const {
    PSet result = copy();
    for (auto it = other.cbegin(); it != other.cend(); ++it) {
        result.add(*it);
    }
    return result;
}

PAnyWrapper PSet::pop() {
    if (this->count() == 0) {
        throw std::out_of_range("pop from an empty set");
    }
    auto it = begin();
    PAnyWrapper result = *it;
    this->remove(*it);
    return result;
}

PSet PSet::symmetric_difference(const PSet& other) const {
    PSet result(*this);
    result.symmetricExceptWith(other);
    return result;
}

void PSet::symmetric_difference_update(const PSet& other) {
    this->symmetricExceptWith(other);
}

void PSet::update(const PSet& other) {
    this->unionWith(other);
}

PSet PSet::operator-(const PSet& other) const {
    return difference(other);
}

PSet PSet::operator-(const PAnyWrapper& other) const {
    PSet result = copy();
    result.discard(other);
    return result;
}

bool PSet::operator==(const PSet& other) const {
    if (count() != other.count()) {
        return false;
    }
    for (auto it = cbegin(); it != cend(); ++it) {
        if (!other.contains(*it)) {
            return false;
        }
    }
    return true;
}

}