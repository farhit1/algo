#pragma once

#include <cassert>
#include <memory>
#include <vector>


namespace task {
namespace internal {

//////////////////
// DECLARATIONS //
//////////////////

class VariableProcessing {
private:
    class UntypedVariable {
    public:
        virtual ~UntypedVariable() = default;

        virtual bool isSet() const = 0;
    };

    std::vector<const UntypedVariable*> requiredVariables_;

protected:
    template<typename T>
    class Variable : public UntypedVariable {
    public:
        Variable() = default;

        template<typename U>
        void set(U&& value);

        void scan(std::istream& cin);

        const T& get() const;

        virtual bool isSet() const override;

    private:
        std::unique_ptr<T> value_;
    };

    template<typename T>
    std::unique_ptr<Variable<T>> variable();

    template<typename T>
    std::unique_ptr<Variable<T>> requiredVariable();

    template<typename T>
    void set(Variable<T>& variable, T&& value);

    void isAllSet() const;

public:
    virtual ~VariableProcessing() = default;
};

/////////////////////////
// Variable DEFINITION //
/////////////////////////

template<typename T>
template<typename U>
void VariableProcessing::Variable<T>::set(U&& value)
{
    assert(!isSet());

    value_ = std::make_unique<T>(std::forward<U>(value));
}

template<typename T>
void VariableProcessing::Variable<T>::scan(std::istream& cin)
{
    T t;
    cin >> t;
    set(std::move(t));
}

template<typename T>
const T& VariableProcessing::Variable<T>::get() const
{
    assert(isSet());

    return *value_;
}

template<typename T>
bool VariableProcessing::Variable<T>::isSet() const
{
    return bool(value_);
}

///////////////////////////////////
// VariableProcessing DEFINITION //
///////////////////////////////////

template<typename T>
std::unique_ptr<VariableProcessing::Variable<T>>
VariableProcessing::variable()
{
    return std::make_unique<Variable<T>>();
}

template<typename T>
std::unique_ptr<VariableProcessing::Variable<T>>
VariableProcessing::requiredVariable()
{
    auto variable = std::make_unique<Variable<T>>();
    requiredVariables_.push_back(variable.get());
    return variable;
}

template<typename T>
void VariableProcessing::set(Variable<T>& variable, T&& value)
{
    assert(!variable.isSet());

    variable = std::forward(value);
}

}}  // ::task::internal
