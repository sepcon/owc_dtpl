#pragma once

#include "templates.h"

namespace dtpl {
namespace details {

using optional_object = std::optional<json_object>;
class collector_base {
 public:
  inline optional_object collect(const fields& dtpl);
  inline optional_object collect(const key& key, const fields& dtpl);
  inline optional_object collect(const key& key,
                                 const src_oesis_method_n_field& conf);
  inline optional_object collect(const key& key,
                                 const src_oesis_method_1_field& src);
  inline optional_object collect(const key& key,
                                 const src_oesis_category& conf);
  inline optional_object collect(const key& key, const src_oesis& conf);
  inline optional_object collect(const key& key, const src_callback& callback);
  virtual json_type oesis_invoke(int mid, const json_type& input) {
    return json_object{{"os_name", "100"},
                       {"version", "10201"},
                       {"val", json_object{{"hello", "world"}}},
                    {"bool", true},
                       {"public_file_sharing", 1},
                       {"public_file_sharing_bool", 1}};
  }
};

optional_object collector_base::collect(const key& key, const fields& dtpl) {
  if (!dtpl.empty()) {
    if (auto val = collect(dtpl); val.has_value()) {
      return json_object{{key, std::move(val.value())}};
    }
  }
  return {};
}

optional_object collector_base::collect(const fields& dtpl) {
  if (!dtpl.empty()) {
    json_object output;
    for (auto& [key, val] : dtpl) {
      std::visit(
          [&key = key, &output, this](auto&& val) {
            if (auto subOutput = collect(key, val)) {
              output.merge(subOutput.value());
            }
          },
          val);
    }
    if (!output.empty()) {
      return output;
    }
  }
  return {};
}

optional_object collector_base::collect(const key& key,
                                        const src_oesis_method_n_field& dtpl) {
  auto result = oesis_invoke(dtpl.mid, {});
  json_object output;
  for (auto& [key, path] : dtpl.fields) {
    std::visit(
        [&, &k = key](auto&& p) {
          if (auto outk = get(result, p); !outk.is_null()) {
            output[k] = std::move(outk);
          }
        },
        path);
  }
  return json_object{{key, std::move(output)}};
}

optional_object collector_base::collect(const key& key,
                                        const src_oesis_method_1_field& src) {
  auto result = oesis_invoke(src.mid, {});
  return json_object{{key, get(result, src.src_path)}};
}

optional_object collector_base::collect(const key& key,
                                        const src_oesis_category& conf) {
  return json_object{{"public_sharing", -1}};
}

optional_object collector_base::collect(const key& key, const src_oesis& conf) {
  optional_object output;
  std::visit([&](auto&& cf) { output = collect(key, cf); }, conf);
  return output;
}

inline optional_object collector_base::collect(const key& key,
                                               const src_callback& callback) {
  auto output = callback();
  if (output.is_null()) {
    return {};
  } else {
    return json_object{{key, std::move(output)}};
  }
}

}  // namespace details
using details::collector_base;
}  // namespace dtpl
