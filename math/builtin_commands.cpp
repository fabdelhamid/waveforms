// Some built in commands
// included from run_function.cpp

	// print
	else if (function_name == "PRINTLN"
                or function_name == "PRINT")
	{
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (1);
		cout << EvalSQ (arguments.front());
		
		if (function_name == "PRINTLN")
		  cout << endl;
	} // else if - printing
	
	// pause
	else if (function_name == "PAUSE")
	{
        
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (0);
		system ("pause");
		
	} // else if - pause

	// pause
	else if (function_name == "QUIT")
	{
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (0);
		exit(0);
		
	} // else if - quit

	/* 
		`Include' command 
		*/
	else if (function_name == "INCLUDE" or function_name == "include")
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


