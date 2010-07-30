#ifndef DATABASESVN_H
#define DATABASESVN_H

#include "Database.h"
#include "PhosDcsLogging.h"

//#include <svncpp/client.hpp>
#include <string>

class DatabaseSVN : public Database
  {
     public:
     
      /** Constructor */
     DatabaseSVN();
     
     /** Constructor */
     DatabaseSVN(std::string repoPath, std::string destPath);
     
     /** Destructor */
     virtual ~DatabaseSVN();
    
     /** Initialise the database, abstract, must be overridden by subclasses */
     virtual int Initialise() = 0;
     
     /** Set the repository path */
     void SetRepoPath(std::string path) { fRepoPath = path; }
     
     /** Set the repository path */
     //   void SetDestinationPath(std::string path) { fDestinationPath = svn::Path(path); }
     
     protected:
	 
	/** Checkout given revision */
	int CheckoutRevision(unsigned long rev = -1);
     	
	/** The svn client */
	//	svn::Client fSvnClient;

	/** Path to the svn repo */
	std::string fRepoPath;
	
	/** The current revision ( -1 is trunk ) */
	unsigned long fRevision;
	
	/** Path to the destination for the checkout */
	//	svn::Path fDestinationPath;
	
  };

#endif // DATABASESVN_H
