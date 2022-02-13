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


#ifndef __MIDI_STM32_TYPE_HPP__
#define __MIDI_STM32_TYPE_HPP__

namespace midi_stm32
{

// @brief Definitions for MIDI System Real-Time
enum class SystemRealTimeMessages
{
	TimingClock = 	0xF8,
	Start		=	0xFA,
	Continue	= 	0xFB,
	Stop		= 	0xFC,
	ActiveSense	= 	0xFE,
	Reset		= 	0xFF,
};

enum class NoteOn
{
	Ch1			= 	0x90,
	Ch2			= 	0x91,
	Ch3			= 	0x92,
	Ch4			= 	0x93,
	Ch5			= 	0x94,
	Ch6			= 	0x95,
	Ch7			= 	0x96,
	Ch8			= 	0x97,
	Ch9			= 	0x98,
	Ch10		= 	0x99,
	Ch11		= 	0x9A,
	Ch12		= 	0x9B,
	Ch13		= 	0x9C,
	Ch14		= 	0x9D,
	Ch15		= 	0x9E,
	Ch16		= 	0x9F,
};

enum class NoteOff
{
	Ch1			= 	0x80,
	Ch2			= 	0x81,
	Ch3			= 	0x82,
	Ch4			= 	0x83,
	Ch5			= 	0x84,
	Ch6			= 	0x85,
	Ch7			= 	0x86,
	Ch8			= 	0x87,
	Ch9			= 	0x88,
	Ch10		= 	0x89,
	Ch11		= 	0x8A,
	Ch12		= 	0x8B,
	Ch13		= 	0x8C,
	Ch14		= 	0x8D,
	Ch15		= 	0x8E,
	Ch16		= 	0x8F,
};

enum class Note
{
	G9			=	0x7F,
	F_sharp9	=	0x7E,
	F9			=	0x7D,
	E9			=	0x7C,
	D_sharp9	=	0x7B,
	D9			=	0x7A,
	C_sharp9	=	0x79,
	C9			=	0x78,
	B8			=	0x77,
	A_sharp8	=	0x76,
	A8			=	0x75,
	G_sharp8	=	0x74,
	G8			=	0x73,
	F_sharp8	=	0x72,
	F8			=	0x71,
	E8			=	0x70,
	D_sharp8	=	0x6F,
	D8			=	0x6E,
	C_sharp8	=	0x6D,
	C8			=	0x6C,
	B7			=	0x6B,
	A_sharp7	=	0x6A,
	A7			=	0x69,
	G_sharp7	=	0x68,
	G7			=	0x67,
	F_sharp7	=	0x66,
	F7			=	0x65,
	E7			=	0x64,
	D_sharp7	=	0x63,
	D7			=	0x62,
	C_sharp7	=	0x61,
	C7			=	0x60,
	B6			=	0x5F,
	A_sharp6	=	0x5E,
	A6			=	0x5D,
	G_sharp6	=	0x5C,
	G6			=	0x5B,
	F_sharp6	=	0x5A,
	F6			=	0x59,
	E6			=	0x58,
	D_sharp6	=	0x57,
	D6			=	0x56,
	C_sharp6	=	0x55,
	C6			=	0x54,
	B5			=	0x53,
	A_sharp5	=	0x52,
	A5			=	0x51,
	G_sharp5	=	0x50,
	G5			=	0x4F,
	F_sharp5	=	0x4E,
	F5			=	0x4D,
	E5			=	0x4C,
	D_sharp5	=	0x4B,
	D5			=	0x4A,
	C_sharp5	=	0x49,
	C5			=	0x48,
	B4			=	0x47,
	A_sharp4	=	0x46,
	A4			=	0x45,
	G_sharp4	=	0x44,
	G4			=	0x43,
	F_sharp4	=	0x42,
	F4			=	0x41,
	E4			=	0x40,
	D_sharp4	=	0x3F,
	D4			=	0x3E,
	C_sharp4	=	0x3D,
	C4			=	0x3C,
	B3			=	0x3B,
	A_sharp3	=	0x3A,
	A3			=	0x39,
	G_sharp3	=	0x38,
	G3			=	0x37,
	F_sharp3	=	0x36,
	F3			=	0x35,
	E3			=	0x34,
	D_sharp3	=	0x33,
	D3			=	0x32,
	C_sharp3	=	0x31,
	C3			=	0x30,
	B2			=	0x2F,
	A_sharp2	=	0x2E,
	A2			=	0x2D,
	G_sharp2	=	0x2C,
	G2			=	0x2B,
	F_sharp2	=	0x2A,
	F2			=	0x29,
	E2			=	0x28,
	D_sharp2	=	0x27,
	D2			=	0x26,
	C_sharp2	=	0x25,
	C2			=	0x24,
	B1			=	0x23,
	A_sharp1	=	0x22,
	A1			=	0x21,
	G_sharp1	=	0x20,
	G1			=	0x1F,
	F_sharp1	=	0x1E,
	F1			=	0x1D,
	E1			=	0x1C,
	D_sharp1	=	0x1B,
	D1			=	0x1A,
	C_sharp1	=	0x19,
	C1			=	0x18,
	B0			=	0x17,
	A_sharp0	=	0x16,
	A0			=	0x15,
};

} // namespace midi_stm32


#endif // __MIDI_STM32_TYPE_HPP__