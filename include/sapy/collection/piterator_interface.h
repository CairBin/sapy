#pragma once

namespace sapy{

namespace collection{
template <typename T>
class PIteratorInterface{
public:
    // 兼容STL(algorithm函数等)
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::forward_iterator_tag;

public:
    virtual T& operator*();
    virtual const T& operator*() const;
    virtual PIteratorInterface<T> &operator++();
    virtual PIteratorInterface<T> operator+(size_t offset);
    virtual PIteratorInterface<T> operator++(int x);


    virtual bool operator!=(const PIteratorInterface<T>& other) const;
    virtual bool operator==(const PIteratorInterface<T> &other) const;
    virtual T* operator->();
    virtual const T* operator->() const;
    virtual bool operator<(const PIteratorInterface<T>& other) const;
    virtual bool operator<=(const PIteratorInterface<T> &other) const;
    virtual bool operator>(const PIteratorInterface<T> &other) const;
    virtual bool operator>=(const PIteratorInterface<T> &other) const;
};

template <typename T>
class PConstIteratorInterface{
public:
    using value_type = const T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T *;
    using reference = const T &;
    using iterator_category = std::forward_iterator_tag;

public:
    virtual const T &operator*() const;
    virtual PConstIteratorInterface<T> &operator++();
    virtual PConstIteratorInterface<T> operator+(size_t offset);
    virtual PConstIteratorInterface<T> operator++(int x);

    virtual bool operator!=(const PConstIteratorInterface<T> &other) const;
    virtual bool operator==(const PConstIteratorInterface<T> &other) const;

    virtual const T *operator->() const;
    virtual bool operator<(const PConstIteratorInterface<T> &other) const;
    virtual bool operator<=(const PConstIteratorInterface<T> &other) const;
    virtual bool operator>(const PConstIteratorInterface<T> &other) const;
    virtual bool operator>=(const PConstIteratorInterface<T> &other) const;
};

template <typename T>
class PReverseIteratorInterface{
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::forward_iterator_tag;

public:
    virtual T& operator*();
    virtual const T& operator*() const;
    virtual PReverseIteratorInterface<T>& operator++();
    virtual PReverseIteratorInterface<T> operator+(size_t offset);
    virtual PReverseIteratorInterface<T> operator++(int x);

    virtual bool operator!=(const PReverseIteratorInterface<T>& other) const;
    virtual bool operator==(const PReverseIteratorInterface<T> &other) const;
    virtual T* operator->();
    virtual const T* operator->() const;
    virtual bool operator<(const PReverseIteratorInterface<T>& other) const;
    virtual bool operator<=(const PReverseIteratorInterface<T> &other) const;
    virtual bool operator>(const PReverseIteratorInterface<T> &other) const;
    virtual bool operator>=(const PReverseIteratorInterface<T> &other) const;
};

template <typename T>
class PConstReverseIteratorInterface{
public:
    using value_type = const T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T *;
    using reference = const T &;
    using iterator_category = std::forward_iterator_tag;

public:

    virtual const T &operator*() const;
    virtual PConstReverseIteratorInterface<T> &operator++();
    virtual PConstReverseIteratorInterface<T> operator+(size_t offset);
    virtual PConstReverseIteratorInterface<T> operator++(int x);

    virtual bool operator!=(const PConstReverseIteratorInterface<T> &other) const;
    virtual bool operator==(const PConstReverseIteratorInterface<T> &other) const;

    virtual const T *operator->() const;
    virtual bool operator<(const PConstReverseIteratorInterface<T> &other) const;
    virtual bool operator<=(const PConstReverseIteratorInterface<T> &other) const;
    virtual bool operator>(const PConstReverseIteratorInterface<T> &other) const;
    virtual bool operator>=(const PConstReverseIteratorInterface<T> &other) const;
};

template<typename T, typename U> 
class PIterableInterface{
public:
    virtual PIteratorInterface<T> begin();
    virtual PIteratorInterface<T> end();

    virtual PConstIteratorInterface<U> cbegin() const;
    virtual PConstIteratorInterface<U> cend() const;

};

template <typename T, typename U>
class PReverseIterableInterface{
public:
    virtual PReverseIteratorInterface<T> rbegin();
    virtual PReverseIteratorInterface<T> rend();

    virtual PConstReverseIteratorInterface<U> crbegin() const;
    virtual PConstReverseIteratorInterface<U> crend() const;
};


template <typename StlIterType, typename IteratorInterface ,typename T>
class FromStlIteratorBaseTemplate : public IteratorInterface{
public:
    FromStlIteratorBaseTemplate(StlIterType iter)
        : iter_(iter) {}
    
    T& operator*() override{
        return *iter_;
    }

    const T& operator*() const override{
        return *iter_;
    }

    IteratorInterface& operator++() override{
        ++iter_;
        return *this;
    }

    IteratorInterface operator+(size_t offset) override{
        auto cp_iter = iter_;
        for(size_t i = 0; i < offset; i++){
            ++cp_iter;
        }
        return FromStlIteratorBaseTemplate(cp_iter);
    }

    IteratorInterface operator++(int x) override{
        FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T> temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const IteratorInterface& other) const override{
        const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T> *p = dynamic_cast < const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T>*>(&other);
        if (!p)
            throw std::runtime_error("Error: type error.");
        return iter_ == p->iter_;
    }

    bool operator!=(const IteratorInterface& other) const override{
        const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T> *p = dynamic_cast<const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T> *>(&other);
        if (!p)
            throw std::runtime_error("Error: type error.");
        return iter_ != p->iter_;
    }

    T *operator->() override
    {
        return &(*iter_);
    }

    const T* operator->() const override{
        return &(*iter_);
    }

    // bool operator<(const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T>& other) const {
    //     return iter_ < other.iter_;
    // }

    // bool operator<(const IteratorInterface& other) const override {
    //     const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T> *p = dynamic_cast<const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T> *>(&other);
    //     if (!p)
    //         throw std::runtime_error("Error: type error.");
    //     return iter_ < p->iter_;
    // }

    // bool operator<=(const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T>& other) const {
    //     return iter_ <= other.iter_;
    // }

    // bool operator<=(const IteratorInterface& other) const override {
    //     const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T> *p = dynamic_cast<const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T> *>(&other);
    //     if (!p)
    //         throw std::runtime_error("Error: type error.");
    //     return iter_ <= p->iter_;
    // }

    // bool operator>(const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T>& other) const {
    //     return iter_ > other.iter_;
    // }

    // bool operator>(const IteratorInterface& other) const override {
    //     const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T> *p = dynamic_cast<const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T> *>(&other);
    //     if (!p)
    //         throw std::runtime_error("Error: type error.");
    //     return iter_ > p->iter_;
    // }

    // bool operator>=(const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T> &other) const {
    //     return iter_ >= other.iter_;
    // }

    // bool operator>=(const IteratorInterface& other) const override {
    //     const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T> *p = dynamic_cast<const FromStlIteratorBaseTemplate<StlIterType, IteratorInterface, T> *>(&other);
    //     if (!p)
    //         throw std::runtime_error("Error: type error.");
    //     return iter_ >= p->iter_;
    // }

public:
    StlIterType toStdIter(){
        return iter_;
    }

private:
    StlIterType iter_;
};


template <typename StlIterType, typename IteratorInterface ,typename T>
class FromStlConstIteratorBaseTemplate : public IteratorInterface{
public:
    FromStlConstIteratorBaseTemplate(StlIterType iter)
        : iter_(iter) {}
    
    const T& operator*() const override{
        return *iter_;
    }

    IteratorInterface& operator++() override{
        ++iter_;
        return *this;
    }

    IteratorInterface operator+(size_t offset) override{
        auto cp_iter = iter_;
        for(size_t i = 0; i < offset; i++){
            ++cp_iter;
        }
        return FromStlConstIteratorBaseTemplate(cp_iter);
    }

    IteratorInterface operator++(int x) override{
        FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const IteratorInterface& other) const override{
        const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> *p = dynamic_cast<const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> *>(&other);
        if (!p)
            throw std::runtime_error("Error: type error.");
        return iter_ == p->iter_;
    }

    bool operator!=(const IteratorInterface& other) const override{
        const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> *p = dynamic_cast<const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> *>(&other);
        if (!p)
            throw std::runtime_error("Error: type error.");
        return iter_ != p->iter_;
    }

    const T* operator->() const override {
        return &(*iter_);
    }

    // bool operator<(const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T>& other) const {
    //     return iter_ < other.iter_;
    // }

    // bool operator<(const IteratorInterface& other) const override {
    //     const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> *p = dynamic_cast<const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> *>(&other);
    //     if (!p)
    //         throw std::runtime_error("Error: type error.");
    //     return iter_ < p->iter_;
    // }

    // bool operator<=(const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T>& other) const {
    //     return iter_ <= other.iter_;
    // }

    // bool operator<=(const IteratorInterface& other) const override {
    //     const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> *p = dynamic_cast<const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> *>(&other);
    //     if (!p)
    //         throw std::runtime_error("Error: type error.");
    //     return iter_ <= p->iter_;
    // }

    // bool operator>(const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T>& other) const {
    //     return iter_ > other.iter_;
    // }

    // bool operator>(const IteratorInterface& other) const override {
    //     const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> *p = dynamic_cast<const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> *>(&other);
    //     if (!p)
    //         throw std::runtime_error("Error: type error.");
    //     return iter_ > p->iter_;
    // }

    // bool operator>=(const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> &other) const {
    //     return iter_ >= other.iter_;
    // }

    // bool operator>=(const IteratorInterface& other) const override {
    //     const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> *p = dynamic_cast<const FromStlConstIteratorBaseTemplate<StlIterType, IteratorInterface, T> *>(&other);
    //     if (!p)
    //         throw std::runtime_error("Error: type error.");
    //     return iter_ >= p->iter_;
    // }
public:
    StlIterType toStdIter(){
        return iter_;
    }
private:
    StlIterType iter_;
};

}





};