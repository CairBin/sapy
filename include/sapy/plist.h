#pragma once
#include "sapy/pmodel.h"
#include "sapy/pcollection_interface.h"
#include "sapy/pstring.h"
#include <algorithm>

namespace sapy{

class PList : public PObject, public PCollectionInterface<PList> {
private:
    template<typename... Args>
    void appendImpl(Args&&... args) {
        (data_.emplace_back(std::forward<Args>(args)), ...);
    }

    void clearImpl(){
        data_.clear();
    }

    template <typename T>
    bool removeImpl(const T &elem){
        auto it = std::find(data_.begin(), data_.end(), elem);
        if(it == data_.end()) return false;

        data_.erase(it);
        return true;
    }

    size_t sizeImpl() const{
        return data_.size(); 
    }


    template <typename T>
    bool containImpl(const T &elem) const{
        auto res = std::find(data_.begin(), data_.end(), elem);
        return res != data_.end();
    }


public:
    PString toString() const;
    PAnyWrapper& operator[](size_t index){
        return data_[index];
    }

    const PAnyWrapper& operator[](size_t index) const{
        return data_[index];
    }
    void appendSingle(const PAnyWrapper& item){
        data_.emplace_back(item);
    }
private:
    virtual void _print(std::ostream& os) const override{
        os << toString();
    }
    std::vector<PAnyWrapper> data_;

    friend class PCollectionInterface<PList>;
};



}