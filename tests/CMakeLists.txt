target_sources(${BUILD_NAME} PRIVATE
    catch_main_app.cpp
)

target_include_directories(${BUILD_NAME} PRIVATE 
    .
    # cloned using external.cmake
    ${CMAKE_BINARY_DIR}/embedded_utils/include
    ${CMAKE_BINARY_DIR}/stm32_interrupt_managers/include
)
