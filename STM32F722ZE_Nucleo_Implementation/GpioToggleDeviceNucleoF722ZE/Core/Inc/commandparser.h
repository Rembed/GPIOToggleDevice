/**
 * File Nmae: commandparser.h
 * Description: This file outlines the command structure for parsing a command
 *              and syncing the buffer
 * Author: Michael Thompson (mjt106@case.edu)
 */

#pragma once

#include "fifo.h"
#include "stdint.h"

struct CommandParser
{
	struct Fifo* m_fifo;
	uint8_t m_syncByte1;
	uint8_t m_syncByte2;

	uint8_t m_syncByte1Flag;
	uint8_t m_syncByte2Flag;
};

void CommandParser_init(
		struct CommandParser* this,
		struct Fifo* _fifo,
		uint8_t _syncByte1,
		uint8_t _syncByte2);

uint8_t CommandParser_getCommand(
		struct CommandParser* this);
