add_library(game STATIC)
target_include_directories(game PUBLIC
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}
)
target_sources(game PUBLIC
	game.c
)
target_link_libraries(game PRIVATE utility)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE game)
