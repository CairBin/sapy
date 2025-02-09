#pragma once

#include <cstddef>
#include "sapy/collection/piterator_interface.h"
namespace sapy{

namespace collection{

/**
 * @description: Defines methods to manipulate generic collections.
 * @type_param: {T} The type of the elements in the collection.
 */
template <typename T>
class PCollectionInterface{
public:
    /**
     * @description: Gets the number of elements contained in the collection.
     * @return The number of elements contained in the collection.
     */
    virtual size_t count() const = 0;

    /**
     * @description: Adds an item to the collection.
     * @param item {const T&} The object to add to the collection.
     */
    virtual void add(const T& item) = 0;

    /**
     * @description: Removes all items from the collection.
     */
    virtual void clear() = 0;

    /**
     * @description: Determines whether the collection contains a specific value.
     * @param item {const T&} The object to locate in the collection.
     * @return true if item is found in the collection; otherwise, false.
     */
    virtual bool contains(const T& item) const = 0;

    /**
     * @description: Removes the first occurrence of a specific object from the collection.
     * @param item {const T&} removed item
     * @return true if item was successfully removed from the collection; otherwise, false. This method also returns false if item is not found in the original collection.
     */
    virtual bool remove(const T& item) = 0;
};

}


}