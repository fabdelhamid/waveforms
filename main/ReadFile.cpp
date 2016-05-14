#include "../wavegen.h"

// Main file and path stacks
list <string> filename;
list <string> filepath;


/*
    Reads and executes an input file
    */
void ReadFile (const string& path_orig)
{
    // Path
    string path = path_orig;
    
 	// Push file name and path 
 	// TODO: push line number
 	filename.push_back(GetFileName(path));
 	
 	if (filepath.size()) 
     	filepath.push_back(filepath.back() +  "/" + GetFilePath(path));
    else
        filepath.push_back (GetFilePath(path));

    path = filepath.back() + "/" + filename.back();
     
	ifstream fin;
	//if (argc > 1)
	//{
	//	fin.open(argv[1]);	
	//} /* if */
	//else 
	//{
	//	if (!fin) fin.open ("f:\\cpp\\NodeAnalyzer\\nodeanalyzer.in");
	//} /* else */


	fin.open (path.c_str());
	if (!fin)
	{
		error (path + ": File not found.");		
	} /* if */
	
 
    /* Read entire file into one string (required because we can have
       multiple statements in one line. context always passed as 
       reference to speed up execution. */
 
    stringstream buffer;
    buffer << fin.rdbuf();
    
    string context = buffer.str(); 

    unsigned int line_number = 1;
    
    /* We don't need fin anymore */
    fin.close();
	  
	EvalCode (context, line_number);

    // Return to old file name and path
    // TODO: pop line number
    filename.pop_back();
    filepath.pop_back();
} /* ReadFile */


/*
	Evaluate a piece of code 
	*/
void EvalCode (const string& context, unsigned int& line_number)
{

    /* This loop gets statements one at a time and executes them one by one */
    location l = 0; 
	string statement;
	
	/*
		Main read loop
		*/
	while (l < context.length())
	{
		

		l = Next (context, l, line_number);
		
		/*
			 Check for code blocks/clauses (Waveform, Sprite, etc.)
		*/
		
		block_t block;
		location delimiter_loc;
		

		if ((block  = CmpBlock (context, l)) != BLOCK_INVAL  &&  context.at(delimiter_loc = SkipTwoWords (context, l)) == '{')
		{
			
			/*
				Name of block: `Waveform Square' would return square.
				*/
			string block_identifier = NextWord (context, l, line_number);
		
			/* 
				Check for misaligned brackets 
				*/
			if (SkipBrackets (context, delimiter_loc) == context.length())
				error ("expecting '}'");
		
			/* 
				Get code inside block
				*/
			string block_code = StrFromTo (context, delimiter_loc, l = SkipCBrackets (context, delimiter_loc) - 1);
			block_code = StripB ("{", block_code);
		

			
			// Skip ending '}'
			l += 2;			
			
			/*
				For blocks that define identifier names, throw error if assigned name is illegal,
				previously declared or is a reserved keyword.
				*/
			if (block != BLOCK_LOOP && block != BLOCK_IF)				
				CheckLegalIdentifier (block_identifier);
	
			
									
			/*
				Execute Clause 
				*/
				
			/* 
			     Waveform block
			     */
			if (block == BLOCK_WAVEFORM)
			{

                
                if (currently_in_waveform_block || currently_in_sprite_block || currently_in_sound_block)
                    error ("cannot insert waveform here.");
                
                waveform_t wf (block_identifier, block_code) ;
                waveforms.push_back (wf);
                
                currently_in_waveform_block = 1;
                
                		l++;

        		EvalCode (block_code, line_number);
        		        		
        		currently_in_waveform_block = 0;
        		
            } /* if  - waveform*/ 	

            /*
                Sprite block
                */
		    else if (block == BLOCK_SPRITE)
		    {		    	
		    	
                if (currently_in_waveform_block || currently_in_sprite_block || currently_in_sound_block)
                    error ("cannot insert sprite here");

                sprite_t sprite (block_identifier);
                sprites.push_back (sprite);
                
                currently_in_sprite_block = 1;
                l++;
        		EvalCode (block_code, line_number);
        		currently_in_sprite_block = 0;
            } /* else if  - sprite */

            /*
                Sound block
                */
		  /*  else if (block == BLOCK_SOUND)
		    {
                if (currently_in_waveform_block || currently_in_sprite_block || currently_in_sound_block)
                    error ("cannot insert sprite here");

                sound_t sound;
                sprite.push_back (wf);
                
                currently_in_sound_block = 1;
        		EvalCode (block_code, line_number);
        		currently_in_sound_block = 0;
            } */ /* else if  - sound */

			
			/*
			     Loop block
			   */
			
		    else if (block == BLOCK_LOOP)
		    {
		    	
		    	
		    	//if (!IsNumericValue ())
		    	int loop_iterations = _stof (Eval (block_identifier));
		    	
                unsigned original_line_number = line_number;
                while (loop_iterations)
                {
                    line_number = original_line_number;
             		EvalCode (block_code, line_number);  
                     
                    loop_iterations = _stof (Eval (block_identifier));          
                } /* while - eval code  loop_iterations times*/
                
            } /* else if  - loop*/
            
            
            
		  
			continue;
		} /* if */
		
		/*
			Block identifier but errorneous syntax
			*/
		else if (CmpBlock (context, l))
		{
			string block_identifier = NextWord (context, l, line_number);
			
			error ("invalid block syntax for `" + block_identifier + "' ");
		} /* else if */
		
        /*
			Read one statement, skipping comments
			*/	 	 	
		statement = ReadOneStatement (context, l, line_number);
		/*
			Execute this statement 
		*/
		if (statement.length())
    		Eval (statement);
		
		
    } /* while */
	
} /* EvalCode */


/* 
    Reads and returns one statement from input file, skipping comments
*/
string ReadOneStatement (const string& context, location& l, unsigned int& line_number)
{
    string result = "";
	
	/*
		Determine location of begining of next statement
		*/
		    
    l = Next (context, l, line_number);
    
    /* 
		Copy from this location until next semi-colon ';' or end-of-line
		`Next' will account for quoted delimiters and new lines 
		*/
		
	bool inq = InAnyQuote(context,l);
	while (l < context.length() && 
			((context.at(l) != ';' && context.at(l) != '\n') || (inq)))
	{
        
        inq = InAnyQuote(context,l);
		result += context.at(l++);
		if (!inq)
    		l = Next (context, l, line_number);
	} // while 
       
	  
	if (l < context.length() && context.at(l) == ';')
		l++;
  
    
   // cout << "ROS: context[l]: " << context.at(l) << endl; 
    
    return result;
}  /* ReadOneStatement */
