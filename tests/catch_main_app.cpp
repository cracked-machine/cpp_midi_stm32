#include <catch2/catch_all.hpp>
#include <midi_stm32.hpp>


// enforce code coverage with explicit instances of func templates so that linker does not drop references
enum class DummyInterruptType { usart5, capacity };
template midi_stm32::Driver<DummyInterruptType>::Driver(const DeviceInterface<DummyInterruptType> &midi_interface);
template void midi_stm32::Driver<DummyInterruptType>::send_realtime_start_msg();
template void midi_stm32::Driver<DummyInterruptType>::send_realtime_stop_msg();
template void midi_stm32::Driver<DummyInterruptType>::send_realtime_continue_msg();
template void midi_stm32::Driver<DummyInterruptType>::send_realtime_clock_msg();
template void midi_stm32::Driver<DummyInterruptType>::send_note_cmd(midi_stm32::NoteOn cmd, Note note, uint8_t velocity);
template midi_stm32::DeviceInterface<DummyInterruptType>::DeviceInterface(USART_TypeDef *midi_usart, DummyInterruptType usart_isr_type);
template USART_TypeDef* midi_stm32::DeviceInterface<DummyInterruptType>::get_usart_handle();
template DummyInterruptType midi_stm32::DeviceInterface<DummyInterruptType>::get_usart_isr_type();

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