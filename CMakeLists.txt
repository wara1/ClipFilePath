cmake_minimum_required(VERSION 3.14)
project(ClipFilePath)

add_executable(
  ${PROJECT_NAME} WIN32
)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  PRIVATE
    src
    src/func
)

# ソース
set(PUBLIC_FILES)
set(PRIVATE_FILES
  src/main.cpp
  src/func/clip_file_path.cpp
  src/func/clip_file_path.hpp
)

target_sources(${PROJECT_NAME}
  PUBLIC
    ${PUBLIC_FILES}
  PRIVATE
    ${PRIVATE_FILES}
)

# GoogleTest requires at least C++14
set_property(TARGET ${PROJECT_NAME}
  PROPERTY
    CXX_STANDARD 14
)

# CMakePredefinedTargets
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# グループ名
set(GROUP_NAME ${PROJECT_NAME})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES FOLDER ${GROUP_NAME})

# フィルタ
set(ALL_FILES ${PUBLIC_FILES} ${PRIVATE_FILES})
foreach(file_path IN LISTS ALL_FILES)
  string(REGEX MATCH "^.*\/" directory_path ${file_path})
  SOURCE_GROUP(${directory_path} FILES ${file_path})
endforeach()
