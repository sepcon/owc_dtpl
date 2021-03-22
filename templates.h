#pragma once

#include "callback_tpl.h"
#include "json_paths.h"
#include "oesis_tpl.h"

namespace dtpl {
namespace details {

struct field;
using fields = std::vector<field>;
using source = std::variant<src_oesis, src_callback, fields>;

struct field {
  key key;
  source val;
};

field operator<<=(key key, source item) {
  return field{std::move(key), source{std::move(item)}};
}

field operator<<=(key key, std::initializer_list<field> sub_data) {
  return field{std::move(key), fields{std::move(sub_data)}};
}

}  // namespace details

using details::operator<<=;
using data_template = details::fields;

}  // namespace dtpl
