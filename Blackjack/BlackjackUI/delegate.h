/*!
 * \file delegate.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#ifndef DELEGATE_H
#define DELEGATE_H

#include "game_exceptions.h"

/*!
 * \class Delegate
 *
 * \brief This class is not documented.
 *
 */
template<typename T>
class Delegate {};

/*!
 * \class Delegate
 *
 * \brief This class is not documented.
 *
 */
template<typename R, typename ARG0>
class Delegate<R (ARG0)>
{
    typedef void* InstancePtr;
    typedef bool (*InternalFunction)(InstancePtr, ARG0);
    typedef std::pair<InstancePtr, InternalFunction> Stub;

public:
    Delegate(void) : m_stub((void*)NULL, (InternalFunction)NULL) {}

    // Binds a free function
    template <R (*Function)(ARG0)>
    Delegate<R (ARG0)>& Bind(void)
    {
        m_stub.first = (void*)NULL;
        m_stub.second = &FunctionStub<Function>;
        return *this;
    }

    // Binds a class method
    template <class C, R (C::*Function)(ARG0)>
    Delegate<R (ARG0)>& Bind(C* instance)
    {

        m_stub.first = instance;
        m_stub.second = &ClassMethodStub<C, Function>;
        return *this;
    }

    // Invokes the delegate
    R Invoke(ARG0 arg0) const
    {
        if (!m_stub.second)
            throw InvalidDelegateException("Cannot invoke unbound delegate. Call Bind() first.");

        return m_stub.second(m_stub.first, arg0);
    }

    bool inline IsNULL() { return (this->m_stub.second == NULL); }

private:
    // turns a free function into our internal function stub
    template <R (*Function)(ARG0)>
    static inline R FunctionStub(InstancePtr, ARG0 arg0)
    {
        // we don't need the instance pointer because we're dealing with free functions
        return (Function)(arg0);
    }

    // turns a member function into our internal function stub
    template <class C, R (C::*Function)(ARG0)>
    static inline R ClassMethodStub(InstancePtr instance, ARG0 arg0)
    {
        // cast the instance pointer back into the original class instance
        return (static_cast<C*>(instance)->*Function)(arg0);
    }

    Stub m_stub;
};

#endif // DELEGATE_H
