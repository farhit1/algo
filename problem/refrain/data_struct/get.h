#pragma once

#include "refrain.h"

#include <memory>
#include <vector>


namespace problem {
namespace refrain {
namespace data_struct {

std::unique_ptr<Refrain> get(const std::vector<int>& s, size_t alphabet);

}}}  // ::problem::refrain::data_struct
