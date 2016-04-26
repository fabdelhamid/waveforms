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


float NumEval  (const string& operation)
{
	list <string> operands = SeparateOperands (operation);
	
	if (operands.size() == 1)
	{
		

			/*
				Todo: convert use run_function on operators
				*/
				
			
		    return _stof (operation);
		    
		    

	} /* if - one operand*/
	
	else
	{	
		
		/*
			TODO: use run_function
			*/
			
		/*
			Temporary workaround until run_function is used
			NOTE: ASSUMES multiplication operation
			*/
		if (operands.size() == 3)
		{
			return NumEval (operands.front()) * NumEval (operands.back());
		} /* if */
		
		error ("Multiple operands to NumEval");
	} /* else - multiple operands*/	 
	
} /* eval */


string Eval  (const string& o_operation)
{

 
    string operation = o_operation; //really redundant
    operation = StripWhitespaceBE (operation);
    operation = StripParens (operation);

    //auto operands = SeparateOperands (operation); operand count has to be one at this point

	list <string> operands = SeparateOperands (o_operation);
	
	if (operands.size() == 1)
	{
			
        // literal value
        if (IsNumericValue (operation))
		{
		    return tostr (NumEval (operation)); //maybe return operation  directly
		} /* if */
		
	    function_t fcode;
        string function_name = GetFunctionName(operation);
        
         //function
        if (IsFunctionCall (operation))
        { 
    		return run_function (function_name, SeparateArguments (StripB (function_name, operation)));
     	} /* if */
     	
	 	
        // only one operand at this point, either a symbol or unknown
        return operation;
	} /* if */
	
	else
	{
		
		string result = "";
		
		for (list<string>::iterator o = operands.begin(); o != operands.end(); o++)
		{
			
			if (IsOperator (*o))
			{
				result += *o;	
				
			} /* if */
			
			else
			{
				result += Eval (*o);	
			
			} /* else */
			
			
		} /* for */

		return StripE (" ", result);
	} /* else */	 
				
} /* eval */

void AssertArgtype (const string& argument, const type_t type)
{
	if (OperationType (argument) != type)
		error ("argument " + argument + " is of the wrong type");
		
} // AssertArgtype

