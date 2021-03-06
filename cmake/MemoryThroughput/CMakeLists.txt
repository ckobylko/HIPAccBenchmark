SET(PROJECT_NAME "MemoryThroughput")

SET(PROJECT_HEADER_DIR "../../include/${PROJECT_NAME}/")
SET(PROJECT_SOURCE_DIR "../../src/${PROJECT_NAME}/")

# Add source files
SET(PROJECT_SOURCES "${PROJECT_SOURCE_DIR}/AVX_Routines.cpp"
                    "${PROJECT_SOURCE_DIR}/MemoryThroughput.cpp"
                    "${PROJECT_SOURCE_DIR}/SSE_Routines.cpp"
                    "${PROJECT_SOURCE_DIR}/TestRead.cpp"
                    "${PROJECT_SOURCE_DIR}/TestWrite.cpp")


# Add header files
SET(PROJECT_HEADERS_PUBLIC  "${PROJECT_HEADER_DIR}/MemoryThroughput.h")
SET(PROJECT_HEADERS_PRIVATE "${PROJECT_SOURCE_DIR}/TestRead.h"
                            "${PROJECT_SOURCE_DIR}/TestWrite.h")

SET(PROJECT_HEADERS         "${PROJECT_HEADERS_PUBLIC}" "${PROJECT_HEADERS_PRIVATE}")

SET_SOURCE_FILES_PROPERTIES("${PROJECT_SOURCE_DIR}/AVX_Routines.cpp" PROPERTIES COMPILE_FLAGS ${CPP_COMP_FLAG_AVX})


ADD_LIBRARY(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

SOURCE_GROUP(${SOURCE_GROUP_HEADER_FILES}        FILES ${PROJECT_HEADERS_PRIVATE})
SOURCE_GROUP(${SOURCE_GROUP_PUBLIC_HEADER_FILES} FILES ${PROJECT_HEADERS_PUBLIC})
SOURCE_GROUP(${SOURCE_GROUP_SOURCE_FILES}        FILES ${PROJECT_SOURCES})
