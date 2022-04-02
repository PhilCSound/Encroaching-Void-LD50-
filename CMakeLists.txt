cmake_minimum_required(VERSION 3.15)

project(AlgoViewer)

option(USE_STATIC_LIBS "Link libraries statically?" OFF)
option(USE_STATIC_STD_LIBS "Use statically linked standard/runtime libraries? This option must match the one used for SFML." OFF)

set(SOURCE_FILES
	src/main.cpp
	src/Application.cpp
	src/Application.hpp
	src/State.hpp
	src/AlgoDisplayState.hpp
	src/AlgoDisplayState.cpp
	src/AlgoVisualizer.hpp
	src/AlgoVisualizer.cpp
	src/Command.hpp
	src/LookCommand.hpp
	src/SwapCommand.hpp
	src/EnumAnimationState.hpp
	src/Algorithms.hpp
	src/Algorithms.cpp)

set(SFML_STATIC_LIBRARIES FALSE)
set(TGUI_BACKEND SFML)
set(TGUI_STATIC_LIBRARIES FALSE)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(USE_STATIC_LIBS)
	set(SFML_STATIC_LIBRARIES TRUE)
	set(TGUI_STATIC_LIBRARIES TRUE)
endif()

find_package(SFML COMPONENTS graphics audio REQUIRED)
find_package(TGUI REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio tgui)


if(USE_STATIC_STD_LIBS)
	if(WIN32 AND MSVC)
		set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	else()
		target_compile_options(${PROJECT_NAME} PRIVATE -static)
	endif()
endif()

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION .)