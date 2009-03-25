#include "PhosDcsLogging.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <cstdlib>

PhosDcsLogging* PhosDcsLogging::fInstance = 0;



PhosDcsLogging::PhosDcsLogging() :
  fFileLogLevel(LOG_LEVEL_EXTREME_VERBOSE),
  fTerminalLogLevel(LOG_LEVEL_VERBOSE),
  fLogViewerLevel(LOG_LEVEL_DEFAULT),
  fLogFile(),
  fLogViewerStringStream()
{
  
  fLogLevels.push_back(string("NONE"));  
  fLogLevels.push_back(string("ERROR"));  
  fLogLevels.push_back(string("WARNING"));  
  fLogLevels.push_back(string("INFO"));  
  fLogLevels.push_back(string("VERBOSE"));  
  fLogLevels.push_back(string("VERY_VERBOSE"));  
  fLogLevels.push_back(string("EXTREME_VERBOSE"));  

  stringstream filename;
  stringstream timestamp;
  stringstream datestamp;
  
  GetTimeStamp(timestamp, datestamp); 
   filename << "../log/" << datestamp.str() << "_" << timestamp.str() << ".log";
  
  fLogFile.open(filename.str().c_str());
  //fLogFile.open("log/test.log");
 
  if(fLogFile.is_open() == false)
    {
      cerr << "Could not open log file!" << endl;
      cerr << "Check permissions and if ../log/ directory exists in current directory" << endl;
      cerr << "Exiting..." << endl;
      exit(1);
    }

  Logging(string("Starting Logger..."), LOG_LEVEL_INFO);
  
}
  
  
PhosDcsLogging::~PhosDcsLogging()
{
  fLogFile.close();
}

PhosDcsLogging* PhosDcsLogging::Instance()
{
  if(!fInstance)
    {
      fInstance = new PhosDcsLogging();
    }
  return fInstance;
}

void PhosDcsLogging::Logging(string logmsg, unsigned int level)
{
  
  string tmplogmsg = fLogLevels[level] + ": " + logmsg;
  if(level <= fFileLogLevel)
    {
      LogFile(tmplogmsg);
    }
  if(level <= fTerminalLogLevel)
    {
      LogTerminal(tmplogmsg);
    }
  if(level <= fLogViewerLevel)
    {
      LogViewer(tmplogmsg);
    }
}

void PhosDcsLogging::LogFile(string logmsg)
{
  stringstream timestamp;
  stringstream datestamp;
  GetTimeStamp(timestamp, datestamp);
  fLogFile << timestamp.str() << ": " << logmsg << endl;
}

void PhosDcsLogging::LogTerminal(string logmsg)
{
  cout << logmsg << endl;
}

void PhosDcsLogging::LogViewer(string logmsg)
{
  stringstream timestamp;
  stringstream datestamp;
  GetTimeStamp(timestamp, datestamp);
  fLogViewerStringStream << timestamp.str() << ": " << logmsg << endl;
}

string PhosDcsLogging::GetLogViewerString()
{ 
  string tmpstring = fLogViewerStringStream.str();
  fLogViewerStringStream.str(" ");
  return tmpstring; 
} 

void PhosDcsLogging::GetTimeStamp(stringstream& timestamp, stringstream& datestamp)
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  if(timestamp)
    {
      timestamp.fill('0');
      timestamp.width(2);
      timestamp << timeinfo->tm_hour << ":";
      timestamp.width(2);
      timestamp << timeinfo->tm_min << ":";
      timestamp.width(2);
      timestamp << timeinfo->tm_sec;
    }
  if(datestamp)
    {
      datestamp.fill('0');
      datestamp << timeinfo->tm_year + 1900 << ".";
      datestamp.width(2);
      datestamp << timeinfo->tm_mon + 1 << ".";
      datestamp.width(2);
      datestamp << timeinfo->tm_mday;  
    }
}













