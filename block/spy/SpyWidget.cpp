//!
//! \file SpyWidget.cpp
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

#include <SpyWidget.hpp>
#include <SpyBlock.hpp>

#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QCloseEvent>
#include <QGridLayout>
#include <QMapIterator>
#include <QMetaProperty>

/* ============================================================================
 *
 * */
SpyWidget::SpyWidget(QWeakPointer<SpyBlock> spy_block, QWidget* parent)
    : QWidget(parent)
    , _spyblock         (spy_block)
    , _header           (spy_block)
    , _body             (spy_block)
    , _footer           (spy_block)
{
    // Basic verification
    if(!getSharedSpyBlock()) {
        throw std::runtime_error("Spy widget has been created without a parent spy block");
    }

    // Window configuration
    setWindowTitle("SpyBlock: " + getSharedSpyBlock()->blockName());

    // Create layout
    new QGridLayout(this);
    ((QGridLayout*)layout())->setSpacing(0);
    ((QGridLayout*)layout())->setContentsMargins(0,0,0,0);
    
    ((QGridLayout*)layout())->addWidget(&_header, 0, 0, Qt::AlignTop);
    ((QGridLayout*)layout())->addWidget(&_body  , 1, 0);
    ((QGridLayout*)layout())->addWidget(&_footer, 2, 0, Qt::AlignBottom);
    
    // Connect update signals
    connect(getSharedSpyBlock().data(), SIGNAL(spiedBlockChanged()), this, SLOT(onSpiedBlockChange()));
}

/* ============================================================================
 *
 * */
QSharedPointer<BotBlock> SpyWidget::getSharedSpiedBlock()
{
    return getSharedSpyBlock()->getSharedSpiedBlock();
}

/* ============================================================================
 *
 * */
void SpyWidget::onSpiedBlockChange()
{
    _header.onSpiedBlockChange();
    _body  .onSpiedBlockChange();
    _footer.onSpiedBlockChange();

    // Build the new one
    QSharedPointer<BotBlock> spied = getSharedSpiedBlock();
    if(spied)
    {        
        // Connect events
        connect( spied.data(), SIGNAL(blockfPropertyValuesChanged  ()), &_header, SLOT(updateValues()) );

        connect( spied.data(), SIGNAL(blockiPropertyValuesChanged   ()), &_body  , SLOT(updateValues   ()) );
        connect( spied.data(), SIGNAL(blockiPropertyStructureChanged()), &_body  , SLOT(updateStructure()) );
    }
}

/* ============================================================================
 *
 * */
void SpyWidget::closeEvent(QCloseEvent* event)
{
    if(_spyblock)
    {
        //
        QSharedPointer<SpyBlock> spyblock = _spyblock.toStrongRef();
        
        //
        spyblock->hide();
        
        //
        event->ignore();
    }
}
