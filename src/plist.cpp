#include "sapy/plist.h"
#include "sapy/panywrapper.h"
namespace sapy{

bool PList::operator<(const PList& other) const {
    size_t thisSize = this->count();
    if (thisSize < other.count())
        return true;

    for (size_t i = 0; i < thisSize; ++i)
        if((*this)[i] < other[i])
            return true;

    return false;
}

bool PList::operator==(const PList &other) const{
    if (this->count() != other.count())
        return false;

    for (size_t i = 0; i < other.count(); i++){
        if ((*this)[i] != other[i])
            return false;
    }

    return true;
}

void PList::_print(std::ostream& os) const{
    os << toString();
}

PString PList::toString() const {
    PString result = "[";

    for(size_t i = 0; i < count(); ++i){
        if ((*this)[i].isString()){
            result += "\"";
            result += (*this)[i].toString();
            result += "\"";
            continue;
        }else{
            result += (*this)[i].toString();
        }

        if (i + 1 < count()){
            result += ", ";
        }
    }

    result += "]";
    return result;
}

void PList::sort(
    std::function<PAnyWrapper(const PAnyWrapper &)> key,
    bool reverse)
{
    if (key && !reverse)
    {
        collection::PSorter<PAnyWrapper> sorter([key](const PAnyWrapper &a, const PAnyWrapper &b) -> bool
                                                { return key(a) < key(b); });

        sorter.sort(begin(), end());
        return;
    }

    if (key && reverse)
    {
        collection::PSorter<PAnyWrapper> sorter([key](const PAnyWrapper &a, const PAnyWrapper &b) -> bool
                                                { return key(a) > key(b); });

        sorter.sort(begin(), end());
        return;
    }

    if (!key && !reverse)
    {
        collection::PSorter<PAnyWrapper> sorter;
        sorter.sort(begin(), end());
    }

    if (!key && reverse)
    {
        collection::PSorter<PAnyWrapper> sorter([](const PAnyWrapper &a, const PAnyWrapper &b) -> bool
                                                { return a > b; });
        sorter.sort(begin(), end());
    }
}

}
