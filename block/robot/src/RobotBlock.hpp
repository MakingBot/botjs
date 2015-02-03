#ifndef ROBOTBLOCK_HPP
#define ROBOTBLOCK_HPP

#include <BodyAsmBlock.hpp>

//! Block interactive properties
#define ROBOTBLOCK_BLOCK_I_PROPERTIES_ {"name"} 

//!
//! Central data in robotic dev :-)
//! This block provide a main wrapper for the all robot structure
//!
class RobotBlock : public BotBlock
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName MEMBER _name)
   
public:
    //!
    //! Default constructor
    //!
    explicit RobotBlock(const QString& name, QObject *parent = 0)
        : BotBlock(name, QStringList(ROBOTBLOCK_BLOCK_I_PROPERTIES_), parent)
    { }

    //! FROM BotBlock
    virtual void init(QSharedPointer<BotEngine> js_engine)
    {
        BotBlock::init(js_engine);
    }

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("robot"); }

    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BotBlock::BlockData; }

    //!
    //! Robot name getter
    //!
    const QString& name() const { return _name; }

    //!
    //! Robot name setter
    //!
    void setName(const QString& name) { _name = name; emit propertyValuesChanged(); }
    
    // base()
    // partFromName()
    
public slots:
    //!
    //! Define the body base of the robot
    //!
    void setBase(BotBlock* block)
    {
        // Basic check
        
        // Check the block is a body
        
        // If the block is a child of another robot, kidnap it
        
        // If the block is a part remove it from parts
        
        // set it as the base
        _base = block->weakFromThis();
    }

    //!
    //! Append a body to the robot
    //!
    void appendBody(BotBlock* block)
    {
        
    }

    //! FROM BotBlock
    virtual void connect(BotBlock* block)
    {
        // Basic check
        if(!block) { throw std::runtime_error("Cannot connect to a null block"); }
        
        // if BodyAsmBlock
        // QInputDialog to ask if the block must be a base or a part
        
        // Add it to the childs
        BotBlock::connect(block);
    }

protected:
    //! Robot name
    QString _name;
    
    //! Robot base, a fixed body assembly
    QWeakPointer<BodyAsmBlock> _base;
    
    //! Robot parts of the robot
    QList<QWeakPointer<BodyAsmBlock>> _bodies;
};

#endif // ROBOTBLOCK_HPP
