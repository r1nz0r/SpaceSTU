#pragma once

namespace SSTU
{
    class NonCopyable
    {
    public:
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator = (const NonCopyable&) = delete;
        NonCopyable(NonCopyable&&) noexcept = delete;
        NonCopyable& operator = (NonCopyable&&) noexcept = delete;

    protected:
        NonCopyable() = default;
        ~NonCopyable() = default; /// Protected non-virtual destructor
    };
}
