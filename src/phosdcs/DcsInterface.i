%module DcsInterface
 %{
 /* Includes the header in the wrapper code */

 #include "DcsInterface.h"
 %}

%include "std_vector.i"
%include "std_string.i"

%apply const std::string& {std::string* fName};

%include "PhosConst.h"
%include "PhosDataTypes.h"
%include "DcsInterface.h"



namespace std {
   %template(vectorfee) vector<FeeServer>;
};
