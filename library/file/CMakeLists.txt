add_library(file STATIC)
target_include_directories(file PUBLIC
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}
)
target_sources(file PUBLIC
	file.c
)
target_link_libraries(file PRIVATE utility)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE file)
