#ifndef NETWORKBLOCK_HPP
#define NETWORKBLOCK_HPP

#include <QUdpSocket>
#include <BotBlock.hpp>
#include <NetworkThread.hpp>

//!
//! Block that provides a communication interface for Network using IP on UDP/TCP
//!
class NetworkBlock : public BotBlock
{
    Q_OBJECT
    Q_ENUMS(InterfaceRole)
    Q_ENUMS(InterfaceConfiguration)


    Q_PROPERTY(QString          netname     READ netname WRITE setNetname MEMBER _netname)
    Q_PROPERTY(bool             activated   READ activated WRITE setActivated MEMBER _activated)
    Q_PROPERTY(quint16          port        MEMBER _port )
    Q_PROPERTY(InterfaceRole    role        MEMBER _role)
    
public:
    enum InterfaceRole { RoleMaster, RoleSlave } ;
    enum InterfaceConfiguration { ConfigurationManual, ConfigurationAuto } ;

    //!
    //! Default constructor
    //!
    explicit NetworkBlock(const QString& name = QString("network"), QObject *parent = 0);

    //! FROM BotBlock
    virtual void init(QSharedPointer<BotEngine> js_engine);

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("network"); }

    //! FROM BotBlock
    virtual QString getBlockDescription() const
    {
        return QString();
    }
    
    //! Network interface name
    const QString& netname() { return _netname; }

    void setNetname(const QString& name) { _netname = name; }

    //!
    //! Activation status getter
    //!
    bool activated() { return _activated; }
    
    void setActivated(bool active)
    {
        if(active) { activate(); }
        else  { _activated = false;  } 
    }
    
    void activate()
    {
    
        _activated = true; 
    }

public slots:

protected:
    //! Network interface name
    QString _netname;

    //! Used port for the interface
    quint16  _port;
    
    //! Role of this interface
    InterfaceRole _role;

    //! Configuration type of this interface
    InterfaceConfiguration _configuration;
    
    //! Activation status, True if the interface is activated
    bool _activated;
    
    // status: inactive, scanning, connected
    
    //! UDP Socket
    QSharedPointer<QUdpSocket> _udpSocket;

    // QHostAddress  _target;
    // QStringList <name,ip>
    
// master, manual
// write port
// start spy
// start scan
// write target
// inactive -> activate
    
    

/*
 _udpSocket->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, _port);
*/

};

#endif // NETWORKBLOCK_HPP
