#pragma once
#include <utility>

//
// Usage:
//
// SCOPE_EXIT{ cout << "hello"; }; // will be called at the scope exit
//

#define SCOPE_EXIT_CAT2(x, y) x##y
#define SCOPE_EXIT_CAT(x, y) SCOPE_EXIT_CAT2(x, y)
#define SCOPE_EXIT const auto SCOPE_EXIT_CAT(scopeExit_, __COUNTER__) = ScopeExit::MakeScopeExit() += [&]

namespace ScopeExit
{
    template<typename F>
    class ScopeExit 
    {
    public:
        explicit ScopeExit(F&& fn) : m_fn(fn)
        {
        }
        
        ~ScopeExit()
        { 
            m_fn();
        }

        ScopeExit(ScopeExit&& other) : m_fn(std::move(other.m_fn))
        {
        }

    private:
        ScopeExit(const ScopeExit&);
        ScopeExit& operator=(const ScopeExit&);

    private:
        F m_fn;
    };

    struct MakeScopeExit
    {
        template<typename F>
        ScopeExit<F> operator+=(F&& fn)
        {
            return ScopeExit<F>(std::move(fn));
        }
    };
}