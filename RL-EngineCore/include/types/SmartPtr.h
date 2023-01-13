#pragma once

namespace Core {
    template <typename T>
    class SmartPtr
    {
    private:
        void AddRef() {
            if (ptr_ != nullptr) {
                ptr_->AddRef();
            }
        }

        void Release() {
            if (ptr_ != nullptr) {
                ptr_->Release();
                ptr_ = nullptr;
            }
        }

        T* ptr_;

    public:

        //constructor and destructor
        SmartPtr() : ptr_(nullptr) {}
        SmartPtr(T* ptr) : ptr_(ptr) { AddRef(); }
        SmartPtr(const SmartPtr<T>& other) : ptr_(other.ptr_) { AddRef(); }
        SmartPtr(SmartPtr<T>&& other) : ptr_(other.ptr_) { other.ptr_ = nullptr; }
        ~SmartPtr() { Release(); }

        //functions
        T** Create() { Release(); ptr_ = nullptr; return &ptr_; }
        T* Get() const { return ptr_; }
        T** GetAddress() { return &ptr_; }

        //operators
        T* operator->() { return ptr_; }

        SmartPtr<T>& operator=(const SmartPtr<T>& other) {
            if (ptr_ != other.ptr_) {
                Release();
                ptr_ = other.ptr_;
                AddRef();
            }
            return *this;
        }

        SmartPtr<T>& operator=(SmartPtr<T>&& other) {
            if (ptr_ != other.ptr_) {
                Release();
                ptr_ = other.ptr_;
                other.ptr_ = nullptr;
            }
            return *this;
        }
    };
}
