#pragma once
#include <exception>

//
// Usage:
//
// SCOPE_SUCCESS{ cout << "hello"; }; // will be called at the scope success in case of success (no exception is thrown)
//

#define SCOPE_SUCCESS_CAT2(x, y) x##y
#define SCOPE_SUCCESS_CAT(x, y) SCOPE_SUCCESS_CAT2(x, y)
#define SCOPE_SUCCESS const auto SCOPE_SUCCESS_CAT(scopeSuccess_, __COUNTER__) = ScopeExit::MakeScopeSuccess() += [&]

namespace ScopeExit
{
    template<typename F>
    class ScopeSuccess 
    {
    public:
        explicit ScopeSuccess(F&& fn) : m_fn(fn)
        {
        }
        
        ~ScopeSuccess()
        { 
            if (!std::uncaught_exception())
            {
                m_fn();
            }
        }

        ScopeSuccess(ScopeSuccess&& other) : m_fn(std::move(other.m_fn))
        {
        }

    private:
        ScopeSuccess(const ScopeSuccess&);
        ScopeSuccess& operator=(const ScopeSuccess&);

    private:
        F m_fn;
    };

    struct MakeScopeSuccess
    {
        template<typename F>
        ScopeSuccess<F> operator+=(F&& fn)
        {
            return ScopeSuccess<F>(std::move(fn));
        }
    };
}