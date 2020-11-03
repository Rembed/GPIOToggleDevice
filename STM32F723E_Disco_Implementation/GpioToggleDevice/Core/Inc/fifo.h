/**
 * File Name: fifo.h
 * Description: This file outlines the definition of a first in, first out circular buffer
 * Author: Michael Thompson (mjt106@case.edu)
 */

#pragma once

#include "stdint.h"

struct Fifo
{
	uint8_t* m_buffer;
	uint8_t m_bufferLength;
	uint8_t m_head;
	uint8_t m_tail;
};

void Fifo_init(
		struct Fifo* this,
		uint8_t* _buffer,
		uint8_t _bufferLength);

void Fifo_push(
		struct Fifo* this,
		uint8_t _byte);

uint8_t Fifo_pop(
		struct Fifo* this);

uint8_t Fifo_isEmpty(
		struct Fifo* this);
