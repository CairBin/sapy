#pragma once

#include "sapy/collection/pcollection_interface.h"

namespace sapy{

namespace collection{
/**
 * @description: Provides the base interface for the abstraction of sets.
 * @type_param: {T} The type of elements in the set.
 */
template <typename T>
class PSetInterface : public PCollectionInterface<T>, public PIterableInterface<T, T>{
public:
    /**
     * @description: Adds an element to the current set and returns a value
     *               to indicate if the element was successfully added.
     * @param item {const T&} The element to add to the set
     * @return true if the element is added to the set; false if the element is already in the set.
     */
    virtual bool insert(const T& item);

    /**
     * @description: Removes all elements in the specified collection from the current set.
     * @param other {const PSetInterface<T>&} The collection of items to remove from the set.
     */
    virtual void exceptWith(const PSetInterface<T>& other);

    /**
     * @description: Modifies the current set so that it contains only elements that are also in a specified collection.
     * @param other {const PSetInterface<T>&} The collection to compare to the current set.
     */
    virtual void intersectWith(const PSetInterface<T>& other);

    /**
     * @description: Determines whether the current set is a proper (strict) subset of a specified collection.
     * @param other {const PSetInterface<T>&} The collection to compare to the current set.
     * @return true if the current set is a proper subset of other; otherwise, false.
     */
    virtual bool isProperSubsetOf(const PSetInterface<T>& other) const;

    /**
     * @description: Determines whether the current set is a proper (strict) superset of a specified collection.
     * @param other {const PSetInterface<T>&} The collection to compare to the current set.
     * @return true if the current set is a proper superset of other; otherwise, false.
     */
    virtual bool isProperSupersetOf(const PSetInterface<T>& other) const;

    /**
     * @description: Determines whether a set is a subset of a specified collection.
     * @param other {const PSetInterface<T>&} The collection to compare to the current set.
     * @return true if the current set is a subset of other; otherwise, false.
     */
    virtual bool isSubsetOf(const PSetInterface<T>& other) const;

    /**
     * @description: Determines whether the current set is a superset of a specified collection.
     * @param other {const PSetInterface<T>&} The collection to compare to the current set.
     * @return true if the current set is a superset of other; otherwise, false.
     */
    virtual bool isSupersetOf(const PSetInterface<T>& other) const;

    /**
     * @description: Determines whether the current set overlaps with the specified collection.
     * @param other {const PSetInterface<T>&} The collection to compare to the current set.
     * @return true if the current set and other share at least one common element; otherwise, false.
     */
    virtual bool overlaps(const PSetInterface<T>& other) const;

    /**
     * @description: Determines whether the current set and the specified collection contain the same elements.
     * @param {const PSetInterface<T>&} The collection to compare to the current set.
     * @return true if the current set is equal to other; otherwise, false.
     */
    virtual bool setEquals(const PSetInterface<T>& other) const;

    /**
     * @description: Modifies the current set so that it contains only elements that are present either in the current set or in the specified collection, but not both.
     * @param other {const PSetInterface<T>&} The collection to compare to the current set.
     */
    virtual void symmetricExceptWith(const PSetInterface<T>& other);

    /**
     * @description: Modifies the current set so that it contains all elements that are present in the current set, in the specified collection, or in both.
     * @param other {const PSetInterface<T>&} The collection to compare to the current set.
     */
    virtual void unionWith(const PSetInterface<T>& other);

    virtual ~PSetInterface() = default;
};

}

}