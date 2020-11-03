/**
 * File Nmae: commandparser.h
 * Description: This file outlines the command structure for parsing a command
 *              and syncing the buffer
 * Author: Michael Thompson (mjt106@case.edu)
 */

#include "commandparser.h"

void CommandParser_init(
		struct CommandParser* this,
		struct Fifo* _fifo,
		uint8_t _syncByte1,
		uint8_t _syncByte2)
{
	this->m_fifo = _fifo;
	this->m_syncByte1 = _syncByte1;
	this->m_syncByte2 = _syncByte2;

	this->m_syncByte1Flag = 0;
	this->m_syncByte2Flag = 0;
}


uint8_t CommandParser_getCommand(
		struct CommandParser* this)
{
	uint8_t byte;
	if(!Fifo_isEmpty(this->m_fifo))
	{
		byte = Fifo_pop(this->m_fifo);

		if(byte == this->m_syncByte1
				&& !this->m_syncByte1Flag)
		{
			this->m_syncByte1Flag = 1;
		}

		else if(byte == this->m_syncByte2
				&& this->m_syncByte1Flag
				&& !this->m_syncByte2Flag)
		{
			this->m_syncByte2Flag = 1;
		}

		else if(this->m_syncByte1Flag && this->m_syncByte2Flag)
		{
			this->m_syncByte1Flag = 0;
			this->m_syncByte2Flag = 0;
			return byte;
		}

		else
		{
			this->m_syncByte1Flag = 0;
			this->m_syncByte2Flag = 0;
		}

		return 0;
	}
}
