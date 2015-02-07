#ifndef LINKBLOCK_HPP
#define LINKBLOCK_HPP
//!
//! \file LinkBlock.hpp
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

#include <BotBlock.hpp>

#include <QMatrix4x4>

//class JointBlock;

//!
//! Fixe transformation between 2 joints
//! The link between 2 motors of a robot arm for example
//!
class LinkBlock : public BotBlock
{
    Q_OBJECT
    // Q_PROPERTY(QMatrix4x4 transform READ transform WRITE setTransform MEMBER _transform)
    
public:
    //!
    //! Default constructor
    //!
    explicit LinkBlock(const QString& name = QString("link"), QObject *parent = 0)
        : BotBlock(name, parent)
    { }


    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BotBlock::BlockData; }
  
    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("link"); }



    //!
    // //! Transform matrix getter
    // //!
    // const QMatrix4x4& transform() const { return _transform; }
    
    // //!
    // //! Transform matrix setter
    // //!
    // void setTransform(const QMatrix4x4& matrix) { _transform = matrix; }
    
public slots:

protected:
    // rotation
    
    // translation
    

    // // Transform matrix
    // QMatrix4x4 _transform;
    
    // //! Link end
    // QWeakPointer<JointBlock> _endJoint;
    
    // //! Link base
    // QWeakPointer<JointBlock> _baseJoint;

};

#endif // LINKBLOCK_HPP
