#ifndef SPYWIDGETBODY_HPP
#define SPYWIDGETBODY_HPP
//!
//! \file SpyWidgetBody.hpp
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

#include <QWidget>
#include <BotBlock.hpp>

class SpyBlock;

//!
//! Widget that display personal block properties 
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class SpyWidgetBody : public QWidget
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    SpyWidgetBody(SpyBlock* spy_block, QWidget* parent=0);

    //! FROM QWidget
    void paintEvent(QPaintEvent *event);


    
public slots:

    //! When the spied change
    void onSpiedBlockChange();

    //! Update property structure
    void updateStructure();

    //! Update property values
    void updateValues();
    
    //! For line edit property widget
    void onLineTextEdited(const QString& text);

    //! For combobox that manage boolean switch
    void onComboBoxBool( const QString & text );

    //! For combobox that manage enum
    void onComboBoxEnum( const QString & text );

    //! For real list modification
    void onListModified(QList<qreal>& list);

    void onVector3DEdit(const QVector3D&);
    void onVector4DEdit(const QVector4D&);


    void onDoubleSpinBoxChange(double);


    //! Signal to the spy, which property has to be updated
    void onNewValueRequestFor(quint8 propid);


protected:

    //! Parent block
    SpyBlock* _spyblock;

    //! Map that contains widget of each property
    QMap<quint8, QWidget*> _widgetMap;

    //! Delete all current widgets
    void destroyStructure();



};

#endif // SPYWIDGETBODY_HPP
