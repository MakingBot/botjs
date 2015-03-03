#ifndef BLOCKMENU_HPP
#define BLOCKMENU_HPP

#include <QList>
#include <QScrollArea>
#include <QSharedPointer>
#include "BlockMenuItem.hpp"

//!
//! Menu that propose block that can be created
//!
class BlockMenu : public QScrollArea
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    BlockMenu(QWidget *parent = 0);

protected:

    //! Menu aera
    QSharedPointer<QWidget> _menu;

    //! Items
    QList<QSharedPointer<BlockMenuItem> > _items;

};

#endif // BLOCKMENU_HPP
