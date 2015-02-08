//!
//! \file LinkBlock.cpp
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

#include <LinkBlock.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(LinkBlock)

/* ============================================================================
 *
 * */
void LinkBlock::updateTransform()
{
    // Start with the identity matrix
    QMatrix4x4 new_transform;

    // Translate
    new_transform.translate(_translation.toVector3D());

    new_transform.rotate( _rotation[0], QVector3D(1, 0, 0) );
    new_transform.rotate( _rotation[1], QVector3D(0, 1, 0) );
    new_transform.rotate( _rotation[2], QVector3D(0, 0, 1) );

    // Set the new transformation
    _transform = new_transform;
}

