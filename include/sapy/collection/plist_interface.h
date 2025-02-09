#pragma once
#include "sapy/collection/pcollection_interface.h"
#include "sapy/collection/piterator_interface.h"
namespace sapy{

namespace collection{

/**
 * @description: Represents a collection of objects that can be individually accessed by index.
 * @type_param: {T} The type of elements in the list.
 */
template <typename T>
class PListInterface : virtual public PCollectionInterface<T>,public PIterableInterface<T, T>, public PReverseIterableInterface<T, T>{
public:
    /**
     * @description: Determines the index of a specific item in the list
     * @param item {const T&} The object to locate in the list
     * @return The index of item if found in the list; otherwise, -1.
     */
    virtual int indexOf(const T& item) const;

    /**
     * @description: Inserts an item to the list at the specified index.
     * @param index {size_t} The zero-based index at which item should be inserted.
     * @param item {const T&} The object to insert into the list.
     */
    virtual void insert(size_t index, const T& item);

    /**
     * @description: Removes the list item at the specified index.
     * @param index {size_t} The zero-based index of the item to remove.
     */
    virtual void removeAt(size_t index);

    /**
     * @description: Operator []
     * @param index {size_t} The zero-based index of the item to access.
     * @return Gets the element reference
     */
    virtual T& operator[](size_t index);

    /**
     * @description: Operator []
     * @param index {size_t} The zero-based index of the item to access.
     * @return Gets the element const reference.
     */
    virtual const T &operator[](size_t index) const;

    virtual ~PListInterface() = default;
};

}

}