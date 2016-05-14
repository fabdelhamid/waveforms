// Some built in methods
// included from run_function.cpp
	
	
	/* 
		`set' command - set wavepoint value exactly at specified location
		*/
	/* 
		`setb' command - set wavepoint value at the insant after specified location
		*/
	/* 
		`seta' command - set wavepoint value at the insant after specified location
		*/
		
	else if (function_name == "set"
                or function_name == "setb"
                or function_name == "seta")
	{
         

		// Make sure argument count is correct
		ASSERT_ARGCOUNT (2);
		
		double w_location = _stof (Eval (arguments.front()));
		double value      = _stof (Eval (arguments.back()));		
		
		// location error checks
		if (w_location < 0 
             or w_location > waveforms.back().Samples()
             or floor(w_location) != w_location)
             error ("location value specified is invalid or out of range");

		// value error checks
		if (abs (value) > MAX_AMPLITUDE or floor(value) != value)
             error ("amplitude value specified is invalid or out of range");

    	if (function_name == "set")	
		  CURRENT_WAVEFORM.AddWavepoint (WAVEPOINT_AT ,   // type
										w_location,   // location
										value);        // value
    	else if (function_name == "setb")	
		  CURRENT_WAVEFORM.AddWavepoint (WAVEPOINT_BEFORE,   // type
										w_location,   // location
										value);        // value
										
        else if (function_name == "seta")	
		  CURRENT_WAVEFORM.AddWavepoint (WAVEPOINT_AFTER,   // type
										w_location,   // location
										value);        // value

        return "NaV";										
	} /* else - set */

		


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
	} // else - setmethod 

	
	/* 
		`Hold' command - hold current time point for a speicifed duration
		*/
	else if (function_name == "Hold")
	{
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (1);

		
		timepoint_t time;
        if (OperationType (arguments.back()) == TYPE_TIMEPOINT)
            time = GetTimepoint (arguments.back());
        else            
            time = GetTimepoint (Eval(arguments.back()));

        /////////////////////////////////////////////////
        
		if (currently_in_sprite_block)
			CURRENT_SPRITE.Hold (time);
			
		else if (currently_in_sound_block)
			CURRENT_SPRITE.Hold (time);
			
		else
			error (function_name + " command not allowed here");
					
		
	} // else - Hold 	

	
	/* 
		`morph' command - morph a waveform to another in a sprite or sound container.
		*/
	else if (function_name == "Morph")
	{
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (2);

		waveform_t* final     = GetWaveform  (arguments.front());
		
		// invalid waveform specified
		if (final == NULL)
		  error ("invalid waveform specified");
		
        /////////////////////////////////////////////////		
		
		timepoint_t time;
        if (OperationType (arguments.back()) == TYPE_TIMEPOINT)
            time = GetTimepoint (arguments.back());
        else            
            time = GetTimepoint (Eval(arguments.back()));

        /////////////////////////////////////////////////
        
		if (currently_in_sprite_block)
			CURRENT_SPRITE.MorphTo (final, time);
			
		else if (currently_in_sound_block)
			CURRENT_SPRITE.MorphTo (final, time);
			
		else
			error (function_name + " command not allowed here");
					
		
	} // else - Morph 	

	/* 
		`Load' command
		*/
	else if (function_name == "Load")
	{
		// Make sure argument count is correct		
		ASSERT_ARGCOUNT (1);
		
		list<string>::const_iterator arg = arguments.begin();

		waveform_t* final     = GetWaveform  (*arg++);
		
		if (final == NONE)
		  error ("invalid waveform specified");

		if (currently_in_sprite_block)
			CURRENT_SPRITE.Load (final);
			
		else if (currently_in_sound_block)
			CURRENT_SPRITE.Load (final);
			
		else
			error (function_name + " command not allowed here");
					
		
	} // else - Load 	
