cmake_minimum_required(VERSION 3.15)

project(c-scripts-rofi
  VERSION 2.0
  LANGUAGES C
)

# --- Debug | Release

set(default_build_type "Debug")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the build type." FORCE)
  # Optional: Restrict to standard types for the UI
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# ---

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -ggdb3 -fstack-protector -fsanitize=address,undefined")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#add_compile_definitions(_POSIX_C_SOURCE=200809L)
add_compile_definitions(_GNU_SOURCE)

# --- fmt: clang-format

find_program(CLANG_FORMAT_EXE NAMES clang-format)

if(CLANG_FORMAT_EXE)
  message(STATUS "Found clang-format: ${CLANG_FORMAT_EXE}")

  file(GLOB_RECURSE ALL_FORMAT_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
  )

  add_custom_target(fmt
    COMMAND ${CLANG_FORMAT_EXE} --verbose -i ${ALL_FORMAT_FILES}
    COMMENT "Formatting source files with clang-format..."
  )
else()
  message(WARNING "clang-format not found. 'format' target will not be available.")
endif()


# --- tidy: clang-tidy
find_program(CLANG_TIDY_EXE NAMES clang-tidy)

if(CLANG_TIDY_EXE)
  message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")

  file(GLOB_RECURSE ALL_TIDY_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

  add_custom_target(tidy
    COMMAND ${CLANG_TIDY_EXE} -p ${CMAKE_BINARY_DIR} --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy --use-color ${ALL_TIDY_FILES}
    COMMENT "Running Clang-Tidy static analysis..."
  )
else()
  message(WARNING "clang-tidy not found. 'tidy' target will not be available.")
endif()


# --- doxygen

find_package(Doxygen)

if (DOXYGEN_FOUND)
  set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs")

  doxygen_add_docs(docs
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    COMMENT "Generating API documentation"
  )
else()
  message(STATUS "Doxygen not found, documentation target will not be created.")
endif()


# --- executable: scripts-rofi

add_executable(scripts-rofi ${SOURCES})

target_include_directories(scripts-rofi
  PRIVATE include
  ${PROJECT_SOURCE_DIR}/vnd/uthash/include)
