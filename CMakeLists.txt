cmake_minimum_required(VERSION 3.10.2)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(lib/engine)

project(game CXX)
include_directories(./include)
SET (GAME_SOURCE_DIR ./src)

if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Android")
	file(GLOB GAME_SOURCE_FILES ${GAME_SOURCE_DIR}/*.cpp ${GAME_SOURCE_DIR}/desktop/*.cpp ./include/*.h)
else()
	file(GLOB GAME_SOURCE_FILES ${GAME_SOURCE_DIR}/SceneMainMenu.cpp ${GAME_SOURCE_DIR}/android/main_android.cpp ./include/*.h)
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Android")
	find_library(log-lib log)
	find_library(android-lib android)
	find_library(egl-lib EGL)
	set(OPENGL_LIB GLESv2)
endif()

if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Android")
	add_executable(game ${GAME_SOURCE_FILES})
else()
	add_library(game SHARED ${GAME_SOURCE_FILES})
endif()
target_include_directories(engine INTERFACE ${ENGINE_INCLUDE_DIR})
target_link_libraries(game engine)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Android")
	target_link_libraries(game ${OPENGL_LIB} ${log-lib} ${android-lib} ${egl-lib})
endif()