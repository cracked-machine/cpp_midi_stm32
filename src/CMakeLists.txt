target_sources(${BUILD_NAME} PRIVATE
    midi_stm32.cpp    
    midi_stm32_common.cpp
)

target_include_directories(${BUILD_NAME} PRIVATE 
    ../include
)