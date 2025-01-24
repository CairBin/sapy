#pragma once
#include "sapy/panywrapper.h"
#include "sapy/pcollection_interface.h"
#include "sapy/piterator.h"
// #include "sapy/pstring.h"
#include <algorithm>

namespace sapy{
class PString;
class PAnyWrapper;
class PList : public PObject, public PCollectionInterface<PList> {
private:
    template<typename... Args>

    void appendImpl(Args&&... args) {
        (data_.emplace_back(std::forward<Args>(args)), ...);
    }

    inline void clearImpl(){
        data_.clear();
    }

    template <typename T>
    inline bool removeImpl(const T &elem){
        auto it = std::find(data_.begin(), data_.end(), elem);
        if(it == data_.end()) return false;

        data_.erase(it);
        return true;
    }

    inline size_t sizeImpl() const{
        return data_.size(); 
    }


    template <typename T>
    inline bool containImpl(const T &elem) const{
        auto res = std::find(data_.begin(), data_.end(), elem);
        return res != data_.end();
    }


public:

    PList() = default;
    PList(std::initializer_list<PAnyWrapper> init) : data_(init){};
    // template <typename... Args>
    // PList(Args&&... args) {
    //     (data_.emplace_back(std::forward<Args>(args)), ...);
    // }

     PString toString() const;

    inline PAnyWrapper& operator[](size_t index){
        return data_[index];
    }

    inline const PAnyWrapper& operator[](size_t index) const{
        return data_[index];
    }
    inline void appendSingle(const PAnyWrapper& item){
        data_.emplace_back(item);
    }

    using iterator = std::vector<PAnyWrapper>::iterator;
    using const_iterator = std::vector<PAnyWrapper>::const_iterator;  
    using value_type = PAnyWrapper;
    inline iterator begin(){
        return iterator(data_.begin());
    }

    inline iterator end(){
        return iterator(data_.end());
    }
    inline const_iterator begin() const{
        return const_iterator(data_.begin());
    }
    inline const_iterator end() const{
        return const_iterator(data_.end());
    }


private:
    virtual void _print(std::ostream& os) const override;
    std::vector<PAnyWrapper> data_;

    friend class PCollectionInterface<PList>;
};



}