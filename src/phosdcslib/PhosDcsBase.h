#ifndef PHOSDCSBASE_H
#define PHOSDCSBASE_H

#include "PhosConst.h"
#include "DatabasePedestals.h"
#include <typeinfo>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
//#include <typeinfo>

using  std::cout;
using  std::endl;

using namespace PhosConst;

class PhosDcsBase
  {
  public:
    PhosDcsBase();
    virtual ~PhosDcsBase();

    template<typename T>
    void  Reset ( T *array, const int N ) const
      {
        for ( int i= 0; i< N; i++ )
          {
            array[i] = 0;
          }
      }

    template<typename T>
    void  DeletePtr ( T *array, const int N ) const
      {
        for ( int i= 0; i< N; i++ )
          {
            if ( array[i] != 0 )
              {
                delete array[i];
              }
          }
      }




    template<typename T>
    void DumpData ( const T *array, const int N ) const
      {
        for ( int i= 0; i< N; i++ )
          {
            if ( N%16 == 0 )
              {
                printf ( "\n" );
              }
            cout <<array[i]<<"  \t" <<endl;
          }
      }


    template<typename T>
    T  MaxValue ( const T *values, const int N ) const
      {
        T tmpMax = 0;

        for ( int i=0; i< N; i++ )
          {
            if ( values[i] > tmpMax )
              {
                tmpMax = values[i];
              }
          }
        return tmpMax;
      }


    template<typename T>
    T  MinValue ( const T *values, const int N ) const
      {
        T tmpMin = MaxValue ( values, N );

        for ( int i=0; i< N; i++ )
          {
            if ( tmpMin > values[i] )
              {
                tmpMin = values[i];
              }
          }
        return tmpMin;
      }

    //  static void SetScriptDir(char *dir);

    int CheckFile ( const char *fileName, const char *opt ) const;
    int ScanTextFromFile ( const char *fileName, char *textbuffer, const int maxsize );

    static bool fParamIsSet;
    static char fDatabaseFolder[1024];
    static char fSandboxFolder[1024];
    static char fPhosDcsDir[1024];
    static char fPhosDcsScriptDir[1024];
    //  static char fPhosDcsBinDir[1024];
    // static char fPhosDcsLibDir[1024];
    //  static char fPhosDcsSourceDir[1024];
    //  static char fPhosDcsGuiDir[1024];
    
   protected:
	
	/** SVN database of the pedestal values */
	DatabasePedestals fPedestalsDatabase;
	
	
  };

#endif
