#pragma once

#include <optional>
#include <variant>

#include "json.h"

namespace dtpl {

template <class Type, class Base>
struct oveloaded_object : public Base {
  using Base::Base;
  using base_type = Base;
  using type = Type;
  Base& as_base() { return static_cast<Base&>(*this); }
  const Base& as_base() const { return static_cast<Base&>(*this); }
};

class path {
 public:
  using KeyType = std::string;
  using Keys = std::vector<KeyType>;
  using Sep = char;
  using iterator = Keys::iterator;
  using const_iterator = Keys::const_iterator;

  path() = default;
  path(const path&) = default;
  path(path&&) = default;
  path& operator=(const path&) = default;
  path& operator=(path&&) = default;

  path(Keys&& ks) : keys_{std::move(ks)} {}
  path(const Keys& ks) : keys_{ks} {}

  path(const std::string_view& path, Sep sep = '/')
      : keys_{toKeys(path, sep)} {}
  const Keys& keys() const { return keys_; }

  std::string toString(Sep sep = '/') const {
    auto str = std::string{};
    for (const auto& key : keys()) {
      str += key + sep;
    }
    if (!str.empty()) {
      str.resize(str.size() - 1);
    }
    return str;
  }

  path operator/(const KeyType& key) const {
    auto newPath = path{keys_};
    newPath.keys_.push_back(key);
    return newPath;
  }

  path operator/(KeyType&& key) const {
    auto newPath = path{keys_};
    newPath.keys_.push_back(std::move(key));
    return newPath;
  }

  path operator/(const path& p) const {
    auto newKeys = keys_;
    std::copy(std::begin(p.keys()), std::end(p.keys()),
              std::back_inserter(newKeys));
    return path{std::move(newKeys)};
  }

  template <class String>
  bool operator==(const String& p) const {
    auto ks = toKeys(p);
    if (ks.size() != keys_.size()) {
      return false;
    } else {
      auto mi = keys_.rbegin();
      auto i = ks.rbegin();
      auto miend = keys_.rend();
      auto iend = ks.rend();
      while (mi != miend && i != iend) {
        if (*mi != *i) {
          return false;
        }
        ++mi;
        ++i;
      }
      return true;
    }
  }

  auto begin() { return keys_.begin(); }
  auto end() { return keys_.end(); }
  auto begin() const { return keys_.begin(); }
  auto end() const { return keys_.end(); }

 private:
  static Keys toKeys(const std::string_view& path, Sep sep = '/') {
    using std::begin;
    using std::end;
    auto keys = Keys{};

    auto istart = begin(path);
    auto iend = end(path);
    auto it = istart;

    while (it != iend) {
      if (*it == sep) {
        if (*istart != sep) {
          keys.emplace_back(istart, it);
        }
        istart = ++it;
      } else {
        ++it;
      }
    }
    if (istart != iend) {
      auto last = KeyType{istart, iend};
      if (last.back() == '\0') {
        last.resize(last.size() - 1);
      }
      if (!last.empty()) {
        keys.emplace_back(std::move(last));
      }
    }
    return keys;
  }

  Keys keys_;
};

inline bool operator<(const path& kp1, const path& kp2) {
  return kp1.keys() < kp2.keys();
}

inline bool operator==(const path& kp1, const path& kp2) {
  return kp1.keys() == kp2.keys();
}

template <class Type>
using path_to = oveloaded_object<Type, path>;

using path2int = path_to<int>;
using path2double = path_to<double>;
using path2string = path_to<string_type>;
using path2object = path_to<json_object>;
using path2array = path_to<json_array>;
using path2bool = path_to<bool>;
using path2bai = path_to<struct bool_as_int>;
using path2any = std::variant<path2int, path2double, path2string, path2object,
                              path2array, path2bool, path2bai>;

path2int operator""_p2int(const char* p, size_t) { return path2int{p}; }
path2double operator""_p2double(const char* p, size_t) {
  return path2double{p};
}
path2string operator""_p2string(const char* p, size_t) {
  return path2string{p};
}
path2object operator""_p2object(const char* p, size_t) {
  return path2object{p};
}

path2array operator""_p2array(const char* p, size_t) { return path2array{p}; }
path2bool operator""_p2bool(const char* p, size_t) { return path2bool{p}; }

path2bai operator""_p2bai(const char* p, size_t) { return path2bai{p}; }

using key = oveloaded_object<class CollectorKey_, string_type>;

inline key operator""_key(const char* s, std::size_t n) { return key{s, n}; }

template <typename T>
struct jgetter;

template <>
struct jgetter<int> {
  static json_type get_from(const json_type& j) {
    if (j.is_number()) {
      return j;
    } else {
      return {};
    }
  }
};
template <>
struct jgetter<double> {
  static json_type get_from(const json_type& j) {
    if (j.is_number()) {
      return j;
    } else {
      return {};
    }
  }
};
template <>
struct jgetter<bool> {
  static json_type get_from(const json_type& j) {
    if (j.is_bool()) {
      return j;
    } else {
      return {};
    }
  }
};
template <>
struct jgetter<string_type> {
  static json_type get_from(const json_type& j) {
    if (j.is_string()) {
      return j;
    } else {
      return {};
    }
  }
};
template <>
struct jgetter<json_object> {
  static json_type get_from(const json_type& j) {
    if (j.is_object()) {
      return j;
    } else {
      return {};
    }
  }
};
template <>
struct jgetter<json_array> {
  static json_type get_from(const json_type& j) {
    if (j.is_array()) {
      return j;
    } else {
      return {};
    }
  }
};
template <>
struct jgetter<bool_as_int> {
  static json_type get_from(const json_type& j) {
    if (j.is_bool()) {
      return static_cast<int>(j.bool_value());
    } else {
      return {};
    }
  }
};

template <typename T>
auto get(const json_type& j, const path_to<T>& path) {
  auto jptr = &j;
  for (const auto& key : path) {
    if (auto& subj = (*jptr)[key]; !subj.is_null()) {
      jptr = &subj;
    } else {
      return json_type{};
    }
  }
  return jgetter<T>::get_from(*jptr);
}

auto get(const json_type& j, const path2any& path) {
  return std::visit([&](auto&& p) -> json_type { return get(j, p); }, path);
}

}  // namespace dtpl
