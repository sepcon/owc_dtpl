#pragma once

#include <set>

#include "json_paths.h"

namespace dtpl {
namespace details {

using oesis_field = std::pair<string_type, path2any>;
struct oesis_field_compare {
  bool operator()(const oesis_field& l, const oesis_field& r) const {
    return l.first < r.first;
  }
};

using oesis_fields = std::set<oesis_field, oesis_field_compare>;

using oesis_method_input = std::variant<json_type, oesis_fields, oesis_field>;

oesis_method_input method_input(std::initializer_list<oesis_field> tinput) {
  return oesis_method_input{oesis_fields{std::move(tinput)}};
}

oesis_method_input method_input(oesis_field tinput) {
  return oesis_method_input{std::move(tinput)};
}

oesis_method_input method_input(json_type tinput) {
  return oesis_method_input{std::move(tinput)};
}

struct src_oesis_method_1_field {
  path2any src_path;
  oesis_method_input input;
  int mid = -1;
};

struct tpl_last_invocation {
  path2any collected_path;
};

src_oesis_method_1_field oesis_method(int id, path2any src_path,
                                      oesis_method_input&& input = {}) {
  return {std::move(src_path), std::move(input), id};
}

struct src_oesis_method_n_field {
  oesis_fields fields;
  oesis_method_input input;
  int mid = -1;
};

inline src_oesis_method_n_field oesis_method(int mid, oesis_fields&& fs,
                                             oesis_method_input&& input = {}) {
  return src_oesis_method_n_field{std::move(fs), std::move(input), mid};
}

struct src_oesis_category {
  oesis_fields fields;
  oesis_method_input input;
  int category = -1;
};

inline src_oesis_category oesis_category(int mid, oesis_fields&& fs,
                                         oesis_method_input&& input = {}) {
  return src_oesis_category{std::move(fs), std::move(input), mid};
}

inline oesis_field operator<<=(string_type&& dst_field, path2any&& src_path) {
  return {std::move(dst_field), std::move(src_path)};
}
using src_oesis = std::variant<src_oesis_category, src_oesis_method_1_field,
                               src_oesis_method_n_field>;

}  // namespace details

using details::method_input;
using details::oesis_category;
using details::oesis_method;
}  // namespace dtpl
