#pragma once 

#include "sapy/pobject.h"
#include "sapy/pcollection_interface.h"
#include "sapy/pstring.h"
#include "sapy/panywrapper.h"
#include <unordered_map>
#include "sapy/putility.h"
#include "sapy/piterator.h"

namespace sapy{

class PAnyWrapper;

class PDict : public PObject, public PCollectionInterface<PDict>{
private:
    friend class PCollectionInterface<PDict>;

/*****************Implement PCollectionInterface methods*******************/
private:
    template <typename... Args>
    inline void appendImpl(Args &&...args){
        (container_.emplace(std::forward<Args>(args)), ...);
    }

    inline void clearImpl(){
        container_.clear();
    }

    template <typename T>
    inline bool removeImpl(const T &elem){
        auto it = std::find(container_.begin(), container_.end(), elem);
        if (it == container_.end())
            return false;

        container_.erase(it);
        return true;
    }

    inline size_t sizeImpl(){
        return container_.size();
    }

    template <typename T>
    inline bool containImpl(const T &elem) const{
        auto res = std::find(container_.begin(), container_.end(), elem);
        return res != container_.end();
    }
    struct HashFunc {
        size_t operator()(const PAnyWrapper &obj) const;
    };
public:
    virtual PString toString() const override;
    PAnyWrapper& operator[](const PAnyWrapper& key);
    const PAnyWrapper& operator[](const PAnyWrapper& key) const;
    
    
    using iterator = std::unordered_map<PAnyWrapper, PAnyWrapper, HashFunc>::iterator;
    using const_iterator = std::unordered_map<PAnyWrapper, PAnyWrapper, HashFunc>::const_iterator;  
    using value_type = std::pair<PAnyWrapper, PAnyWrapper>;
    inline iterator begin(){
        return iterator(container_.begin());
    }

    inline iterator end(){
        return iterator(container_.end());
    }
    inline const_iterator begin() const{
        return const_iterator(container_.begin());
    }
    inline const_iterator end() const{
        return const_iterator(container_.end());
    }

private:
    
    virtual void _print(std::ostream &os) const override;
    std::unordered_map<PAnyWrapper, PAnyWrapper, HashFunc> container_;
};

}