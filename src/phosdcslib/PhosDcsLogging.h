#ifndef PHOSDCSLOGGING_H
#define PHOSDCSLOGGING_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const unsigned int LOG_LEVEL_NONE = 0;
const unsigned int LOG_LEVEL_ERROR = 1;
const unsigned int LOG_LEVEL_WARNING = 2;
const unsigned int LOG_LEVEL_INFO = 3;
const unsigned int LOG_LEVEL_VERBOSE = 4;
const unsigned int LOG_LEVEL_VERY_VERBOSE = 5;
const unsigned int LOG_LEVEL_EXTREME_VERBOSE = 6;

const unsigned int LOG_LEVEL_DEFAULT = LOG_LEVEL_INFO;



/**
 * Class used for logging for the PHOS APD GUI
 */
class PhosDcsLogging
  {
  public:

    /** Returns pointer to the logging instance. Creates the object if it don't exists */
    static PhosDcsLogging* Instance();

    /** The function used for logging */
    void Logging ( string logmsg, unsigned int level );

    /** Set the logging level for the file output */
    void SetFileLoggingLevel ( unsigned int level )
    {
      fFileLogLevel = level;
    }

    /** Set the logging level for the terminal */
    void SetTerminalOutputLevel ( unsigned int level )
    {
      fTerminalLogLevel = level;
    }

    /** Set the logging level for the log viewer */
    void SetLogViewerLevel ( unsigned int level )
    {
      fLogViewerLevel = level;
    }

    /** Get the log viewer string */
    string GetLogViewerString();

    /** Get the current time/date stamp */
    void GetTimeStamp ( stringstream& timestamp, stringstream& datestamp );

  private:

    /** Default constructor (called by the Instance() function */
    PhosDcsLogging();

    /** Default destructor */
    ~PhosDcsLogging();

    /** Log message to file */
    void LogFile ( string logmsg );

    /** Log message to terminal */
    void LogTerminal ( string logmsg );

    /** Log message to log viewer */
    void LogViewer ( string logmsg );

    /** Pointer to the logging instance */
    static PhosDcsLogging* fInstance;

    /** The log level for the log file */
    unsigned int fFileLogLevel;

    /** The log level for the terminal */
    unsigned int fTerminalLogLevel;

    /** The log level for the log viewer */
    unsigned int fLogViewerLevel;

    /** The stream to the log file */
    ofstream fLogFile;

    /** The log viewer stream */
    stringstream fLogViewerStringStream;

    /** Vector containing strings corresponding to the different log levels */
    vector<string> fLogLevels;

    /** Copy constructor - not implemented */
    PhosDcsLogging ( const PhosDcsLogging & );

    /** Assignment operator - not implemented */
    PhosDcsLogging & operator = ( const PhosDcsLogging );

  };


#endif
