// Some built in mathematical operators
// included from run_function.cpp

    // TODO: do we to call Eval(?
	// Internal assignment command
	else if (function_name == "_OP_ASSIGN")
	{
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (2);
		string value = Eval (arguments.back());
		GetOrCreateVariable (arguments.front())->SetValue (value);		
		return value;
	} // else if - _OP_ASSIGN internal assignment command

	
	// _OP_ADD which is either arithmetic addition or concatenation
	else if (function_name == "_OP_ADD")
	{
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (2);
		string arg1 = arguments.front();
		string arg2 = arguments.back();
		string result;
		
		// 
		// Concatenation
		
		if (OperationType (arg1) == TYPE_TEXT || OperationType (arg2) == TYPE_TEXT)
		{
		
			
			result = "\"" + EvalSQ(arg1) + EvalSQ(arg1) + "\"";
		} // if

		
		// unsupported form of addition
		/* else if 
		{
			error ("unsupported form of addition");
		} */ // else if 
				
		// numerical addition
		// All possible error checks are to be completed by this point in the form of `else if's'
		else 
		{
			result = NumberToString (_stof (Eval(arg1)) + _stof (Eval(arg2)));
		} // else if
		
		return result;
		
	}  // else if - _OP_ADD
	

    // TODO: do we need to call Eval( ?
	// Arithmatic and logical operators
	else if (function_name == "_OP_MULTIPLY" 
                or function_name == "_OP_DIVIDE"
                or function_name == "_OP_SUBTRACT"
                
                or function_name == "_OP_LESS_THAN_OR_EQUAL"
                or function_name == "_OP_LESS_THAN"
                or function_name == "_OP_GREATER_THAN_OR_EQUAL"
                or function_name == "_OP_GREATER_THAN"                                
                )
	{
		// Make sure argument count is correct
		ASSERT_ARGCOUNT (2);
				
		if (OperationType (arguments.front()) == TYPE_TEXT 
		      or OperationType (arguments.back()) == TYPE_TEXT)
		      error ("wrong argument type for multiplication");
		            
	    double result_num;

        if (function_name == "_OP_LESS_THAN_OR_EQUAL")
            result_num = _stof (Eval (arguments.front())) <= _stof (Eval (arguments.back())); 
            
        else if (function_name == "_OP_LESS_THAN")
            result_num = _stof (Eval (arguments.front())) < _stof (Eval (arguments.back())); 
        
        else if (function_name == "_OP_GREATER_THAN_OR_EQUAL")
            result_num = _stof (Eval (arguments.front())) >= _stof (Eval (arguments.back())); 
        
        else if (function_name == "_OP_GREATER_THAN") 
            result_num = _stof (Eval (arguments.front())) > _stof (Eval (arguments.back())); 
        
        else if (function_name == "_OP_MULTIPLY")
            result_num = _stof (Eval (arguments.front())) * _stof (Eval (arguments.back()));     
              
        else if (function_name == "_OP_DIVIDE")
            result_num = _stof (Eval (arguments.front())) / _stof (Eval (arguments.back()));    
               
        else if (function_name == "_OP_SUBTRACT")
            result_num = _stof (Eval (arguments.front())) - _stof (Eval (arguments.back()));       
        
        return NumberToString (result_num);
                
	} // Numerical only operators
