

#include <iostream>
#include "PhosDcsLogging.h"

using namespace std;

int main(int argc, const char** argv)
{

  //  PhosDcsLogging::Instance()->SetTerminalOutputLevel(LOG_LEVEL_NONE);

  for(int i = 0; i < 1; ++i)
    {
      PhosDcsLogging::Instance()->Logging("test1", LOG_LEVEL_DEFAULT);

      PhosDcsLogging::Instance()->Logging("test2", LOG_LEVEL_DEFAULT);
    }

  cout << "Log viewer string: " << endl << PhosDcsLogging::Instance()->GetLogViewerString();

  return 0;
}
