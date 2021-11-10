add_executable(game_app game_app.cpp)
# target_compile_features(game_app PRIVATE cxx_std_17)

target_link_libraries(game_app PRIVATE game_lib)

set(GAME_RESOURCE_PATH res)
target_compile_definitions(game_app PRIVATE RESOURCE_PATH="../${GAME_RESOURCE_PATH}")

add_custom_command(
    TARGET game_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${GAME_RESOURCE_PATH}
            ${CMAKE_BINARY_DIR}/${GAME_RESOURCE_PATH})