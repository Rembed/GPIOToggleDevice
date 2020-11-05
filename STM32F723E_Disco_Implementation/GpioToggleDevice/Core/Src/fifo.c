/**
 * File Name: fifo.c
 * Description: This file outlines the definition of a first in, first out circular buffer
 * Author: Michael Thompson (mjt106@case.edu)
 */

#include "fifo.h"

void Fifo_init(
		struct Fifo* this,
		uint8_t* _buffer,
		uint32_t _bufferLength)
{
	this->m_buffer = _buffer;
	this->m_bufferLength = _bufferLength;
	this->m_head = 0;
	this->m_tail = 0;
}

void Fifo_push(
		struct Fifo* this,
		uint8_t _byte)
{
	this->m_buffer[this->m_head] = _byte;

	this->m_head = (this->m_head + 1) % this->m_bufferLength;
}

uint8_t Fifo_pop(
		struct Fifo* this)
{
	uint8_t retByte = 0x00;

	retByte = this->m_buffer[this->m_tail];
	this->m_tail = (this->m_tail + 1) % this->m_bufferLength;

	return retByte;
}

uint8_t Fifo_isEmpty(
		struct Fifo* this)
{
	return this->m_head == this->m_tail;
}
