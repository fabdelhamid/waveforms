/*
    WAVEGEN - 2014,2015 Fady Abdelhamid <fabdelhamid@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    WAVEGEN  is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Fady's Circuit Solver.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "../wavegen.h"


#define ASSERT_ARGCOUNT(n) if(arguments.size() != n) error("wrong argument count for `" + function_name + "' ")

using namespace std;

// allowable fcodes  = FN_CURRENT, FN_VOLTAGE, FN_VALUE, FN_ADD, FN_SUBTRACT, FN_MULTIPLY, FN_DIVIDE, FN_RAISE, FN_EXP
int  run_function (function_t fcode, string& arg1 , string& arg2 )
{

        
} /* run_function */

string run_function (const string function_name, const list<string>& arguments  )
{  
    float result = 0;
    function_t fcode = FN_INVAL;
    string sresult = "";


    list<string>::const_iterator u = arguments.begin();
    string argument_0 = "", argument_1 = "", argument_2 = "", argument_3 = ""; 

    if (u != arguments.end())
       argument_0 = *u++;    
    
    if (u != arguments.end())
       argument_1 = *u++;    

    if (u != arguments.end())
       argument_2 = *u++;    

    if (u != arguments.end())
       argument_3 = *u++;    

	/*******************************************************************/
	
	
	/*
	  Action depending on function name 
		*/
 
#include "builtin_methods.cpp"   // set,seta,setb,...
#include "builtin_operators.cpp" // +,-,...
#include "builtin_mathematical_functions.cpp" // sin,cos,...
#include "builtin_commands.cpp" // print, println, ...

	//  REMOVED: `rem' command was removed
	
	/*
		Unknown function.
		TODO: custom functions.
		*/
	else
	{
		// System function
		if (BeginsWith ("_OP", function_name))
			error ("internal command " + function_name + " is not supported by this build");
		else
			error ("unknown function `" + function_name + "' ");
		
			
	} /* else */
	
	return "NaV";
	
	/*******************************************************************/		       
    switch (fcode)
    {
           case FN_CURRENT:
                break;
                
                
            //todo: fix for unlimited arguments    
           ////////////////////////////////////////////////////////////

           case FN_ADD:
                if (IsNumericValue (arguments))
                  {
                                          
                     for (list<string>::const_iterator i = arguments.begin(); i!=arguments.end(); i++)
                       result += NumEval (*i);
                               
                      return tostr (result);

                  } /* if */
                 else
                  {
                  	
                  	std::list<string>::const_iterator e = arguments.end(); --e;
                  	list<string>::const_iterator i = arguments.begin();
                     for (; i != e; i++)
                       sresult += Eval (*i) + " + ";
                       
                       i++; sresult += Eval (*i);
                       
                       //  improve result
                       return sresult;
                       
                  } /* else */      

           ////////////////////////////////////////////////////////////

           case FN_SUBTRACT:
                if (IsNumericValue (arguments))
                  {
                                          
                     for (list<string>::const_iterator i = arguments.begin(); i!=arguments.end(); i++)
                       result -= NumEval (*i);
                               
                      return tostr (result);

                  } /* if */
                 else
                  {
                  	std::list<string>::const_iterator e = arguments.end(); --e;
                  	list<string>::const_iterator i = arguments.begin();
                     for (; i != e; i++)
                       sresult += Eval (*i) + " - ";
                       
                       i++; sresult += Eval (*i);
                       
                       //  todo: improve result
                       return sresult;
                       
                  } /* else */      


           ////////////////////////////////////////////////////////////

           case FN_MULTIPLY:
                if (IsNumericValue (arguments))
                  {
                                          
                     for (list<string>::const_iterator i = arguments.begin(); i!=arguments.end(); i++)
                       result *= NumEval (*i);
                               
                      return tostr (result);

                  } /* if */
                 else
                  {
                  	std::list<string>::const_iterator e = arguments.end(); --e;
                  	list<string>::const_iterator i = arguments.begin();
                     for (; i != e; i++)
                       sresult += Eval (*i) + "*";
                       
                       i++; sresult += Eval (*i);
                       
                       //  improve result
                       return sresult;
                       
                  } /* else */      
                

           ////////////////////////////////////////////////////////////

           case FN_DIVIDE:
                if (IsNumericValue (arguments))
                  {
                                          
                     for (list<string>::const_iterator i = arguments.begin(); i!=arguments.end(); i++)
                       result /= NumEval (*i);
                               
                      return tostr (result);

                  } /* if */
                 else
                  {
                  	std::list<string>::const_iterator e = arguments.end(); --e;
                  	list<string>::const_iterator i = arguments.begin();
                     for (; i != e; i++)
                       sresult += Eval (*i) + " / ";
                       
                       i++; sresult += Eval (*i);
                       
                       //  improve result
                       return sresult;
                       
                  } /* else */      
           
           ////////////////////////////////////////////////////////////

           case FN_EXP:
           
                if (IsNumericValue (argument_0))
                  return _ftos (exp(NumEval (argument_0)));

                //if (!numerical_value_1 && !numerical_value_2)
                  return  "exp(" + Eval (argument_1) + ")";

           ////////////////////////////////////////////////////////////
            
           case FN_RAISE: 
           
				bool numerical_value_1 = IsNumericValue (argument_0);
				bool numerical_value_2 = IsNumericValue (argument_1);
           		
                
                if (numerical_value_1 && numerical_value_2)
                  return tostr(pow (NumEval (arguments.front()), NumEval (argument_1)));

                if (numerical_value_1 && !numerical_value_2)
                  return tostr (NumEval (arguments.front())) + " ^ " + Eval (argument_1);
                                                   
                if (!numerical_value_1  && numerical_value_2)
                  return Eval (arguments.front())  + " ^ " + tostr (NumEval (argument_1));

                //if (!numerical_value_1 && !numerical_value_2)
                  return Eval (arguments.front())  + " ^ " + GetBestForm (argument_1);


           ////////////////////////////////////////////////////////////

           // cos,sin,...                           
    } /* switch */
        
} /* run_function */

