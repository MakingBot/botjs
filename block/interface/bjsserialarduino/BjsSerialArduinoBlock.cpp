//!
//! \file BjsSerialArduinoBlock.cpp
//!
// Copyright 2015 MakingBot
// This file is part of BotJs.
//
// BotJs is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// BotJs is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with BotJs.  If not, see <http://www.gnu.org/licenses/>.

#include <BjsSerialArduinoBlock.hpp>

#include <ControllerBlock.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(BjsSerialArduinoBlock)


/* ============================================================================
 *
 * */
void BjsSerialArduinoBlock::interpret(QByteArray& array)
{
	if(array.size() != ARDUINO_MESSAGE_SIZE)
	{
		BLOCK_LOG("fail size = " << array.size()  );
		return;
	}

	CtrlMail mail;
	mail.device = (quint16)array[0];
	mail.propid = (quint8) array[1];

//	int mode = array[2];
//	mail.mode = () mode;

	array.remove(0, 3);
	array.remove(4, 4);
    mail.value  = array;

    _controllers[mail.device].toStrongRef()->newMail(mail);
}

