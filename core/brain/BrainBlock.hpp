





#include <QThread>


class BhEvent
{

public:

    //! \brief
    BhEvent(const QJSValue& condition);

    void copy(BhEvent& bhev);


    bool attach(const QJSValue& action);

    bool triggered();

    void performAction();


    void operator=(BhEvent& bhev);

protected:

    //! \brief
    //!
    QJSValue action;

    //! \brief
    //!
    QJSValue condition;

};

/* ============================================================================
 *
 */
inline bool BhEvent::triggered()
{
    QJSValue result = condition.call();
    if(result.isBool())
    {
        return result.toBool();
    }
    return false;
}

/* ============================================================================
 *
 */
inline void performAction()
{
    action.call();
}



#include <QTimer>
#include <QThread>


//! \class BehaviourBlock
//!
class BehaviourBlock : public BotBlock
{

public:

    //! \brief Create a 'frequency' hz cyclic event called 'name'
    //!
    void createEvent(const QString& name, quint16 frequency);

    //! \brief Create an event called 'name' that is triggered when 'condition' is true
    //!
    void createEvent(const QString& name, QJSValue condition);

    //! \brief Attach an action to the event 'name'
    //!
    void attachEvent(const QString& name, QJSValue action);

    //! \brief To log an event from Js scope
    //!
    void log(const QString& message);

protected:


    QTimer m_timerControl;

    QTimer m_timerEvent;

    //! \brief Behaviour thread
    //!
    QThread m_thread;



};

/* ============================================================================
 *
 */
void BehaviourBlock::createEvent(const QString& name, const QJSValue& condition)
{
    // Check the name
    if( name.isEmpty() )
    {

    }

    // Check if the condition is callable
    if( !condition.isCallable() )
    {

    }

    // Check if the name already exists
    if( m_thread.m_events.find(name) != m_thread.m_events.end() )
    {

    }

    // Set the new event
    m_thread.m_events[name] = BhEvent(condition);
}

/* ============================================================================
 *
 */
void BehaviourBlock::attachEvent(const QString& name, const QJSValue& action)
{
    // Check if the action is callable
    if( !condition.isCallable() )
    {

    }

    // Set the action
    m_thread.m_events[name].attach(action);
}






class BehaviourThread : public QThread
{
    friend class BehaviourBlock;

public:

    //! \brief Default constructor
    //!
    BehaviourThread();

protected:

    //! \brief Map of behaviour events
    //!
    QMap<QString, BhEvent> m_events;

};


