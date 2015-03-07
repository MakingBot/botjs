//!
//! \file BotBlock.cpp
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

#include <BotBlock.hpp>

// Static declaration
BotEngine BotBlock::JsEngine;

// Static declaration
quint32 BotBlock::BlockCounter;

// Static declaration
QMap<quint32, QSharedPointer<BotBlock> > BotBlock::BlockMap;

/* ============================================================================
 *
 * */
void BotBlock::GenerateIdNumber(QSharedPointer<BotBlock> block)
{
	// Set Id number
	block->setBlockIdNumber(BlockCounter);

	// Track pointer
	BlockMap[BlockCounter] = block;

	// Increment counter
	BlockCounter++;
}

/* ============================================================================
 *
 * */
QSharedPointer<BotBlock> BotBlock::IdNumberToBlock(quint32 id)
{
	return BlockMap[id];
}

/* ============================================================================
 *
 * */
QString BotBlock::JsString(const QString& string)
{
    return QString("'") + string + QString("'");
}

/* ============================================================================
 *
 * */
QString BotBlock::JsIProperty(const QString& property_name)
{
    QString jsline;
    QTextStream stream(&jsline);

    // Get the id
    quint8 id = _iPropIds[property_name];

    // Get the property
    const IProperty& prop = _iProperties[id];

    // Append the name
    stream << "." << property_name << " = ";

    // Set the property in function of the type
    switch( prop.type() )
    {
        case IProperty::IPTypeBool         :
        {
            bool value = this->property(property_name.toStdString().c_str()).toBool();
            if( value )
            {
                stream << "true;";
            }
            else
            {
                stream << "false;";
            }
            break;
        }
        
        case IProperty::IPTypeInt          :
        {
            break;   
        }
        case IProperty::IPTypeReal         :
        {
            break;   
        }
        case IProperty::IPTypeString       :
        {
            break;   
        }
        case IProperty::IPTypeEnum         :
        {
            break;   
        }
        case IProperty::IPTypeBlock        :
        {
            break;   
        }
        case IProperty::IPTypeSonBlock     :
        {
            break;   
        }
        case IProperty::IPTypeBrotherBlock :
        {
            break;   
        }
        case IProperty::IPTypeRealList     :
        {
            break;   
        }
        case IProperty::IPTypeVector3D     :
        {
            break;   
        }
        case IProperty::IPTypeVector4D     :
        {
            break;   
        }
        case IProperty::IPTypeMatrix44     :
        {
            break;   
        }
    }

    // End
    stream << endl;
    return jsline;
}
