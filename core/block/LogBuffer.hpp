#ifndef LOGBUFFER_HPP
#define LOGBUFFER_HPP
//!
//! \file LogBuffer.hpp
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

#include <QDir>
#include <QMutex>
#include <QMutexLocker>

#include <QFile>
#include <iostream>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <QTextStream>
#include <QSharedPointer>

//!
//! End tag to terminate a log stream
//!
class LogEnder { public: LogEnder() {} };

//!
//! Buffer to store log messages
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class LogBuffer : public QObject
{
    Q_OBJECT
    
public:
    //!
    //! Default constructor
    //!
    explicit LogBuffer(const QString& logfilepath, QObject* parent = 0)
        : QObject(parent)
    	, _newLog(true)
    	, _logEnable(false)
		, _talkEnable(false)
    	, _coutstream(stdout)
    {
        // Set the file path
        _logfile.setFileName(logfilepath);
     
        // Open log file
        if( ! _logfile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) )
        {
            _coutstream << "Unable to open (" << logfilepath << ")" << endl;
        }

        // Open stream on this file
        _filestream.setDevice( &_logfile );
    }
    
    //!
    //!
    //!
    ~LogBuffer()
    {
        _logfile.close();
    }

    //!
    //! Id setter
    //!
    void setId(const QString& id)
    {
    	_id = id;
    }

    //!
    //! Log enable getter
    //!
    bool logEnable() const
    {
    	return _logEnable;
    }

    //!
    //! Log enable setter
    //!
    void setLogEnable(bool e)
    {
        if(e) { _logEnable = true;  }
        else  { _logEnable = false; }
    }

    //!
    //! Talk enable getter
    //!
    bool talkEnable() const
    {
    	return _talkEnable;
    }

    //!
    //! Talk enable setter
    //!
    void setTalkEnable(bool e)
    {
        if(e) { _talkEnable = true;  }
        else  { _talkEnable = false; }
    }

    //!
    //! General log function
    //!
    template<typename T> void streamlog( T val )
    {
        if( _logEnable )
        {
        	_filestream << val;
        }

        if( _talkEnable )
        {
            if(_newLog)
            {
                _coutstream << "[" << _id << "] ";
            }
            _coutstream << val;
        }

        if(_newLog) { _newLog = false; }
    }

    //!
    //! Stop the current log and flush it
    //!
    void endLog()
    {
        if( _logEnable )
        {
        	_filestream << endl;
        }

        if( _talkEnable )
        {
        	_coutstream << endl;
        }

        if(!_newLog) { _newLog = true; }     
    }

    // --- Stream Operators ---

    LogBuffer& operator<< ( LogEnder            p ) { endLog();                             return *this; }
    
    LogBuffer& operator<< ( QChar               p ) { streamlog<QChar               >(p);   return *this; }
    LogBuffer& operator<< ( signed short        p ) { streamlog<signed short        >(p);   return *this; }
    LogBuffer& operator<< ( float               p ) { streamlog<float               >(p);   return *this; }
    LogBuffer& operator<< ( const QString&      p ) { streamlog<const QString&      >(p);   return *this; }
    LogBuffer& operator<< ( char                p ) { streamlog<char                >(p);   return *this; }
    LogBuffer& operator<< ( unsigned short      p ) { streamlog<unsigned short      >(p);   return *this; }
    LogBuffer& operator<< ( signed int          p ) { streamlog<signed int          >(p);   return *this; }
    LogBuffer& operator<< ( unsigned int        p ) { streamlog<unsigned int        >(p);   return *this; }
    LogBuffer& operator<< ( signed long         p ) { streamlog<signed long         >(p);   return *this; }
    LogBuffer& operator<< ( unsigned long       p ) { streamlog<unsigned long       >(p);   return *this; }
    LogBuffer& operator<< ( qlonglong           p ) { streamlog<qlonglong           >(p);   return *this; }
    LogBuffer& operator<< ( qulonglong          p ) { streamlog<qulonglong          >(p);   return *this; }
    LogBuffer& operator<< ( double              p ) { streamlog<double              >(p);   return *this; }
    LogBuffer& operator<< ( const QByteArray&   p ) { streamlog<const QByteArray&   >(p);   return *this; }
    LogBuffer& operator<< ( const char*         p ) { streamlog<const char*         >(p);   return *this; }
    LogBuffer& operator<< ( const void*         p ) { streamlog<const void*         >(p);   return *this; }

    LogBuffer& operator<< ( const QVector3D& p )
    {
        QString strlist;
        QTextStream s(&strlist);
        s << '[' << p.x() << ", " << p.y() << ", " << p.z() << ']';
        streamlog<const QString&>(strlist);
        return *this;
    }
    
    LogBuffer& operator<< ( const QVector4D& p )
    {
        QString strlist;
        QTextStream s(&strlist);
        s << '[' << p.x() << ", " << p.y() << ", " << p.z() << ", " << p.w() << ']';
        streamlog<const QString&>(strlist);
        return *this;
    }

    LogBuffer& operator<< ( const QList<qreal>& p )
    {
        bool first = true;

        QString strlist;
        QTextStream s(&strlist);

        s << '[';
        foreach(qreal r, p)
        {
            if(first) { s << r; first=false; }
            else      { s << ", " << r;      }
        }
        s << ']';

        streamlog<const QString&>(strlist);
        return *this;
    }

protected:

    // LogBuffer identifier
    QString _id;

    //! True if no log is being written
    bool _newLog;

    //! Buffer lock
    QMutex _mutex;

    //! True if the buffer can write logs into a file
    bool _logEnable;

    //! Log file descriptor 
    QFile _logfile;
    
    //! Stream to write logs into a file
    QTextStream _filestream;

    //! True if the buffer can print logs on the shell
    bool _talkEnable;

    //! Stream to print logs on the shell
    QTextStream _coutstream;

};

#endif // LOGBUFFER_HPP
