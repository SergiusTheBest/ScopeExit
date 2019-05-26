#pragma once
#include <exception>

//
// Usage:
//
// SCOPE_FAILURE{ cout << "hello"; }; // will be called at the scope exit in case of failure (exception is thrown)
//

#define SCOPE_FAILURE_CAT2(x, y) x##y
#define SCOPE_FAILURE_CAT(x, y) SCOPE_FAILURE_CAT2(x, y)
#define SCOPE_FAILURE const auto& SCOPE_FAILURE_CAT(scopeFailure_, __COUNTER__) = ScopeExit::MakeScopeFailure() += [&]

namespace ScopeExit
{
    template<typename F>
    class ScopeFailure 
    {
    public:
        explicit ScopeFailure(F&& fn) : m_fn(fn)
        {
        }
        
        ~ScopeFailure()
        { 
            if (std::uncaught_exception())
            {
                m_fn();
            }
        }

        ScopeFailure(ScopeFailure&& other);

    private:
        ScopeFailure(const ScopeFailure&);
        ScopeFailure& operator=(const ScopeFailure&);

    private:
        F m_fn;
    };

    struct MakeScopeFailure
    {
        template<typename F>
        ScopeFailure<F> operator+=(F&& fn)
        {
            return ScopeFailure<F>(std::move(fn));
        }
    };
}