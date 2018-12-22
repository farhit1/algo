# Common build system for problems

## Available problems

- [Internal point](problem/internal_point)
- [Refrain](problem/refrain)

## How to add a new problem

### 0. Start

Create folder `problem/your_problem_name`. All the sources for your problem should be placed there.

### 1. Input

Describe it's input like that:

```c++
class Input : public ::task::Input {
public:
    Input() = default;

    std::unique_ptr<Variable<int>> n = requiredVariable<int>();
    std::unique_ptr<Variable<int>> m = variable<int>();

protected:
    virtual void scan_(std::istream& cin) override {
        n->scan(cin);
        if (n->get() == 42) {
            m->scan(cin);
        }
    }
};
```

Use `requiredVariable` to check, that `scan_` really got `n` or just `variable` if it's not necessary.
Use `set` to set variable to something or `scan` to get it from `std::istream`.
Note that all the variables could be set not more that once.
Use `get` to get variable's value.

### 2. Output

Then describe problem's output:

```c++
class Output : public ::task::Output {
public:
    using ::task::Output::Output;

    std::unique_ptr<Variable<int>> answer = requiredVariable<int>();

protected:
    virtual void print_(std::ostream& cout) const override {
        cout << answer->get() << std::endl;
    }
};
```

Usage is the same as in input.

### 3. Solution

Soluton should read input and create an output. It looks like that: 

```c++
class Solution : public ::task::Solution {
public:
    explicit Solution(const std::shared_ptr<::task::Input>& input)
            : ::task::Solution(input)
            , input_(static_cast<const Input*>(solutionInput_.get()))
            , output_(std::make_shared<Output>(input))
    {}

    virtual void run() override {
        if (input_->n->get() == 42) {
            output_->answer->set(input_->m->get());
        }
        else {
            output_->answer->set(input_->n->get());
        }
    }

    virtual const Output* output() const override {
        return output_.get();
    }

private:
    const Input* input_;
    std::shared_ptr<Output> output_;
};
```

Note, that like in input, you can't set any output's variable more than once.

### 4. Input and solution getter

Create a file, which contains following functions from the global namespace:

```c++
std::shared_ptr<::task::Input> getInput() {
    return std::make_shared<::your::Input>();
}

std::unique_ptr<::task::Solution> getSolution(const std::shared_ptr<::task::Input>& input) {
    return std::make_unique<::your::Solution>(input);
}
```

### 5. Usage of data structs and modules

You can use existing data structures (see available ones in `data_struct` folder) or even add yours.

This is how you can use treap:

1. Include it

```c++
#include <data_struct/treap.h>
```

2. Use it
```c++
auto treap = ::data_struct::getTreap<int>();
```

Given `treap` satisfies [set's interface](data_struct/include/data_struct/set.h).

### 6. Build

Use `python3 build.py your_problem_name singletest` to build your problem
(you can also use `multitests` instead of the last argument). 

Building system will call `add_sources(args)` function from `problem/your_problem_name/build.py`.
Here `args` is array of arguments passed to builder after ones described above.
It should return an array of paths to `.cpp` files to be linked with your program.
Don't forget to add file, which contains `getInput` and `getSolution` implementation.

### 7. Run

`./run`
