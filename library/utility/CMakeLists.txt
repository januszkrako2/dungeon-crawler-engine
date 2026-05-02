add_library(utility STATIC)
target_include_directories(utility PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/include
)
target_sources(utility PUBLIC
	utility.c
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE utility)
