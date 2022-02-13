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

#include <midi_stm32.hpp>
#include <usart_utils.hpp>

namespace midi_stm32 
{

Driver::Driver(DeviceInterface &midi_interface)
:   m_midi_interface(midi_interface)
{
    m_midi_tim_isr_handler.initialise_isr(this);
    LL_USART_Enable(m_midi_interface.get_usart_handle());
}

void Driver::set_tempo_bpm(uint8_t bpm)
{
    m_midi_interface.get_tim_handle()->PSC = bpm;
}

void Driver::send_realtime_start_msg()
{
    LL_USART_TransmitData8(m_midi_interface.get_usart_handle(), static_cast<uint8_t>(SystemRealTimeMessages::Start));
    LL_TIM_EnableCounter(m_midi_interface.get_tim_handle());
    LL_TIM_EnableIT_UPDATE(m_midi_interface.get_tim_handle());
}

void Driver::send_realtime_stop_msg()
{
    LL_TIM_DisableIT_UPDATE(m_midi_interface.get_tim_handle());
    LL_TIM_DisableCounter(m_midi_interface.get_tim_handle());
    LL_USART_TransmitData8(m_midi_interface.get_usart_handle(), static_cast<uint8_t>(SystemRealTimeMessages::Stop));
}

void Driver::send_realtime_clock_msg()
{
    LL_USART_TransmitData8(m_midi_interface.get_usart_handle(), static_cast<uint8_t>(SystemRealTimeMessages::TimingClock));
}

template<typename NOTE_CMD>
void Driver::send_note_cmd(NOTE_CMD cmd, Note note, uint8_t velocity)
{
    if constexpr ((std::is_same_v<NOTE_CMD, midi_stm32::NoteOn>) ||
                  (std::is_same_v<NOTE_CMD, midi_stm32::NoteOff>))  
    {    
        // check the TC and BSY flags and use an appropriate delay if waiting on one of these flags
        uint16_t delay_us {250};

        stm32::usart::wait_for_tc_flag(m_midi_interface.get_usart_handle(), delay_us);
        stm32::usart::wait_for_bsy_flag(m_midi_interface.get_usart_handle(), delay_us);
        LL_USART_TransmitData8(m_midi_interface.get_usart_handle(), static_cast<uint8_t>(cmd));

        stm32::usart::wait_for_tc_flag(m_midi_interface.get_usart_handle(), delay_us);
        stm32::usart::wait_for_bsy_flag(m_midi_interface.get_usart_handle(), delay_us);
        LL_USART_TransmitData8(m_midi_interface.get_usart_handle(), static_cast<uint8_t>(note));

        stm32::usart::wait_for_tc_flag(m_midi_interface.get_usart_handle(), delay_us);
        stm32::usart::wait_for_bsy_flag(m_midi_interface.get_usart_handle(), delay_us);
        LL_USART_TransmitData8(m_midi_interface.get_usart_handle(), static_cast<uint8_t>(velocity));
    }
    else
    {
        // invalid NOTE_CMD type used!
    }

}


void Driver::midi_usart_isr()
{
	// if ((m_midi_interface.get_usart_handle()->ISR & USART_ISR_RXNE_RXFNE) == USART_ISR_RXNE_RXFNE)
    // {
    //     m_midi_pkt[0] = USART5->RDR; 	// grab first MIDI byte from USART
    // }
}

void Driver::midi_tim_isr()

{
    // send_realtime_clock_msg();
    send_realtime_clock_msg();
    LL_TIM_ClearFlag_UPDATE(m_midi_interface.get_tim_handle());
}

}  // namespace midi_stm32 
