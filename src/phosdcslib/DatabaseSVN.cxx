
#include "DatabaseSVN.h"

DatabaseSVN::DatabaseSVN() : Database()
  //,fSvnClient()
  //,fRepoPath()
,fRevision(-1)
  //,fDestinationPath()
{
   
}

DatabaseSVN::DatabaseSVN ( std::string repoPath, std::string destPath ) : Database()
  //,fSvnClient()
  //,fRepoPath(repoPath)
,fRevision(-1)
  //,fDestinationPath(destPath)
{

}

DatabaseSVN::~DatabaseSVN()
{
   
}

int DatabaseSVN::CheckoutRevision ( long unsigned int rev )
{
//    int res = fSvnClient.checkout(fRepoPath.c_str(), fDestinationPath, svn::Revision(rev), true);
//    if(res == rev)
//    {
//       stringstream log;
//       log << "DatabaseSVN::CheckoutRevision: Successfully checked out revision " << rev << " of " << fRepoPath << " in " << fDestinationPath.c_str();
//       PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO);
//    }
//    else
//    {
//       stringstream log;
//       log << "DatabaseSVN::CheckoutRevision: Could not check out revision " << rev << " of " << fRepoPath << " in " << fDestinationPath.c_str();
//       PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
//    }
//    return res;
}
