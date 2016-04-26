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

	
	/*
		Time command i.e. new keyframe 
		*/
  
	if (function_name == "time")
	{
		// Make sure argument count is correct
		ASSERT_ARGCOUNT (1);
		
		
		if (currently_in_sprite_block)
			CURRENT_SPRITE.SetTime (_stof (argument_0));
		else if (currently_in_sound_block)
			CURRENT_SOUND.SetTime (_stof (argument_0));
		else
			error ("time command not allowed here");
				
	} /* if - time */
	
	
	/* 
		`set' command - set wavepoint value exactly at specified location
		*/
	else if (function_name == "set")
	{
         

		// Make sure argument count is correct
		ASSERT_ARGCOUNT (2);
		
		CURRENT_WAVEFORM.AddWavepoint (WAVEPOINT_AT ,   // type
										atoi (arguments.front().c_str()),   // location
										atoi (arguments.back().c_str()));	// value
	} /* else - set */
		
	/* 
		`setb' command - set wavepoint value at the insant after specified location
		*/
	else if (function_name == "setb")
	{
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (2);
		
		CURRENT_WAVEFORM.AddWavepoint (WAVEPOINT_BEFORE,   // type
										_stof (EvalSQ (arguments.front())),   // location
										_stof (EvalSQ (arguments.back())));	// value			
	} /* else - setb */
		

	/* 
		`seta' command - set wavepoint value at the insant after specified location
		*/
	else if (function_name == "seta")
	{
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (2);
	    AssertArgtype (arguments.front(), TYPE_NUM);
	    AssertArgtype (arguments.back(),  TYPE_NUM);
		
		CURRENT_WAVEFORM.AddWavepoint (WAVEPOINT_AFTER,   // type
										_stof (EvalSQ (arguments.front())),   // location
										_stof (EvalSQ (arguments.back())));	// value			
	} /* else - seta */

	/* 
		`setmethod' command - set interpolation method
		*/
	else if (function_name == "setmethod")
	{
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (2);
	    AssertArgtype (arguments.front(), TYPE_NUM);   // location
	    AssertArgtype (arguments.back(),  TYPE_TEXT);  // method
		
		CURRENT_WAVEFORM.SetInterpolationMethod (_stof (EvalSQ (arguments.front())),   // location
           									   	    EvalSQ (arguments.back()));	// interpolation method			
	} /* else - setmethod */

	
	
	/* 
		`morph' command - morph a waveform to another in a sprite or sound container.
		*/
	else if (function_name == "Morph")
	{
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (2);
		
		list<string>::const_iterator arg = arguments.begin();

		waveform_t* final     = GetWaveform  (*arg++);
		timepoint_t time      = GetTimepoint (*arg)  ;


		if (currently_in_sprite_block)
			CURRENT_SPRITE.MorphTo (final, time);
		else if (currently_in_sound_block)
			CURRENT_SPRITE.MorphTo (final, time);
		else
			error (function_name + " command not allowed here");
					
		
	} /* else - Morph */	

	/* 
		`Load' command 
		*/
	else if (function_name == "Load")
	{
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (1);
		
		list<string>::const_iterator arg = arguments.begin();

		waveform_t* final     = GetWaveform  (*arg++);


		if (currently_in_sprite_block)
			CURRENT_SPRITE.Load (final);
		else if (currently_in_sound_block)
			CURRENT_SPRITE.Load (final);
		else
			error (function_name + " command not allowed here");
					
		
	} /* else - Load */	


	/* 
		`Include' command 
		*/
	else if (function_name == "include")
	{
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (1);
		
		list<string>::const_iterator arg = arguments.begin();

		string path = EvalSQ (*arg++);

        // Include is not allowed inside any blocks
		if (currently_in_any_block)
			error (function_name + " command not allowed here");
		
		ReadFile (path);
		
		
        //error (function_name + " command not supported yet.");
					
		
	} /* else - include */	


	//  REMOVED: `rem' command was removed
	
	/*
		Unknown function.
		TODO: custom functions.
		*/
	else
	{
		error ("Unknown function `" + function_name + "' ");
	} /* else */
	
	return "";
	
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

