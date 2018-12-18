#pragma once

#include <task/internal/variable_processing.h>

#include <iostream>


namespace task {

class Input : public internal::VariableProcessing {
public:
    virtual ~Input() = default;

    void scan(std::istream& cin = std::cin);

protected:
    virtual void scan_(std::istream& cin) = 0;

    bool scanned_ = false;
};

}  // ::task
