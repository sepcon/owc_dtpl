#pragma once

#include <functional>

#include "json.h"

namespace dtpl {
namespace details {

using src_callback = std::function<json_type()>;

template <class Callable>
src_callback callback(Callable&& c) {
  return std::forward<Callable>(c);
}

}  // namespace details

using details::callback;

}  // namespace dtpl
