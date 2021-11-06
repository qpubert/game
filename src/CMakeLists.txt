# Make an automatic library - will be static or dynamic based on user setting
add_library(game_lib game.cpp tilemap.cpp tileset.cpp)

# We need this directory, and users of our library will need it too
target_include_directories(game_lib PUBLIC ../include)

# This depends on SFML
target_link_libraries(game_lib
    PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# All users of this library will need at least C++11
target_compile_features(game_lib PUBLIC cxx_std_11)
