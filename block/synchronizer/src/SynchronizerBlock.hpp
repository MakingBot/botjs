#ifndef SYNCHRONIZERBLOCK_HPP
#define SYNCHRONIZERBLOCK_HPP

//!
//!
//!
class SynchronizerBlock : public BotBlock
{
    Q_OBJECT
    
public:
    //!
    //! Default constructor
    //!
    explicit SynchronizerBlock(const QString& name = QString("synchronizer"), QObject *parent = 0);

    //! FROM BotBlock
    virtual void init(QSharedPointer<BotEngine> js_engine);

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("synchronizer"); }

    //! FROM BotBlock
    virtual QString getBlockDescription() const
    {
        return QString();
    }

public slots:

protected:
    //! UDP Socket
    QSharedPointer<QUdpSocket> _udpSocket;

};

#endif // SYNCHRONIZERBLOCK_HPP
