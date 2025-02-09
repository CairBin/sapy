#pragma once

#include "sapy/collection/pkeyvaluepair.h"
#include "sapy/collection/pcollection_interface.h"
#include "sapy/collection/piterator_interface.h"

namespace sapy{
namespace collection{

template <typename TKey, typename TValue>
class PDictInterface : public PCollectionInterface<PKeyValuePair<TKey, TValue> >, public PIterableInterface<PKeyValuePair<const TKey, TValue>, PKeyValuePair<const TKey, TValue>>{
public:
    /**
     * @description: Adds an element with the provided key and value to the dict.
     * @param key {const TKey&} The object to use as the key of the element to add.
     * @param val {const TValue&} The object to use as the value of the element to add.
     */
    virtual void insert(const TKey& key, const TValue& val);

    /**
     * @description: Determines whether the dict contains an element with the specified key.
     * @param key {const TKey&} The key to locate in the dict.
     * @return true if the dict contains an element with the key; otherwise, false.
     */
    virtual bool containsKey(const TKey& key) const;

    /**
     * @description: Removes the element with the specified key from the dict.
     * @param key {const TKey&} The key of the element to remove.
     * @return true if the element is successfully removed; otherwise, false. This method also returns false if key was not found in the original dict.
     */
    virtual bool remove(const TKey& key);

    /**
     * @description: operator []
     * @param key {const TKey& key} The key of element to access.
     * @return return value reference
     */
    virtual TValue& operator[](const TKey& key);

    /**
     * @description: operator []
     * @param key {const TKey& key} The key of element to access.
     * @return return value const reference
     */
    virtual const TValue& operator[](const TKey& key) const;
};

}
}