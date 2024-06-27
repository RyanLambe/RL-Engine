#pragma once

#include <optional>
#include <vector>

/**
 * OptionalVector is a wrapper class for a vector of optional values.
 * OptionalVector contains a custom iterator to skip any nullopt values
 */
namespace rl
{

    template<typename Vec> class OptionalVectorIterator
    {
    public:
        using ValueType = typename Vec::ValueType;

        OptionalVectorIterator(std::optional<ValueType>* p, std::optional<ValueType>* e) : ptr(p), end(e)
        {
            if (ptr == nullptr)
            {
                end = ptr;
                return;
            }

            while (!ptr->has_value())
            {
                if (ptr >= end)
                {
                    ptr = end;
                    return;
                }
                ++ptr;
            }
        }

        OptionalVectorIterator& operator++()
        {
            do
            {
                if (ptr >= end)
                    return *this;
                ++ptr;
            } while (!ptr->has_value());
            return *this;
        }

        inline ValueType* operator->() const
        {
            return &(*ptr).value();
        }

        inline ValueType& operator*() const
        {
            return (*ptr).value();
        }

        inline bool operator==(const OptionalVectorIterator& other) const
        {
            return ptr == other.ptr;
        }

        inline bool operator!=(const OptionalVectorIterator& other) const
        {
            return !(*this == other);
        }

    private:
        std::optional<ValueType>* ptr;
        std::optional<ValueType>* end;
    };

    template<typename T> class OptionalVector
    {
    public:
        using ValueType = T;
        using Iterator = OptionalVectorIterator<OptionalVector<T>>;

        std::vector<std::optional<T>> vec = std::vector<std::optional<T>>();

        inline std::optional<T>& operator[](size_t index)
        {
            return vec[index];
        }

        inline void push_back(const std::optional<T>& value)
        {
            vec.push_back(value);
        }

        template<typename... Args> inline void emplace_back(Args&&... args)
        {
            vec.emplace_back(std::forward<Args>(args)...);
        }

        inline size_t size() const noexcept
        {
            return vec.size();
        }

        inline Iterator begin()
        {
            return Iterator(vec.data(), vec.data() + vec.size());
        }

        inline Iterator end()
        {
            return Iterator(vec.data() + vec.size(), vec.data() + vec.size());
        }
    };
} // namespace rl
