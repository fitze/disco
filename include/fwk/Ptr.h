// Copyright (C) 1993-2002 David R. Cheriton.  All rights reserved.
// Modified by Chris Dembia.

#ifndef FWK_PTR_H
#define FWK_PTR_H

namespace fwk {

template <class T>
class Ptr
{
public:
    Ptr(T* p = 0) : ptr_(p) { if (ptr_) ptr_->newRef(); }
    Ptr(const Ptr<T>& mp) : ptr_(mp.ptr_) { if (ptr_) ptr_->newRef(); }
    ~Ptr() { if (ptr_) ptr_->deleteRef(); }

    Ptr<T>& operator=( const Ptr<T>& mp );
    Ptr<T>& operator=( Ptr<T>& mp );
    Ptr<T>& operator=( T* p );

    bool operator<(const Ptr<T>& mp ) const { return ptr_ < mp.ptr_; }

    bool operator==( const Ptr<T>& mp ) const { return ptr_ == mp.ptr_; }
    bool operator!=( const Ptr<T>& mp ) const { return ptr_ != mp.ptr_; }
    bool operator==( T* p ) const { return ptr_ == p; }
    bool operator!=( T* p ) const { return ptr_ != p; }

    const T * operator->() const { return ptr_; }
    T * operator->() { return ptr_; }
    T * ptr() const { return ptr_; }

    template <class OtherType>
    operator Ptr<OtherType>() const { return Ptr<OtherType>( ptr_ ); }

    struct PointerConversion { int valid; };
    operator int PointerConversion::*() const {
        return ptr_ ? &PointerConversion::valid : 0;
    }

protected:
    T *ptr_;
};

template<class T> Ptr<T>&
Ptr<T>::operator=( const Ptr<T>& mp ) {
    const T * save = ptr_;
    ptr_ = mp.ptr_;
    if( ptr_ ) ptr_->newRef();
    if( save ) save->deleteRef();
    return *this;
}

template<class T> Ptr<T>&
Ptr<T>::operator=( Ptr<T>& mp ) {
    T * save = ptr_;
    ptr_ = mp.ptr_;
    if( ptr_ ) ptr_->newRef();
    if( save ) save->deleteRef();
    return *this;
}

template<class T> Ptr<T>&
Ptr<T>::operator=( T* p ) {
    T * save = ptr_;
    ptr_ = p;
    if( ptr_ ) ptr_->newRef();
    if( save ) save->deleteRef();
    return *this;
}

}

#endif /* FWK_PTR_H */