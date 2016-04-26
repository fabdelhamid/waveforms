/*
    WAVEGEN - 2014,2015 Fady Abdelhamid <fabdelhamid@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    WAVEGEN is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Fady's Circuit Solver.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "../wavegen.h"

operator_t CmpOperator (const string &context, int l)
{
   for (ident i = 0; i < OPERATORS; i++)
     if (opsign[i].length() > 0 && Compare (opsign[i], context, l))
       return (operator_t) i;

   return (operator_t) 0;
 
} /* CmpOperator */

  /////////////////////////////////////////////////////////////////

/*
	
	*/
bool IsOperator (const string& o)
{
	
	return o.length() && (o.length() == opsign[(unsigned int) CmpOperator (o)].length());
} /* IsOperator */

  /////////////////////////////////////////////////////////////////

function_t CmpFunction (const string &context, location l)
{
   for (ident i = 0; i < FUNCTIONS; i++)
     if (Compare (funcname[i], context, l)   
     		&&	((context.length() > l + funcname[i].length())
		 			&& context.at (Next (context, l + funcname[i].length())) == '(')
			  	 || (context == funcname[i]))
			 
			 
			  
       return (function_t) i;

   return (function_t) 0;	
	
} /* CmpFunction */

  /////////////////////////////////////////////////////////////////

block_t CmpBlock (const string &context, location l)
{
   for (ident i = 0; i < BLOCKS; i++)
     if (Compare (blockname[i], context, l)   
     		&&	(context.length() > l + blockname[i].length())
			  	 || (context == blockname[i]))
       return (block_t) i;

   return (block_t) 0;	
	
} /* CmpFunction */

  /////////////////////////////////////////////////////////////////

bool IsNumericValue  (const list<string>& arguments)
{
	/* 
		TEMPORARY
		*/
	if (arguments.size() > 1)
		return false;
		
	for (list<string>::const_iterator o = arguments.begin(); o != arguments.end(); o++)
	{
		if (!IsNumericValue (*o))
		  return false;
	} /* for */
	
	return true;
} /* IsNumericValue */

  /////////////////////////////////////////////////////////////////

/*
  Determine if the value of a string is a known numerical value 
  */
bool IsNumericValue  (const string& o_formula)
{
	
	bool result = true;
	string formula = StripParens (o_formula);
		
	list<string> operands = SeparateOperands (formula);

	// one operand only 
    if (operands.size() == 1)  
    {    
	
        ///////////////////////////// Literal
        if (IsNumber (operands.front() ))
        {    	
        
			return true;
		} /* if */

        ///////////////////////////// Value Identifier


    	
        ///////////////////////////// Function Call

        
        if (IsFunctionCall (operands.front ()))
		{
			return false;
			
			bool bresult = IsNumericValue (SeparateArguments (GetArguments  (operands.front()))  )  ;
          	return bresult;
    	} /* if */
    	
        return false;
    } /* if */

	// multiple operands  
	else
    { 
	   
        for (list<string>::iterator o = operands.begin(); o != operands.end(); )	
        {
		 
            if (!IsNumericValue (*o))
            {
            	return false;
         	} /* if */
         	
            o++; 
			
         	if (o != operands.end())				
				o++;
        } /* for */

        return true;
    } /* else */

} /* IsNumericValue */

  /////////////////////////////////////////////////////////////////

/*
  Determine if a the value of a string is constantly known
  (symbolic or numeric)
  */
bool ValueKnown  (const string& o_formula)
{
	bool result = true;
	
	string formula        = StripParens (o_formula);
	list<string> operands = SeparateOperands (formula);
    
    // one operand only 
    if (operands.size() == 1)  
    {
		    	
        ///////////////////////////// Literal
        if (IsNumber (operands.front()))
          return true;
        
        ///////////////////////////// Literal
        if (IsSymbol (operands.front()))
          return true;

        ///////////////////////////// Value Request

        
        ///////////////////////////// Function Call
        if (IsFunctionCall (operands.front()))
          return ValueKnown (SeparateArguments (GetArguments  (operands.front())));
        
        
        return false;
    } /* if */
    
    // multiple operands  
    else
    {
    	operands = OperandsOnly (operands);
    
        for (list<string>::iterator o = operands.begin(); o != operands.end(); o++)	
        { 
        
          if (!ValueKnown (*o))
             return false;          
          
        } /* for */
    return true;
    } /* else */

} /* circuit_t::ValueKnown */

  /////////////////////////////////////////////////////////////////

bool ValueKnown  (const list<string>& arguments)
{
	
	
	for (list<string>::const_iterator o = arguments.begin(); o != arguments.end(); o++)
		if (!ValueKnown (*o))
			return false;
	
	return true;
	
} /* circuit_t::ValueKnown */

  /////////////////////////////////////////////////////////////////

string GetBestForm (const string& formula)
{
	 // TODO: improve
	 return formula;	
} /* GetBestForm */
  /////////////////////////////////////////////////////////////////
  
  
  /////////////////////////////////////////////////////////////////
/////



// TODO: GetValueAsString with element value identifier




  /////////////////////////////////////////////////////////////////


  
  //////////////////////////////////////////////////////////////
  list<string> symbols;
  /*
    Determine if a string is a previously-added symbol name
    */
  bool  IsSymbol (const string& s_name)
  {
  	
	// run through global symbol table
	for (list<string>::iterator i = symbols.begin();  i != symbols.end(); i++)
	  if (*i == s_name)
	    return true;
	
	return false;
	
  } /* IsSymbol */
  
  /////////////////////////////////////////////////////////////////

/*
  Add a symbol to the symbol table
  */
  void  SetSymbol (string& s_name)
  {
	symbols.push_back      (s_name);
	
  } /* SetSymbol */
  
  /////////////////////////////////////////////////////////////////
  
  
  /*
    Determine if the *left hand side* of an = 0 equation is redundant 
    for example, 1 - 1 or  -1 + 1.
    
    Note that this function takes the left hand side only, not the = 0 part. */
    
bool RedundantEquation (const string& lhs)
{
	
	//string o_lhs = lhs;
	list<string> ops = SeparateOperands (lhs);
	
	/* 
	  First: the case of x-x (=0) 
		*/
	
	/* FFWD to 2nd operand */
	list <string>::const_iterator o = ops.begin();
	o++;
	
	if (ops.size() == 3 && ops.front() == ops.back() && (*o) == "-" )
		return true;
		
		
	/* 
	  Second: the case of -x+x (=0) 
		*/
	if (ops.size() == 3 && ops.front() == "-" + ops.back() && (*o) == "+" )
		return true;
		
		
	/*
		No test passed
		*/
		
	return false;
	
} /* RedundantEquation */
  
  /////////////////////////////////////////////////////////////////
  
  /*
  	if an entire formula  consists of negated operands,
  	replaces negative signes by positive signs and returns the new format
  	*/
  string RemoveUnnecessaryNegatives (const string& formula)
  {
  		
  		// TODO: Implement a system for conversion of negative products  		
  		if (!formula.length())
  			return formula;
  			
  		//if (strstr (formula, "*") || strstr (formula, "/"))
  		//	return formula;
  			
  		string result = "";
		list<string> ops = SeparateOperands (formula);

		if (!BeginsWith ("-", ops.front()))
			return formula;
			
		list<string>::const_iterator o = ops.begin();
		
		// initial orientation
		if (ops.front() != "-") 
		{
			result = StripB ("-", ops.front());
			o++;
		} /* if */

		for (; o != ops.end(); )
		{
			
			// skip multiplication and division
			if (*o == "*" || *o == "/" || *o == "^")
			{
				result +=  *o; 
				o++;
				
				if (o != ops.end()) 
				{
					result += *o; 
					o++;
				} /* if */				
			} /* if */	
			
					
			if (*o == "-")
			{
				// we should have a - sign at this point			
				o++; 
				if (o != ops.end())
				{
					result += " + " + *o;
					o++; 
				} /* if */
					
			} /* if */
			else if (BeginsWith ("-", *o))
			{
				result += " + " + StripB ("-", *o);			
				o++;
			} /*else if */
	
			else 
			{
				return formula;				
			} /* else */


		} /* for */

		result = StripB (" + ", result);
		result = StripB (" ", result);

		return result;
  } /* RemoveUnnecessaryNegatives */

  
