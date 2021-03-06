macro(ADD_ISPC_SOURCE PIXEL_TYPE VECTORIZATION_TYPE MASK_SIZE GANG_SIZE)
    IF(${PIXEL_TYPE} STREQUAL ${SUFFIX_TYPE_FLOAT})
        SET(VAR_NAME_PIXEL_TYPE "FLOAT")
    ELSEIF(${PIXEL_TYPE} STREQUAL ${SUFFIX_TYPE_UINT8})
        SET(VAR_NAME_PIXEL_TYPE "UINT8")
    ELSEIF(${PIXEL_TYPE} STREQUAL ${SUFFIX_TYPE_INT})
        SET(VAR_NAME_PIXEL_TYPE "INT")
    ELSE()
        MESSAGE(FATAL_ERROR "The pixel type suffix ${PIXEL_TYPE} is not known!")
    ENDIF()

    IF(${VECTORIZATION_TYPE} STREQUAL ${SUFFIX_VEC_SSE4_2})
        SET(ISPC_COMMAND_ARGS --target=sse4-i${MASK_SIZE}x${GANG_SIZE})
    ELSEIF(${VECTORIZATION_TYPE} STREQUAL ${SUFFIX_VEC_AVX})
        SET(ISPC_COMMAND_ARGS --target=avx1.1-i${MASK_SIZE}x${GANG_SIZE})
    ELSE()
        MESSAGE(FATAL_ERROR "The vectorization type suffix ${PIXEL_TYPE} is not known!")
    ENDIF()
    LIST(INSERT ISPC_COMMAND_ARGS 0 -O3)

    SET(ISPC_CURRENT_ROOT_NAME   "${ISPC_NAME}${PIXEL_TYPE}")
    SET(ISPC_CURRENT_HEADER_NAME "${CMAKE_CURRENT_BINARY_DIR}/${ISPC_CURRENT_ROOT_NAME}${VECTORIZATION_TYPE}.h")
    SET(ISPC_CURRENT_OUTPUT_NAME "${CMAKE_CURRENT_BINARY_DIR}/${ISPC_CURRENT_ROOT_NAME}${VECTORIZATION_TYPE}.o")
    SET(ISPC_CURRENT_SOURCE_NAME "${PROJECT_SOURCE_DIR}/${NAME_ISPC_SOURCES}/${ISPC_CURRENT_ROOT_NAME}/${ISPC_CURRENT_ROOT_NAME}${VECTORIZATION_TYPE}.ispc")

    SET(ISPC_HEADERS_${VAR_NAME_PIXEL_TYPE} "${ISPC_HEADERS_${VAR_NAME_PIXEL_TYPE}}" "${ISPC_CURRENT_HEADER_NAME}")
    SET(ISPC_OUTPUTS_${VAR_NAME_PIXEL_TYPE} "${ISPC_OUTPUTS_${VAR_NAME_PIXEL_TYPE}}" "${ISPC_CURRENT_OUTPUT_NAME}")
    SET(ISPC_SOURCES_${VAR_NAME_PIXEL_TYPE} "${ISPC_SOURCES_${VAR_NAME_PIXEL_TYPE}}" "${ISPC_CURRENT_SOURCE_NAME}")

    ADD_CUSTOM_COMMAND(OUTPUT "${ISPC_CURRENT_OUTPUT_NAME}" "${ISPC_CURRENT_HEADER_NAME}"
                       COMMAND "${ISPC_EXECUTABLE_PATH}" ${ISPC_COMMAND_ARGS} -o "${ISPC_CURRENT_OUTPUT_NAME}" -h "${ISPC_CURRENT_HEADER_NAME}" "${ISPC_CURRENT_SOURCE_NAME}"
                       MAIN_DEPENDENCY "${ISPC_CURRENT_SOURCE_NAME}"
                       WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
endmacro()


macro(MERGE_ISPC_SOURCES PIXEL_TYPE)
   IF(${PIXEL_TYPE} STREQUAL ${SUFFIX_TYPE_FLOAT})
        SET(VAR_NAME_PIXEL_TYPE "FLOAT")
    ELSEIF(${PIXEL_TYPE} STREQUAL ${SUFFIX_TYPE_UINT8})
        SET(VAR_NAME_PIXEL_TYPE "UINT8")
    ELSEIF(${PIXEL_TYPE} STREQUAL ${SUFFIX_TYPE_INT})
        SET(VAR_NAME_PIXEL_TYPE "INT")
    ELSE()
        MESSAGE(FATAL_ERROR "The pixel type suffix ${PIXEL_TYPE} is not known!")
    ENDIF()

    SET_SOURCE_FILES_PROPERTIES(${ISPC_HEADERS_${VAR_NAME_PIXEL_TYPE}} PROPERTIES HEADER_FILE_ONLY TRUE GENERATED TRUE) 
    SET_SOURCE_FILES_PROPERTIES(${ISPC_OUTPUTS_${VAR_NAME_PIXEL_TYPE}} PROPERTIES EXTERNAL_OBJECT TRUE GENERATED TRUE) 

    SET(ISPC_HEADERS "${ISPC_HEADERS}" "${ISPC_HEADERS_${VAR_NAME_PIXEL_TYPE}}")
    SET(ISPC_OUTPUTS "${ISPC_OUTPUTS}" "${ISPC_OUTPUTS_${VAR_NAME_PIXEL_TYPE}}")
    SET(ISPC_SOURCES "${ISPC_SOURCES}" "${ISPC_SOURCES_${VAR_NAME_PIXEL_TYPE}}")

    SOURCE_GROUP("ISPC\\${ISPC_NAME}${PIXEL_TYPE}" FILES ${ISPC_HEADERS_${VAR_NAME_PIXEL_TYPE}})
    SOURCE_GROUP("ISPC\\${ISPC_NAME}${PIXEL_TYPE}" FILES ${ISPC_OUTPUTS_${VAR_NAME_PIXEL_TYPE}})
    SOURCE_GROUP("ISPC\\${ISPC_NAME}${PIXEL_TYPE}" FILES ${ISPC_SOURCES_${VAR_NAME_PIXEL_TYPE}})
endmacro()

macro(MERGE_ALL_ISPC_FILES)
    IF(NOT "${ISPC_SOURCES_FLOAT}" STREQUAL "")
        MERGE_ISPC_SOURCES(${SUFFIX_TYPE_FLOAT})
    ENDIF()

    IF(NOT "${ISPC_SOURCES_UINT8}" STREQUAL "")
        MERGE_ISPC_SOURCES(${SUFFIX_TYPE_UINT8})
    ENDIF()

    IF(NOT "${ISPC_SOURCES_INT}" STREQUAL "")
        MERGE_ISPC_SOURCES(${SUFFIX_TYPE_INT})
    ENDIF()

    SET(ISPC_GENERIC_SOURCE "${PROJECT_SOURCE_DIR}/${NAME_ISPC_SOURCES}/${ISPC_NAME}${SUFFIX_GENERIC}.hxx")
    SET(ISPC_SOURCES        "${ISPC_SOURCES}" "${ISPC_GENERIC_SOURCE}")
    SOURCE_GROUP("ISPC" FILES ${ISPC_GENERIC_SOURCE})

    SET(ISPC_FILES "${ISPC_HEADERS}" "${ISPC_OUTPUTS}" "${ISPC_SOURCES}")
endmacro()