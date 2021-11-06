add_executable(game_app game_app.cpp)
# target_compile_features(game_app PRIVATE cxx_std_17)

target_link_libraries(game_app PRIVATE game_lib)
