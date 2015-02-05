#ifndef LOGBUFFER_HPP
#define LOGBUFFER_HPP

#include <QDir>
#include <QMutex>
#include <QMutexLocker>

#include <QFile>
#include <QTextStream>
#include <QSharedPointer>

class LogEnder
{
public:
    LogEnder() {}
};

//!
//! Buffer to store log messages
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class LogBuffer : public QObject
{
    Q_OBJECT
    
public:
    //! States of the log buffer
    enum State { StateCreated = 0x0, StateInitialized = 0x1, StateEnabled = 0x2, StateTalking = 0x4 };
    
    //!
    //! Default constructor
    //!
    explicit LogBuffer(QObject* parent=0)
        : QObject(parent), _state(StateCreated), _coutstream(stdout)
    { }
    
    ~LogBuffer()
    {
        _logfile.close();
    }

    //! Initialize the log buffer
    void init(const QString& logfilepath, bool enable = false, bool verbose = false)
    {
        // Set the file path
        _logfile.setFileName(logfilepath);
     
        // Open log file
        if( ! _logfile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) )
        {
            std::cerr << "Unable to open (" << logfilepath.toStdString() << ")" << std::endl;
        }

        // Open stream on this file
        _filestream = QSharedPointer<QTextStream>( new QTextStream(&_logfile) );
        
        // Set state flags
        if(enable)  { _state |= StateEnabled; }
        if(verbose) { _state |= StateTalking; }
        _state |= StateInitialized;
    }

    //! Stop logging
    void disable() { _state &= ~StateEnabled; }

    //! Start file logging
    void enable()  { _state |=  StateEnabled;  }

    //!  Enable setter
    void setStateEnable(bool en) 
    {
        if(en) { enable();  }
        else   { disable(); }
    }
    
    //! Start file and shell logging
    void talk()    { _state |= (StateEnabled | StateTalking); }

    //! Stop shell logging
    void stopTalking() { _state &= ~StateTalking; }

    //! Talking setter
    void setStateTalk(bool talk) 
    {
        if(talk) { this->talk();        }
        else    { stopTalking(); }
    }

    //! Return true if this log buffer is enable and log into its file
    bool isEnable()  { if( _state >= (StateInitialized+StateEnabled) ) { return true; } else { return false; } } 

    //! Return true if this log buffer is talking and log into the std cout
    bool isTalking() { if( _state >= (StateInitialized+StateEnabled+StateTalking) ) { return true; } else { return false; } }

    //! General log function
    template<typename T> void streamlog( T val )
    {
        if( _state >= (StateInitialized+StateEnabled) )
        {
            std::cout << "1" << std::endl;

            (*_filestream.data()) << val;
            if( _state >= (StateInitialized+StateEnabled+StateTalking) )
            {

            std::cout << "2" << std::endl;

                _coutstream << val;
            }
        }     
    }

    void endLog()
    {

        std::cout << "3" << std::endl;

        if( _state >= (StateInitialized+StateEnabled) )
        {
            (*_filestream.data()) << endl;
            if( _state >= (StateInitialized+StateEnabled+StateTalking) )
            {
                _coutstream << endl;
            }
        }     
    }

    //LogEnder endLog() { }
    // {
    //     return QTextStream(endl);

    //  //         std::cout << "3" << std::endl;

    //  //    if( _state >= (StateInitialized+StateEnabled) )
    //  //    {

    //  // std::cout << "4" << std::endl;
    //  //        (*_filestream.data()) 
    //  //        if( _state >= (StateInitialized+StateEnabled+StateTalking) )
    //  //        {
    //  // std::cout << "5" << std::endl;

    //  //            _coutstream << endl;
    //  //        }
    //  //    }     
    //  //    return *this;
    // }

    // --- Stream Operators ---

    //LogBuffer& operator<< ( LogBuffer& b ) { return *this; }
    

    LogBuffer& operator<< ( LogEnder le ) { endLog(); return *this; }
    
    LogBuffer& operator<< ( QChar c     ) { streamlog<QChar>(c); return *this; }
    LogBuffer& operator<< ( signed short i ) { streamlog<signed short>(i); return *this; }
    LogBuffer& operator<< ( float f ) { streamlog<float>(f); return *this; }
    LogBuffer& operator<< ( const QString & string ) { streamlog<const QString &>(string); return *this; }
    LogBuffer& operator<< ( char c ) { streamlog<char>(c); return *this; }

protected:

    //! Represents the state of the log buffer
    quint8 _state;
    
    //! Buffer mutex
    QMutex _mutex;

    //! Log file descriptor 
    QFile _logfile;
    
    //! Stream to write in std::cout
    QTextStream _coutstream;
    
    //! Stream to write in the log file
    QSharedPointer<QTextStream> _filestream;
    
};

#endif // LOGBUFFER_HPP
