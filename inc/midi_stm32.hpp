// MIT License

// Copyright (c) 2021 Chris Sutton

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#ifndef __MIDI_STM32_HPP__
#define __MIDI_STM32_HPP__

#include <midi_stm32_device.hpp>
#include <midi_stm32_types.hpp>

namespace midi_stm32 
{

class Driver : public AllocationRestrictedBase
{
public:
	Driver(DeviceInterface &midi_usart_interface);
	void set_tempo_bpm(uint8_t bpm);

	// @brief Send a MIDI System Real-Time Start cmd
	// and begin master heartbeat timer
	void send_realtime_start_msg();
	// @brief Send a MIDI System Real-Time Stop cmd
	// and stop master heartbeat timer
	void send_realtime_stop_msg();
	// @brief Send a MIDI System Real-Time clock cmd
	void send_realtime_clock_msg();

	/// @brief Send MIDI note on/off command
	/// @tparam NOTE_CMD This must be of type midi_stm32::NoteOn or midi_stm32::NoteOff
	/// @param cmd The note on/off command combined with the channel
	/// @param note The note pitch
	/// @param velocity The note velocity
	/// @note see https://godbolt.org/z/YW3K6jer7 for example usage
	template<typename NOTE_CMD>
	void send_note_cmd(NOTE_CMD cmd, Note note, uint8_t velocity);
	

private:

	// object containing pointer to USART/TIMER peripherals and GPIO pins
    DeviceInterface m_midi_interface;

	// std::array<uint8_t, 3> m_midi_pkt;

	// @brief Helper to register USART callback from STM32G0InterruptManager
	struct UsartIntHandler : public stm32::isr::STM32G0InterruptManager
	{
        // @brief the parent manager class
        Driver *m_midi_driver_ptr;
		// @brief Register Driver with STM32G0InterruptManager
		// @param midi_driver_ptr the manager instance to register
		void register_midi_driver(Driver *midi_driver_ptr)
		{
			m_midi_driver_ptr = midi_driver_ptr;
			// register this internal handler class in stm32::isr::STM32G0InterruptManager
			stm32::isr::STM32G0InterruptManager::register_handler(
				m_midi_driver_ptr->m_midi_interface.get_usart_isr_type(), 
				this);
		}        
        // @brief The callback used by STM32G0InterruptManager
		virtual void ISR()
		{
            m_midi_driver_ptr->midi_usart_isr();
		}        
	};

	// @brief Helper to register TIMER callback from STM32G0InterruptManager
	struct TimIntHandler : public stm32::isr::STM32G0InterruptManager
	{
		// reference to parent class: midi_stm32::Driver
		Driver *m_midi_driver_ptr;

		void initialise_isr(Driver *midi_driver_ptr)
		{
			m_midi_driver_ptr = midi_driver_ptr;
			stm32::isr::STM32G0InterruptManager::register_handler(
				m_midi_driver_ptr->m_midi_interface.get_tim_isr_type(),
				this);
		}
		virtual void ISR()
		{
			m_midi_driver_ptr->midi_tim_isr();
		}
	};

	// @brief UsartIntHandler instance
    UsartIntHandler m_midi_usart_isr_handler;
	// @brief TimIntHandler instance
	TimIntHandler m_midi_tim_isr_handler;

    // @brief function called back by UsartIntHandler->ISR()
    void midi_usart_isr();
	// @brief function called back by TimIntHandler->ISR()
	void midi_tim_isr();

};

} // namespace midi_stm32 

#endif // __MIDI_STM32_HPP__