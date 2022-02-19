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


#ifndef __MIDI_STM32_DRIVER_HPP__
#define __MIDI_STM32_DRIVER_HPP__

#include <stm32g0_interrupt_manager.hpp>
// disable dynamic allocation/copying
#include <allocation_restricted_base.hpp>


#if defined(X86_UNIT_TESTING_ONLY)
	// only used when unit testing on x86
	#include <mock_cmsis.hpp>
	#include <iostream>
#else
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wvolatile"
		#include "main.h"
		#include "usart.h"	
	#pragma GCC diagnostic pop
    
#endif

namespace midi_stm32 
{

class DeviceInterface
{
public:
	DeviceInterface(
		USART_TypeDef *midi_usart, 
		stm32::isr::STM32G0InterruptManager::InterruptType usart_isr_type)
	:	m_midi_usart(midi_usart),
		m_usart_isr_type(usart_isr_type)
	{}

	USART_TypeDef* get_usart_handle() { return m_midi_usart; }
	stm32::isr::STM32G0InterruptManager::InterruptType get_usart_isr_type() { return m_usart_isr_type; }

private:
	USART_TypeDef *m_midi_usart;
	stm32::isr::STM32G0InterruptManager::InterruptType m_usart_isr_type;


};

} // namespace midi_stm32 
    

#endif // __MIDI_STM32_DRIVER_HPP__