add_executable(game_app game_app.cpp game.cpp)
target_compile_features(game_app PRIVATE cxx_std_17)

target_link_libraries(game_app PRIVATE game_lib)

target_include_directories(game_app PRIVATE ../include)

set(RESOURCE_PATH res)
target_compile_definitions(game_app PRIVATE RESOURCE_PATH="../${RESOURCE_PATH}")

add_custom_command(
    TARGET game_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${RESOURCE_PATH}
            ${CMAKE_BINARY_DIR}/${RESOURCE_PATH})



add_executable(tilemap_editor_app 
    tilemap_editor.cpp
    tilemap_editor_app.cpp
    tilemap_editor_state.cpp)
target_compile_features(game_app PRIVATE cxx_std_17)

target_link_libraries(tilemap_editor_app PRIVATE game_lib)

target_include_directories(tilemap_editor_app PRIVATE ../include)

target_compile_definitions(tilemap_editor_app PRIVATE RESOURCE_PATH="../${RESOURCE_PATH}")