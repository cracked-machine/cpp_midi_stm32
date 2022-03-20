target_sources(${BUILD_NAME} PRIVATE
    # put source files here
    midi_stm32.cpp    
    midi_common.cpp
)

target_include_directories(${BUILD_NAME} PRIVATE 
    ../include
)