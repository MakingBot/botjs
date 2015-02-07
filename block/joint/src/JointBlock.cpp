//!
//! \file JointBlock.cpp
//!
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

#include <JointBlock.hpp>
#include <LinkBlock.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(JointBlock)

/* ============================================================================
 *
 * */
void JointBlock::updateTransform()
{
    // To update a joint it must have a base link which has a base joint
    if(_baseLink)
    {
        QSharedPointer<LinkBlock> baseLink   = _baseLink.toStrongRef();
        QWeakPointer<JointBlock>  wbaseJoint = baseLink->weakBase();
        if( wbaseJoint )
        {
            QSharedPointer<JointBlock> baseJoint = wbaseJoint.toStrongRef();

            _pos = baseLink->transform() * baseJoint->pos();
        }
    }
    else
    {
        _pos = QVector4D(0,0,0,1);
    }
}
