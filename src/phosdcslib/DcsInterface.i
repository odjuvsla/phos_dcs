%module DcsInterface
 %{
 /* Includes the header in the wrapper code */

 #include "DcsInterface.h"
 %}

//%include "std_vector.i"
%include "std_string.i"
#%include "/home/phs/build/swig/share/swig/1.3.39/stl.i"
#%include "/home/phs/build/swig/share/swig/1.3.39/std/std_vector.i"
%include "stl.i"
%include "std_vector.i"

%apply const std::string& {std::string* fName};

%include "PhosConst.h"
%include "PhosDataTypes.h"
%include "DcsInterface.h"

namespace std {
   %template(vectorfee) vector<FeeServer>;
};

namespace std {
   %template(vectorint) vector<int>;
};

//namespace std {
//   %template(namestring) string;
//};
