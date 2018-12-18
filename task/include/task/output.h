#pragma once

#include <task/input.h>
#include <task/internal/variable_processing.h>

#include <iostream>
#include <memory>


namespace task {

class Output : public internal::VariableProcessing {
public:
    virtual ~Output() = default;

    explicit Output(const std::shared_ptr<Input>& onInput);

    Input* input() const;

    void print(std::ostream& cout = std::cout) const;

protected:
    const std::shared_ptr<Input> onInput_;

    virtual void print_(std::ostream& cout) const = 0;
};

}  // ::task
