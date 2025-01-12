#include "sapy/pobject.h"
#include "sapy/pstring.h"
#include <vector>
#include <memory>

namespace sapy{

class PList : public PObject{
public:
    PList() = default;
    
    // Delete copy constructor and copy assignment operator
    PList(const PList&) {
        throw std::runtime_error("Copy constructor not allowed");
    };
    PList& operator=(const PList&) = delete;
    
    // Allow move semantics
    PList(PList&&) noexcept = default;
    PList& operator=(PList&&) noexcept = default;


    PString toString() const override;

    PList* _clone() const override {
        return new PList(*this);
    }
    void append(const PObject& obj) {
        std::unique_ptr<PObject> ptr(obj._clone());
        _data.push_back(std::move(ptr));
    }
    PObject& at(size_t index){
        return *_data.at(index);
    }

    size_t size() const{
        return _data.size();
    }
    size_t len() const{
        return size();
    }
    PObject& operator[](size_t index){
        return at(index);
    }
    

    
private:
    virtual void _print(std::ostream& os) const override{
        os << toString().toStdString();
    }
    std::vector<std::unique_ptr<PObject>>_data;
};

}