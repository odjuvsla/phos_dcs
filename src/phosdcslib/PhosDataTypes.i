%module PhosDataTypes
 %{
 /* Includes the header in the wrapper code */
 #include "PhosDataTypes.h"
 %}

%include "std_string.i"
//%include "std_vector.i"
//%include "stl.i"
%include "/home/phs/build/swig/share/swig/1.3.39/stl.i"
%include "/home/phs/build/swig/share/swig/1.3.39/std/std_vector.i"
          
%apply const std::string& {std::string* fName};

//namespace std {
//  %template(vectorfee) vector<FeeServer>;
//};

namespace std {
   %template(vectorint) vector<int>;
};

%include "PhosConst.h"	
%include "PhosDataTypes.h"

