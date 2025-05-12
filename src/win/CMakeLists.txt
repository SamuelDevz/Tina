set(SOURCE_FILES src/Error.cpp
    src/Timer.cpp
    src/Window.cpp
    src/Input.cpp
    src/Game.cpp
    src/Engine.cpp)

if(BUILD_SHARED_LIBS)
    add_library(window SHARED ${SOURCE_FILES})
    target_compile_definitions(window PRIVATE ENGINE_EXPORTS)
    target_compile_definitions(window PUBLIC EXPORT)
else()
    add_library(window STATIC ${SOURCE_FILES})
endif()

target_include_directories(window PUBLIC include)
target_link_libraries(window PRIVATE winmm.lib)
target_compile_definitions(window PUBLIC $<IF:$<CONFIG:DEBUG>,_DEBUG,NDEBUG>)