cmake_minimum_required(VERSION 3.5)

project(owc_dtpl LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(D:/SourceCode/GitHub/json11)
include_directories(${OESIS_API_INCLUDE_DIR})
add_executable(owc_dtpl
  main.cpp
  Config.cpp
  oesis_tpl.h
  json_paths.h
  templates.h
  collector.h
  json.h
  callback_tpl.h
  D:/SourceCode/GitHub/json11/json11.cpp
)

