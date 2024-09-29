#ifndef _SMART_PTR_H_
#define _SMART_PTR_H_

template<typename T>
class SmartPtr
{
public:
    SmartPtr( T* _ptr,bool is_array = false):_ptr(_ptr),is_array(is_array),count(new size_t(1)){}

    SmartPtr(const SmartPtr<T>& other) : _ptr(other._ptr), is_array(other.is_array),count(other.count){
        ++(*count);
    }

    SmartPtr<T>& operator=(const SmartPtr<T>& other);

    const T* const GetResourse()const{return _ptr;}

    ~SmartPtr();

    void swap(SmartPtr<T>& other);
    
    const size_t RefCount()const{return *count;}
    const bool ResourseIsArray()const{return is_array;}

    T& operator*(){return *_ptr;}
    T* operator->(){return _ptr;}

private:
    T* _ptr = nullptr;
    bool is_array = false;
    size_t* count = nullptr;
};

template <typename T>
SmartPtr<T>::~SmartPtr()
{
    if(*count == 1){
        is_array ? delete[] _ptr : delete _ptr;
        delete count;
        std::cout << "cleaning resourse from adress\t" << _ptr << std::endl;
    }
    else{
        --(*count);
    }
}

template <typename T>
inline void SmartPtr<T>::swap(SmartPtr<T> &other)
{
    std::swap(_ptr,other._ptr);
    std::swap(is_array,other.is_array);
    std::swap(count,other.count);
}

template <typename T>
SmartPtr<T> &SmartPtr<T>::operator=(const SmartPtr<T> &other)
{
    //copy-swap idiom
    SmartPtr<T> copy(other);
    swap(copy);
    return *this;
}

#endif

