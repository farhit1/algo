#pragma once

#include <cassert>
#include <memory>
#include <vector>


namespace task {
namespace internal {

class VariableProcessing {
private:
    class UntypedVariable {
    public:
        virtual ~UntypedVariable() = default;

        virtual bool isSet() const = 0;
    };

    std::vector<const UntypedVariable *> requiredVariables_;

protected:
    template<typename T>
    class Variable : public UntypedVariable {
    public:
        Variable() = default;

        template<typename U>
        void set(U&& value)
        {
            assert(!isSet());

            value_ = std::make_unique<T>(std::forward<U>(value));
        }

        void scan(std::istream& cin)
        {
            T t;
            cin >> t;
            set(std::move(t));
        }

        const T& get() const
        {
            assert(isSet());

            return *value_;
        }

        virtual bool isSet() const override
        {
            return bool(value_);
        }

    private:
        std::unique_ptr<T> value_;
    };

    template<typename T>
    std::unique_ptr<Variable<T>> variable()
    {
        return std::make_unique<Variable<T>>();
    }

    template<typename T>
    std::unique_ptr<Variable<T>> requiredVariable()
    {
        auto variable = std::make_unique<Variable<T>>();
        requiredVariables_.push_back(variable.get());
        return variable;
    }

    template<typename T>
    void set(Variable<T> &variable, T&& value)
    {
        assert(!variable.isSet());

        variable = std::forward(value);
    }

    void isAllSet() const;

public:
    virtual ~VariableProcessing() = default;
};

}}  // ::task::internal
