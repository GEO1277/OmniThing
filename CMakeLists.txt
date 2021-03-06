cmake_minimum_required(VERSION 3.7)
project(OmniThing)
message("Running OmniThing's CMakeLists.txt")

set(ARDUINO_CONFIG "arduino_config.json" CACHE STRING "Which json file to use for config")
set(BUILD_TARGET "not_set" CACHE STRING "Which build target (linux, windows, rpi, arduino)")

file(GLOB_RECURSE sources_core src/core/*.cpp src/core/*.c)
file(GLOB_RECURSE sources_os_common src/os_common/lib/*.cpp)
file(GLOB_RECURSE sources_rpi src/raspberry_pi/lib/*.cpp)
file(GLOB_RECURSE sources_arduino src/arduino/lib/*.cpp)
file(GLOB_RECURSE sources_embedded_common src/embedded_common/lib/*.cpp)

file(GLOB_RECURSE includes_core include/core/*.h)
file(GLOB_RECURSE includes_os_common include/os_common/lib/*.h)
file(GLOB_RECURSE includes_rpi include/raspberry_pi/lib/*.h)
file(GLOB_RECURSE includes_arduino include/arduino/lib/*.h)
file(GLOB_RECURSE includes_embedded_common include/embedded_common/lib/*.h)

file(GLOB sources_ESP32WebServer src/ESP32WebServer/*)
file(GLOB sources_ESP32Servo src/ESP32Servo/*)

if(BUILD_TARGET STREQUAL "linux")
    message("Creating Linux Build Configuration")
    add_executable(OmniThing src/os_common/main_os.cpp ${sources_core} ${sources_os_common})
    include_directories(include/core)
    include_directories(include/os_common/lib)
    target_link_libraries(OmniThing pthread)

    add_definitions("-DOMNI_FAKE_F_MACRO")
    add_definitions("-DOMNI_PLAT_LINUX")
    add_definitions("-DOMNI_NOT_ARDUINO")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
elseif(BUILD_TARGET STREQUAL "rpi")
    message("Creating Raspberry Pi Build Configuration")
    add_executable(OmniThing src/os_common/main_os.cpp  ${sources_core} 
                                                        ${sources_os_common} 
                                                        ${sources_rpi} 
                                                        ${sources_embedded_common}
                                                        )
    include_directories(include/core)
    include_directories(include/os_common/lib)
    include_directories(include/raspberry_pi/lib)
    include_directories(include/embedded_common/lib)
    target_link_libraries(OmniThing pigpio pthread rt)

    add_definitions("-DOMNI_FAKE_F_MACRO")
    add_definitions("-DOMNI_PLAT_RPI")
    add_definitions("-DOMNI_NOT_ARDUINO")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
elseif(BUILD_TARGET STREQUAL "windows")
	message("Creating Windows Build Configuration")
	add_executable(OmniThing src/os_common/main_os.cpp ${sources_core} ${sources_os_common})
	add_definitions(-DFOO)
	include_directories(include/core)
	include_directories(include/os_common/lib)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT OmniThing)
	find_library(ws2_32_LIBRARY_PATH ws2_32)
	target_link_libraries(OmniThing ${ws2_32_LIBRARY_PATH})

    add_definitions("-DOMNI_FAKE_F_MACRO")
    add_definitions("-DOMNI_PLAT_WINDOWS")
    add_definitions("-DOMNI_NOT_ARDUINO")
elseif(BUILD_TARGET STREQUAL "arduino")
    message("Creating Arduino Build Configuration")
    file(GLOB_RECURSE old_files arduino_build/*)
    if(EXISTS arduino_build)
        file(REMOVE ${old_files})
    endif()
    file(COPY src/arduino/OmniThing.ino ${sources_core} 
                                        ${sources_arduino} 
                                        ${includes_core} 
                                        ${includes_arduino} 
                                        ${sources_ESP32WebServer} 
                                        ${sources_ESP32Servo} 
                                        ${sources_embedded_common}
                                        ${includes_embedded_common}
                                        DESTINATION arduino_build/OmniThing)
    execute_process(COMMAND python jsonToHeader.py ${ARDUINO_CONFIG} arduino_build/OmniThing/ArduinoJsonConfig.h)
else()
    message("Invalid BUILD_TARGET specify with -DBUILD_TARGET=[linux, rpi, windows, or arduino]")
endif()

