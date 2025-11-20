add_library(utils STATIC)
target_include_directories(utils PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/include
)
target_sources(utils PUBLIC
	utils.c
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE utils)
