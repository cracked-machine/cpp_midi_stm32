// MIT License

// Copyright (c) 2022 Chris Sutton

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

#include <midi_stm32_common.hpp>
// disable dynamic allocation/copying
#include <restricted_base.hpp>
#include <isr_manager_stm32g0.hpp>

namespace midi_stm32 
{

template<typename DEVICE_ISR_ENUM>
class Driver : public RestrictedBase, public CommonFunctions
{
public:
	// cppcheck-suppress uninitMemberVar - m_midi_usart_isr_handler not fully enabled yet (https://github.com/cracked-machine/cpp_midi_stm32/issues/2)
	explicit Driver(const DeviceInterface<DEVICE_ISR_ENUM> &midi_interface)
	:   m_midi_interface(midi_interface)
	{
		stm32::usart::enable_usart(m_midi_interface.get_usart_handle());
	}	

	void send_realtime_start_msg()
	{
		// Send the MIDI Start msg
		stm32::usart::transmit_byte(
			m_midi_interface.get_usart_handle(), 
			static_cast<uint8_t>(SystemRealTimeMessages::Start)
		);
	}

	void send_realtime_stop_msg()
	{
		// Send the MIDI Stop msg
		stm32::usart::transmit_byte(
			m_midi_interface.get_usart_handle(), 
			static_cast<uint8_t>(SystemRealTimeMessages::Stop)
		);
	}

	void send_realtime_continue_msg()
	{
		// Send the MIDI Stop msg
		stm32::usart::transmit_byte(
			m_midi_interface.get_usart_handle(), 
			static_cast<uint8_t>(SystemRealTimeMessages::Continue)
		);
	}	

	void send_realtime_clock_msg()
	{
		stm32::usart::transmit_byte(
			m_midi_interface.get_usart_handle(), 
			static_cast<uint8_t>(SystemRealTimeMessages::TimingClock)
		);
	}

	template<typename NOTE_CMD>
	void send_note_cmd(NOTE_CMD cmd, Note note, uint8_t velocity)
	{
		if constexpr ((std::is_same_v<NOTE_CMD, midi_stm32::NoteOn>) ||
					(std::is_same_v<NOTE_CMD, midi_stm32::NoteOff>))  
		{    
			// check the TC and BSY flags and use an appropriate delay if waiting on one of these flags
			uint16_t delay_us {250};

			stm32::usart::wait_for_tc_flag(m_midi_interface.get_usart_handle(), delay_us);
			stm32::usart::wait_for_bsy_flag(m_midi_interface.get_usart_handle(), delay_us);
			stm32::usart::transmit_byte(
				m_midi_interface.get_usart_handle(), 
				static_cast<uint8_t>(cmd)
			);

			stm32::usart::wait_for_tc_flag(m_midi_interface.get_usart_handle(), delay_us);
			stm32::usart::wait_for_bsy_flag(m_midi_interface.get_usart_handle(), delay_us);
			stm32::usart::transmit_byte(
				m_midi_interface.get_usart_handle(), 
				static_cast<uint8_t>(note)
			);

			stm32::usart::wait_for_tc_flag(m_midi_interface.get_usart_handle(), delay_us);
			stm32::usart::wait_for_bsy_flag(m_midi_interface.get_usart_handle(), delay_us);
			stm32::usart::transmit_byte(
				m_midi_interface.get_usart_handle(), 
				static_cast<uint8_t>(velocity)
			);
		}
		else
		{
			// invalid NOTE_CMD type used!
		}

	}

private:

	// @brief Helper to register USART callback from InterruptManagerStm32g0
	struct UsartIntHandler : public stm32::isr::InterruptManagerStm32Base<DEVICE_ISR_ENUM>
	{
        // @brief the parent manager class
        Driver *m_midi_driver_ptr;
		// @brief Register Driver with InterruptManagerStm32g0
		// @param midi_driver_ptr the manager instance to register
		void register_midi_driver(Driver *midi_driver_ptr)
		{
			m_midi_driver_ptr = midi_driver_ptr;
			// register this internal handler class in stm32::isr::InterruptManagerStm32g0
			stm32::isr::InterruptManagerStm32Base<DEVICE_ISR_ENUM>::register_handler(
				m_midi_driver_ptr->m_midi_interface.get_usart_isr_type(), 
				this);
		}        
        // @brief Definition of InterruptManagerStm32Base::ISR. This is called by stm32::isr::InterruptManagerStm32Base<DEVICE_ISR_ENUM> specialization 
		virtual void ISR()
		{
            m_midi_driver_ptr->midi_usart_isr();
		}        
	};

	// @brief UsartIntHandler instance
    UsartIntHandler m_midi_usart_isr_handler;

    // @brief function called back by UsartIntHandler->ISR()
    void midi_usart_isr()
	{
		// not implemented
	}


	// object containing pointer to USART/TIMER peripherals and GPIO pins
    DeviceInterface<DEVICE_ISR_ENUM> m_midi_interface;	

};

} // namespace midi_stm32 

#endif // __MIDI_STM32_HPP__