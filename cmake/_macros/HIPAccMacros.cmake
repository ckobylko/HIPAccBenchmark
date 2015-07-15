macro(ADD_HIPACC_SOURCE PIXEL_TYPE VECTORIZATION_TYPE)
    IF(${PIXEL_TYPE} STREQUAL ${SUFFIX_TYPE_FLOAT})
        SET(VAR_NAME_PIXEL_TYPE "FLOAT")
    ELSEIF(${PIXEL_TYPE} STREQUAL ${SUFFIX_TYPE_UINT8})
        SET(VAR_NAME_PIXEL_TYPE "UINT8")
    ELSEIF(${PIXEL_TYPE} STREQUAL ${SUFFIX_TYPE_INT})
        SET(VAR_NAME_PIXEL_TYPE "INT")
    ELSE()
        MESSAGE(FATAL_ERROR "The pixel type suffix ${PIXEL_TYPE} is not known!")
    ENDIF()

    IF(${VECTORIZATION_TYPE} STREQUAL ${SUFFIX_VEC_SCALAR})
        SET(HIPACC_COMMAND_ARGS "")
    ELSEIF(${VECTORIZATION_TYPE} STREQUAL ${SUFFIX_VEC_SSE})
        SET(HIPACC_COMMAND_ARGS -v -i-s sse)
    ELSEIF(${VECTORIZATION_TYPE} STREQUAL ${SUFFIX_VEC_SSE2})
        SET(HIPACC_COMMAND_ARGS -v -i-s sse2)
    ELSEIF(${VECTORIZATION_TYPE} STREQUAL ${SUFFIX_VEC_SSE3})
        SET(HIPACC_COMMAND_ARGS -v -i-s sse3)
    ELSEIF(${VECTORIZATION_TYPE} STREQUAL ${SUFFIX_VEC_SSSE3})
        SET(HIPACC_COMMAND_ARGS -v -i-s ssse3)
    ELSEIF(${VECTORIZATION_TYPE} STREQUAL ${SUFFIX_VEC_SSE4_1})
        SET(HIPACC_COMMAND_ARGS -v -i-s sse4.1)
    ELSEIF(${VECTORIZATION_TYPE} STREQUAL ${SUFFIX_VEC_SSE4_2})
        SET(HIPACC_COMMAND_ARGS -v -i-s sse4.2)
    ELSEIF(${VECTORIZATION_TYPE} STREQUAL ${SUFFIX_VEC_AVX})
        SET(HIPACC_COMMAND_ARGS -v -i-s avx)
    ELSE()
        MESSAGE(FATAL_ERROR "The vectorization type suffix ${PIXEL_TYPE} is not known!")
    ENDIF()
    LIST(INSERT HIPACC_COMMAND_ARGS 0 -emit-cpu)


    SET(HIPACC_CURRENT_ROOT_NAME   "${HIPACC_NAME}${PIXEL_TYPE}")
    SET(HIPACC_CURRENT_KERNEL_NAME "${CMAKE_CURRENT_BINARY_DIR}/cc${HIPACC_CURRENT_ROOT_NAME}_${VECTORIZATION_TYPE}${SUFFIX_HIPACC_KERNEL}")
    SET(HIPACC_CURRENT_OUTPUT_NAME "${PROJECT_SOURCE_DIR}/${NAME_HIPACC_OUTPUTS}/${HIPACC_CURRENT_ROOT_NAME}${VECTORIZATION_TYPE}${SUFFIX_HIPACC_OUTPUT}")
    SET(HIPACC_CURRENT_SOURCE_NAME "${PROJECT_SOURCE_DIR}/${NAME_HIPACC_SOURCES}/${HIPACC_CURRENT_ROOT_NAME}/${HIPACC_CURRENT_ROOT_NAME}${VECTORIZATION_TYPE}.cpp")

    SET(HIPACC_KERNELS_${VAR_NAME_PIXEL_TYPE} "${HIPACC_KERNELS_${VAR_NAME_PIXEL_TYPE}}" "${HIPACC_CURRENT_KERNEL_NAME}")
    SET(HIPACC_OUTPUTS_${VAR_NAME_PIXEL_TYPE} "${HIPACC_OUTPUTS_${VAR_NAME_PIXEL_TYPE}}" "${HIPACC_CURRENT_OUTPUT_NAME}")
    SET(HIPACC_SOURCES_${VAR_NAME_PIXEL_TYPE} "${HIPACC_SOURCES_${VAR_NAME_PIXEL_TYPE}}" "${HIPACC_CURRENT_SOURCE_NAME}")

    ADD_CUSTOM_COMMAND(OUTPUT "${HIPACC_CURRENT_OUTPUT_NAME}" "${HIPACC_CURRENT_KERNEL_NAME}"
                       COMMAND "${HIPACC_INSTALL_PATH}/bin/hipacc.exe" ${HIPACC_COMMAND_ARGS} -o "${HIPACC_CURRENT_OUTPUT_NAME}" "${HIPACC_CURRENT_SOURCE_NAME}"
                       MAIN_DEPENDENCY "${HIPACC_CURRENT_SOURCE_NAME}"
                       WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
endmacro()


macro(MERGE_HIPACC_SOURCES PIXEL_TYPE)
   IF(${PIXEL_TYPE} STREQUAL ${SUFFIX_TYPE_FLOAT})
        SET(VAR_NAME_PIXEL_TYPE "FLOAT")
    ELSEIF(${PIXEL_TYPE} STREQUAL ${SUFFIX_TYPE_UINT8})
        SET(VAR_NAME_PIXEL_TYPE "UINT8")
    ELSEIF(${PIXEL_TYPE} STREQUAL ${SUFFIX_TYPE_INT})
        SET(VAR_NAME_PIXEL_TYPE "INT")
    ELSE()
        MESSAGE(FATAL_ERROR "The pixel type suffix ${PIXEL_TYPE} is not known!")
    ENDIF()

    SET(HIPACC_CURRENT_ROOT_NAME              "${HIPACC_NAME}${PIXEL_TYPE}")
    SET(HIPACC_SOURCES_${VAR_NAME_PIXEL_TYPE} "${HIPACC_SOURCES_${VAR_NAME_PIXEL_TYPE}}"
                                              "${PROJECT_SOURCE_DIR}/${NAME_HIPACC_SOURCES}/${HIPACC_CURRENT_ROOT_NAME}/${HIPACC_CURRENT_ROOT_NAME}${SUFFIX_DEFINES}.h")

    SET_SOURCE_FILES_PROPERTIES(${HIPACC_KERNELS_${VAR_NAME_PIXEL_TYPE}} PROPERTIES HEADER_FILE_ONLY TRUE GENERATED TRUE) 
    SET_SOURCE_FILES_PROPERTIES(${HIPACC_OUTPUTS_${VAR_NAME_PIXEL_TYPE}} PROPERTIES HEADER_FILE_ONLY TRUE GENERATED TRUE) 

    SET(HIPACC_KERNELS "${HIPACC_KERNELS}" "${HIPACC_KERNELS_${VAR_NAME_PIXEL_TYPE}}")
    SET(HIPACC_OUTPUTS "${HIPACC_OUTPUTS}" "${HIPACC_OUTPUTS_${VAR_NAME_PIXEL_TYPE}}")
    SET(HIPACC_SOURCES "${HIPACC_SOURCES}" "${HIPACC_SOURCES_${VAR_NAME_PIXEL_TYPE}}")

    SOURCE_GROUP("${SOURCE_GROUP_HIPACC_KERNELS}\\${HIPACC_NAME}${PIXEL_TYPE}" FILES ${HIPACC_KERNELS_${VAR_NAME_PIXEL_TYPE}})
    SOURCE_GROUP("${SOURCE_GROUP_HIPACC_OUTPUTS}\\${HIPACC_NAME}${PIXEL_TYPE}" FILES ${HIPACC_OUTPUTS_${VAR_NAME_PIXEL_TYPE}})
    SOURCE_GROUP("${SOURCE_GROUP_HIPACC_SOURCES}\\${HIPACC_NAME}${PIXEL_TYPE}" FILES ${HIPACC_SOURCES_${VAR_NAME_PIXEL_TYPE}})
endmacro()

macro(MERGE_ALL_HIPACC_FILES)
    MERGE_HIPACC_SOURCES(${SUFFIX_TYPE_FLOAT})
    MERGE_HIPACC_SOURCES(${SUFFIX_TYPE_UINT8})

    SET(HIPACC_GENERIC_SOURCE "${PROJECT_SOURCE_DIR}/${NAME_HIPACC_SOURCES}/${HIPACC_NAME}${SUFFIX_GENERIC}.hxx")
    SET(HIPACC_SOURCES        "${HIPACC_SOURCES}" "${HIPACC_GENERIC_SOURCE}")
    SOURCE_GROUP("${SOURCE_GROUP_HIPACC_SOURCES}" FILES ${HIPACC_GENERIC_SOURCE})

    SET(HIPACC_FILES "${HIPACC_KERNELS}" "${HIPACC_OUTPUTS}" "${HIPACC_SOURCES}")
endmacro()