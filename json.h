#pragma once
#include <json11.hpp>

namespace dtpl {

using string_type = std::string;
using json_type = json11::Json;
using json_object = std::map<std::string, json_type>;
using json_array = json_type::array;

}  // namespace dtpl
