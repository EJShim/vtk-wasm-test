project(manager)

# -----------------------------------------------------------------------------
# Handle VTK dependency
# -----------------------------------------------------------------------------

find_package(VTK
  COMPONENTS
    FiltersSources      # VTK pipeline
    InteractionStyle    # Mouse handling
    RenderingOpenGL2    # For Rendering
    RenderingUI         # For SDL2 Window
)

if (NOT VTK_FOUND)
  message("Skipping example: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif ()

# -----------------------------------------------------------------------------
# Compile example code
# -----------------------------------------------------------------------------

add_executable(${CMAKE_PROJECT_NAME} manager.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}
  PRIVATE
    VTK::FiltersSources
    VTK::InteractionStyle
    VTK::RenderingOpenGL2
    VTK::RenderingUI
)

# -----------------------------------------------------------------------------
# WebAssembly build options
# -----------------------------------------------------------------------------
set(emscripten_link_options)
set(emscripten_compile_options)

list(APPEND emscripten_link_options
  "--bind"
  "SHELL:-s MODULARIZE=1"
  "SHELL:-s EXPORT_NAME=tester"
  "SHELL:-s WASM=1"
  "SHELL:-s EXPORT_ES6=1"
)

set(emscripten_debug_options)
set(DEBUGINFO "PROFILE" CACHE STRING "Type of debug info")
set_property(CACHE DEBUGINFO PROPERTY
  STRINGS
    NONE              # -g0
    READABLE_JS       # -g1
    PROFILE           # -g2
    DEBUG_NATIVE      # -g3
)

if(DEBUGINFO STREQUAL "NONE")
  list(APPEND emscripten_debug_options
    "-g0"
  )
elseif(DEBUGINFO STREQUAL "READABLE_JS")
  list(APPEND emscripten_debug_options
    "-g1"
  )
  list(APPEND emscripten_link_options
    "SHELL:-s DEMANGLE_SUPPORT=1"
  )
elseif(DEBUGINFO STREQUAL "PROFILE")
  list(APPEND emscripten_debug_options
    "-g2"
  )
  list(APPEND emscripten_link_options
    "SHELL:-s DEMANGLE_SUPPORT=1"
  )
elseif(DEBUGINFO STREQUAL "DEBUG_NATIVE")
  list(APPEND emscripten_debug_options
    "-g3"
  )
  list(APPEND emscripten_link_options
    "SHELL:-s ASSERTIONS=1"
    "SHELL:-s DEMANGLE_SUPPORT=1"
  )
endif()

# -----------------------------------------------------------------------------
# Build options
# -----------------------------------------------------------------------------
set(emscripten_optimizations)
set(OPTIMIZE "SMALLEST_WITH_CLOSURE" CACHE STRING "Emscripten optimization")
set_property(CACHE OPTIMIZE PROPERTY
  STRINGS
    NO_OPTIMIZATION       # -O0
    LITTLE                # -O1
    MORE                  # -O2
    BEST                  # -O3
    SMALL                 # -Os
    SMALLEST              # -Oz
    SMALLEST_WITH_CLOSURE # -Oz --closure 1
)

if(OPTIMIZE STREQUAL "NO_OPTIMIZATION")
  list(APPEND emscripten_optimizations
    "-O0"
  )
elseif(OPTIMIZE STREQUAL "LITTLE")
  list(APPEND emscripten_optimizations
    "-O1"
  )
elseif(OPTIMIZE STREQUAL "MORE")
  list(APPEND emscripten_optimizations
    "-O2"
  )
elseif(OPTIMIZE STREQUAL "BEST")
  list(APPEND emscripten_optimizations
    "-O3"
  )
elseif(OPTIMIZE STREQUAL "SMALL")
  list(APPEND emscripten_optimizations
    "-Os"
  )
elseif(OPTIMIZE STREQUAL "SMALLEST")
  list(APPEND emscripten_optimizations
    "-Oz"
  )
elseif(OPTIMIZE STREQUAL "SMALLEST_WITH_CLOSURE")
  list(APPEND emscripten_optimizations
    "-Oz"
  )
  list(APPEND emscripten_link_options
    "--closure 1"
  )
endif()

target_compile_options(${CMAKE_PROJECT_NAME}
  PUBLIC
    ${emscripten_compile_options}
    ${emscripten_optimizations}
    ${emscripten_debug_options}
)

target_link_options(${CMAKE_PROJECT_NAME}
  PUBLIC
    ${emscripten_link_options}
    ${emscripten_optimizations}
    ${emscripten_debug_options}
)

# -----------------------------------------------------------------------------
# VTK modules initialization
# -----------------------------------------------------------------------------

vtk_module_autoinit(
  TARGETS  ${CMAKE_PROJECT_NAME}
  MODULES  ${VTK_LIBRARIES}
)
