#pragma

#include "sapy/pobject.h"
#include "sapy/pcollection_interface.h"
#include "sapy/pstring.h"
#include "sapy/pmodel.h"
#include <unordered_map>
#include "sapy/putility.h"

namespace sapy{

class PDict : public PObject, public PCollectionInterface<PDict>{
private:
    friend class PCollectionInterface<PDict>;

/*****************Implement PCollectionInterface methods*******************/
private:
    template <typename... Args>
    void appendImpl(Args &&...args){
        (container_.emplace(std::forward<Args>(args)), ...);
    }

    void clearImpl(){
        container_.clear();
    }

    template <typename T>
    bool removeImpl(const T &elem){
        auto it = std::find(container_.begin(), container_.end(), elem);
        if (it == container_.end())
            return false;

        container_.erase(it);
        return true;
    }

    size_t sizeImpl(){
        return container_.size();
    }

    template <typename T>
    bool containImpl(const T &elem) const{
        auto res = std::find(container_.begin(), container_.end(), elem);
        return res != container_.end();
    }

private:
    typedef struct HashFunc{
        size_t operator()(const PAnyWrapper &obj) const {
            return obj.hash();
        }
    } HashFunc;

    std::unordered_map<PAnyWrapper, PAnyWrapper, HashFunc> container_;
};

}