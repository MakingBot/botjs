//!
//! \file RenderNode.hpp
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

#include <QList>
#include <Glub.hpp>
#include <BotBlock.hpp>

//!
//! Convert a data block in to a rendering shape
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class RenderNode
{

public:

    static QSharedPointer<RenderNode> CreateRenderNode(QWeakPointer<BotBlock> block);

    //!
    //! Default constructor
    //!
    RenderNode( QWeakPointer<RenderNode> parent = QWeakPointer<RenderNode>() );

    //! Update shape information
    void updateNode();

protected:

    //! True if this node must be rendered
    bool _mustBeRendered;

    //! Buffer parameters
    BufferParam _bufferParam;

    // Node parent
    QWeakPointer<RenderNode> _nodeParent;

    // Node childs
    QList<QSharedPointer<RenderNode> > _nodeChilds;

};
