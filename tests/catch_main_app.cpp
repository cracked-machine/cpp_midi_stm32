#include <catch2/catch_all.hpp>
#include <midi_stm32.hpp>

TEST_CASE("Test MIDI STM32", "[MIDI STM32]")
{
    USART5 = new USART_TypeDef;
	// The USART and Timer used to send the MIDI heartbeat
	midi_stm32::DeviceInterface<STM32G0_ISR> midi_usart_interface(
		USART5,
		STM32G0_ISR::usart5
	);	

    midi_stm32::Driver d(midi_usart_interface);

    REQUIRE(true);
}