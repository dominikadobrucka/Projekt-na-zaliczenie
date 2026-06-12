cmake_minimum_required(VERSION 3.24)
project(GraSFML CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Pobieranie SFML
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
)
FetchContent_MakeAvailable(SFML)

file(GLOB SOURCES *.cpp *.h)

add_executable(MojaGra ${SOURCES})

target_link_libraries(MojaGra PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

target_include_directories(MojaGra PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    add_custom_command(TARGET MojaGra POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${sfml_BINARY_DIR}/lib"
        "$<TARGET_FILE_DIR:MojaGra>"
    )
    
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/grafiki DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dzwieki DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/grafiki DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dzwieki DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
