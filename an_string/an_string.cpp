#include "../wavegen.h"
using namespace std;
/*

    functions:
    
    Compare 

    
    BeginsWith
    EndsWith

    StripB
    StripE
    
    BW_s, EW_s
    nBW_s, nEW_s

    
    BW_s, EW_s Check and strip if check successful
    
    StripB
    StripE
    
    
    StripParameters
    
*/


bool Compare (const string &key, const string &context, location l)
{
     if (key.length() > context.length())
	   return false;
	   
	 if (l + key.length() > context.length())
	 	return false;
     
     for (int i = 0; i < key.length() && ((l + i) < context.length()) ; i++)
       if (key.at(i) != context.at(l + i))
	   return false;
       
       return true;
} /* compare */

bool BeginsWith (const string &str, const string &context)
{
	if (context.length() < str.length())
		return false;
	else if  (context.length() == str.length())
		return str == context;
	
   return Compare (str, context, 0);      
} /* BeginsWith */

bool EndsWith (const string &str, const string &context)
{
	if (context.length() < str.length())
		return false;
	else if  (context.length() == str.length())
		return str == context;

   return Compare (str, context, context.length () - str.length ());       
} /* EndsWith */

/* Name begins with - strip and return bool */ 
bool nBW_sb (const string &key, string &context)
{
	if (!BeginsWith (key, context))
	  return 0;
	  
	context = StripB (key, context);
	return 1;
} /* nBW_sb */

//////////////////////////////////////////////    

/* Name ends with - strip and return bool */ 
bool nEW_sb (const string &key, string &context)
{
	if (!EndsWith (key, context))
	  return 0;
	  
	context = StripE (key, context);
	return 1;
} /* nEW_sb */

//////////////////////////////////////////////    

/*
    Returns location of next non-whitespace character 
    */
location Next (const string &str, location l)
{
	while (l < str.length()
			&&  (str.at(l) == ' '
					|| str.at(l) == '\n'
					||  str.at(l) == '\r'
					|| str.at(l) == '\t'
                    || str.at(l) == '%'))                    
	{
        if (str.at(l) == '%') 
        {
            l = NextLine (str, l);
                
            continue;
        } /* if */
        else        
            l++;
    } // while
	return l;       
} /* Next */


/*
    Next with line number support 
    */
location Next (const string &str, location l, unsigned int& line_number)
{
	while (l < str.length()
			&&  (str.at(l) == ' '
					|| str.at(l) == '\n'
					||  str.at(l) == '\r'
					|| str.at(l) == '\t'
                    || str.at(l) == '%'))                    
	{

        if (str.at(l) == '\n') 
            line_number++;

        if (str.at(l) == '%') 
        {
            l = NextLine (str, l);
                line_number++;
                
            continue;
        } /* if */
        else        
            l++;
    } // while
	return l;       
} /* Next */


/* Returns location of new line */
location NextLine (const string& str, location l)
{
	while (l < str.length()
					&& str.at(l) != '\n')
		l++;	 
	return l;       
    
} /* NextLine */

//////////////////////////////////////////////    

/* TODO: Skip Comments */

/*
	Skip to previous non-whitespace character in an std::string
	*/
location Prev (const string &str, location l)
{	     
	if (l <= 0)
		return 0;
	
	if (l == str.length()
		&& !(str.at(l-1) == ' '
				|| str.at(l-1) == '\n'
				||  str.at(l-1) == '\r'
				|| str.at(l-1) == '\t'))
		return l;
	else
		l--; 
	
	while (l >= 0 
			&& (str.at(l) == ' '
				|| str.at(l) == '\n'
				||  str.at(l) == '\r'
				|| str.at(l) == '\t'))
	     l--;
	     
	return l;       
} /* Prev */

//////////////////////////////////////////////    



/* TODO: Skip Comments */
location NextWithinLine (const string &context, location l)
{
       while (context.at(l) == ' ' ||  context.at(l) == '\t')
                 l++    ;
                 
        return l;         
} /* PrevWithinLine */

//////////////////////////////////////////////    

/* TODO: lastWithinLine */
/* Strip from the beginning */
string StripB (const string &key, const string &context)
{
   if (!BeginsWith (key, context))
      return context;
   
   string result = "";
   
   for (int i = key.length (); i < context.length (); i++)
       result += context.at (i);
       
   return result;    
      
} /* StripB */

//////////////////////////////////////////////    

/* Strip from the end */
string StripE (const string &key, const string &context)
{
   if (!EndsWith (key, context))
    return context;
   
   string result = "";
   
   for (int i = 0 ; i < context.length () - key.length (); i++)
       result += context.at (i);
       
       return result;
      
} /* StripE */

//////////////////////////////////////////////    


/* Strip from the end */
void _StripE (const string &key, string &context)
{
	if (!EndsWith (key, context))
		return;
	string result = "";	
	string t_c = context;
	int length = t_c.length() - key.length();
	for (int i = 0 ; i < length ; i++)
		result += context.at (i);
	context = result;      
} /* _StripE */

//////////////////////////////////////////////    

/*
   PARSING
  */

string* StripParameters (string &context)
{
} /* StripParameters */


/*
	Skip delimiters 
	*/
location Skip (const char d1, const char d2, const string &context, location l)
{	
	if (l >= context.length())
		return context.length();
			
	if (context.at(l) != d1)
	  return l; 	
	l++;
		
	int nests = 1;
	int i;
	
	
	for (i = l; i < context.length(); i++)
	{  
	
	    if (context.at (i) == d1 && !InAnyQuote(context, i))  
		   nests++;
        else if (context.at (i) == d2 && !InAnyQuote(context, i)) 
		  nests--;
        
        if (!nests)
         {
         	// i--;
         	 break;
		 } /* if */
         
	} /* for */
	

   if (i == context.length() && nests)
     error ("Unbalanced delimeter " + d1);

   return i;
	
} /* Skip */

// Finds out if a specific location inside a string is located within a quote.
bool InQuote (const char delim, const string &context, location l)
{
	bool v = 0;
    location  i = 0;
    
	for ( i = 0; i < context.length() && i < l;  i++)
	{
        
    
        
		if (context.at(i) == '\\')
			i++;
			
		else if (context.at(i) == delim)
        {
			v = !v;	
			
        } //else if
        
	    i = Next (context, i);	
	} /* for */
	
   return v;	
} // InQuote

/* 
   Modified to handle - and + prefixes
*/
bool IsNumber (const std::string& o_s)
{
	
	string s = o_s;
	
	s = StripB ("+", s);
	s = StripB ("-", s);
	
    for (string::const_iterator c = s.begin(); c != s.end(); c++)
    	if (!isdigit (*c) && ((*c) != '.'))
    		return false; 
    		
    return true;
}

list<string> SeparateArguments (const string &o_statement)
{
	list<string> result;

	string statement = StripParens (o_statement);
	if (!statement.length())
		return result;
	
	string argument = "";

	for (location i = 0; i < statement.length(); i++)
	{
        if ((statement.at(i) == '(') && !InAnyQuote (statement, i))
        {
            location i_skip = SkipParens (statement, i) + 1;
            argument += StrFromTo (statement, i, i_skip);
            i = i_skip;
            
            continue;
        } // if
        
		if (statement.at(i) != ',')
            argument += statement.at(i);
		else 
		  {
		  	result.push_back(argument); 
		    argument = ""; 
		  }
	} /* for */

	// since there is no trailing ','
	result.push_back(argument); 

	return result;
} /* SeparateArguments */


list<string> OperandsOnly (const list<string>& all, unsigned int x)
{
	list <string> result;
	for (list<string>::const_iterator o = all.begin(); o!= all.end(); o++)
	   if (!IsOperator (*o))
		  result.push_back(RemoveSideEffects (*o));
		  
		  
	/* Strip Empty entries */
	/* TODO: remove after IsOperator is fixed */
	for (list<string>::iterator o = result.begin(); o!= result.end(); o++)
		if (!(*o).length())
		{
			result.erase(o);
			o = result.begin();
		} /* if */		  
		  
	return result;
} /* OperandsOnly */


list<string> OperatorsOnly (const list<string>& all, unsigned int x)
{
	list <string> result;
	for (list<string>::const_iterator o = all.begin(); o!= all.end(); o++)
	   if (IsOperator (*o))
		  result.push_back(*o);
		  
	/* Strip Empty entries */
	/* TODO: remove after IsOperator is fixed */	
	for (list<string>::iterator o = result.begin(); o!= result.end(); o++)
		if (!(*o).length())
		{
			result.erase(o);
			o = result.begin();
		} /* if */		  		  
		  
	return result;
} /* OperandsOnly */


/* Delete an entry one time from a list */
// TODO: Rewrite as template
void DeleteOnce (const string& key, list <string>& container)
{
	for (list <string>::iterator o = container.begin(); o != container.end(); o++)
		if (*o == key)
		{
			container.erase (o);
			return;
		} /* if */
} /* DeleteOnce */

/*
   TODO:  detect leading + and - signs
  */
list<string> SeparateOperands (const string statement)
{
		
	#define add_previous_operand() if (current_operand.length()) result.push_back(current_operand); current_operand = ""
	
	list<string> result;
	string current_operand = "";
	
	
	for (int i = 0; (i = Next (statement, i)) < statement.length(); i++)
	{
		
		operator_t type;
		function_t function;
		
		// In quote; copy operand as is
		if (InAnyQuote (statement, i))
		{
            do
            {
                current_operand += statement.at(i++);
            } // do 
            while (i < statement.length() && InAnyQuote (statement, i));
            add_previous_operand();    
        } // if - in a quote
        
	    /* detected a new operator */
		else if (type = CmpOperator (statement, i))
		{
			
			add_previous_operand();	
			
			// + then -	: ignore the +

			if ((result.back() == "+") && opsign[type] == "-" && StrEmptyOrWhitespace(current_operand))
			{				
				//remove the +
				result.pop_back();
				current_operand  = "-";	
				add_previous_operand();
			} /* if */		
			
		
			//Special case: operation starts with -
			else if (result.empty()  && (opsign[type] == "-") && StrEmptyOrWhitespace(current_operand))
			{

				current_operand = "-";
			} /* if */
			
			// Special cases: ^/*// followed by - (as in e^-5t)                    
			else if ((IsOperator (result.back())  && (opsign[type] == "-") && StrEmptyOrWhitespace(current_operand)))
			{

				
				current_operand = "-";
				
			} /* if */
			
			// op followed by +
			else if (/* result.back() == "^" */ IsOperator (result.back()) && opsign[type] == "+" && StrEmptyOrWhitespace (current_operand))
			{      
			
			
				current_operand = "";
				
			} // else if 

			else
			{
				// Might want to add support for other encodings later on, or maybe to be handled by client
				result.push_back(opsign[type]);				
			} /* else */

			i += opsign[type].length() - 1;   // the -1 is to compensate for the i++ in the for loop
			
		} // if 

		/* detected parens */
		else if (statement.at(i) == '(')
		{
			int o_i = i;
			i = SkipParens(statement, i);
			current_operand += StrFromTo (statement, o_i, i+1);
			
		} // else if 


		/* detected function */
		else if (function = CmpFunction (statement, i))
		{
			
			add_previous_operand();


			i += funcname[function].length();
			i =  Next (statement, i);
			
			/* function identfier was followed by parentheses */
			if (statement.at(i) == '(')
			  {
				int o_i = i;
				i= SkipParens (statement, o_i);
				
                result.push_back (funcname[function] + StrFromTo (statement, o_i, i + 1));
				  							
			  } /* if */
			else
			 {
                  result.push_back(funcname[function]);
	  		 } // else 					
			// skip paren's 
		} // else if 
		
		else 	 	
		{
			current_operand += statement.at(i);
		} /* else if */
		
		
	} /* for */
	
	string old_operand;
	if (current_operand.length()
		&& current_operand.at(0) == '-')
	{
		old_operand = StripB ("-", current_operand);
		current_operand = "-";
		add_previous_operand();
		
		if (old_operand.length())
		{
			current_operand = old_operand;
			add_previous_operand();
		} /* if */
			
	} /* if */
	else
		add_previous_operand();
			
	return result;
  
} /* SeparateOperands */

// Used to fix some function that corrupt quotation
location NextOrPlus1 (const string& context,location l)
{
    if (InAnyQuote (context,l))
        return l+1;
    else
        return Next (context, l);    
} //NextOrPlus1


// Enforces C-style precedence of different operators,
// and converts them to function calls 
string OperatorsToFunctionCalls (const string &statement)
{
    
	string statement_enf = EnforceOperatorPrecedence (statement);
    
    ///list <string> operands = SeparateOperands (statement);
    list <string> operands = SeparateOperands (EnforceOperatorPrecedence (statement_enf));
    
    string operator_used;
    
    // We are only interested in [Operand] [Operator] [Operand] format.
	if (operands.size() != 3 || !IsOperator (operator_used = *next(operands.begin())))
		return statement_enf;
		
	//string operand_1 = operands.front(), operand_2 = operands.back(); 
    
    
    
    string result = ophandler[CmpOperator (operator_used, 0)] + \
					"(" + OperatorsToFunctionCalls (operands.front()) + \
				    "," + OperatorsToFunctionCalls (operands.back()) + ")";
		
	return result;
} // OperatorsToFunctionCalls

// Enforce C-style operator rules
string EnforceOperatorPrecedence (const string& context_s)
{
    list <string> context = SeparateOperands (context_s);
    
   // if (context.size() == 1)
   //     return context_s;
    
    
     string final = "";
     
     for (list<string>::iterator i = context.begin(); i != context.end(); )
     {
         
         string next_op = *(next(i));
         bool is_assign_op = EndsWith ("ASSIGN", ophandler[CmpOperator (next_op, 0)]);
         
         // an assignment operator will take all RHS as one operand
         // x = y + z >> x = (y+z). 
         if (is_assign_op)
         {
               string new_op = "(";
               // first operand
               new_op += *i++ + " ";

               // operator
               new_op += *i++ + " (";
                              
               while (i != context.end())
                new_op += *i++ + " ";
                
               new_op += "))";

               final += new_op;
               
           
                
         } // if - assignment operators
         
         // multiplication: taking all operands as long another multiplaction is found
         
         // division 
         // z * x / y * z -> z * (x/y) * z
         // z * x / y / z * v -> z * (x/(y/z)) * z
         
         else if (next_op == "*")
         {
               string new_op = "(";
               // first operand
               new_op += *i++ + " ";

               // operator
               new_op += *i++ + "(";
                              
               while (i != context.end() && *next(i) == /* "*" */  next_op)
               {  
                   // operand
                   new_op += *i++ + " ";
                   
                   // operator
                   if (i != context.end())
                       new_op += *i++ + " ";
               } // while
               
               // final operand
               if (i != context.end())
                       new_op += *i++ + " ";               
               new_op += "))";
               
               final += new_op;
        } // else - multiplication
         
        else
        {
           // final_list.push_back (*i++);        
           final += (*i++);   
        } // else          
     } // for 

    // TODO: implement this in better code
   // if (final_list.size() == 1)
    //    return SeparateOperands (StripWhitespaceBE (StripParens (final_list.front())));
        
        
     return StripWhitespaceE (StripParens (final));
    	   
} // EnforceOperatorPrecedence 

string StrFromTo (const string &context, location l1, location l2)
{
  return context.substr (l1, l2-l1);
} /* StrFromTo */


/* Strip Whitespace from the begining */
string StripWhitespaceB (const string &context)
{
   return StrFromTo (context, Next (context, 0), context.length());
} /* StripWhitespaceB */


/* Strip Whitespace from the End */
string StripWhitespaceE (const string &context)
{
   return StrFromTo (context, 0, 1 +Prev (context, context.length()));
} /* StripWhitespaceE */

/* Strip Whitespace from the beginning and the end */
string StripWhitespaceBE (const string &context)
{
    
   return StrFromTo (context, Next (context, 0), 1 + Prev (context, context.length()));
} /* StripWhitespaceBE */

bool IsWhitespace (const string &str, location l)
{
   return (str.at(l) == ' '   || str.at(l) == '\n' ||  str.at(l) == '\r' || str.at(l) == '\t');
} /* IsWhiteSpace */

bool IsWhitespace (const string &str)
{
	for (int i = 0; i < str.length(); i++)
		if (!IsWhitespace (str, i))
			return false;
			
	return true;
} /* IsWhiteSpace */


void StreamAssert(istream& fin,string str)
{
     string test;
     fin >> test;
     if (test != str)
       error ("expected " + str);
} /* StreamAssert */

string tostr(float t) { 
   ostringstream os; 
   os<<t; 
   return os.str(); 
} 

/*
	Removes any number of parentheses around an expression
	*/
string StripParens (const string& formula)
{
    
    if (formula == "()")
        return "";
        
	int i      = Next (formula, 0);
	int i_skip = SkipParens (formula, i);   
	int i_end  = Next (formula, i_skip + 1);

    if (i_end && (i_skip != i) && (i_end == formula.length() )   )
	{
		
		string new_formula = StrFromTo (formula, Next (formula, i+1), i_skip );
		
		if (new_formula.at(0) != '(')
		{
			
			return new_formula;
		} /* if */
		else
		{	
			return StripParens (new_formula);
		} /* else */
		 
	} /* if */
    else 
	{
		return formula;
	} /* else */
	
} /* StripParens */

bool IsFunctionCall (const string& call)
{
	return (StripParens(call).find("(") != std::string::npos);

} /* IsFunctionCall */

// dont add & or const!!
string GetArguments ( const string & context)
{
	return StripB (GetFunctionName (context), context);
} /* GetArguments */


string GetFunctionName (const string& context)
{
	int found;

	if ((found = context.find_first_of("()")) == std::string::npos)
        return StripWhitespaceBE (context);
	else 	
		return StripWhitespaceBE (  StrFromTo (context, 0, found));		
} /* GetFunctionName */

// Remove +/- initial signs from a name
string RemoveSideEffects (string e)
{
	
	for (e = StripWhitespaceBE (e);
		  BeginsWith ("+",e)   ||  BeginsWith ("-",e); 
		  	e = StripWhitespaceBE (e))
	{
		
		e = StripB ("+",e);
		e = StripB ("-",e);
	} /* for */
			
	return e;
	
} /* RemoveSideEffects */





string FormatConstMultiplication (string& sign, float constant, string opr, string base)
{
	string identifier;
	
	if (constant == 1)
		identifier =  base;
	else if (constant == 0)
		identifier =  "";
	else if (constant < 0)
	{
		if (sign == "+") sign = "-";
		else sign = "+";
												
		identifier =  tostr (abs (constant)) + opr + base;
						
	} /* else if */
	else
	 
		identifier =  tostr(constant) + opr + base;
	
	return identifier;
	
} /* FormatConstMultiplication */


bool ListContains (const list <string>& l, const string& s)
{
	for (list<string>::const_iterator ls = l.begin(); ls != l.end(); ls++)
		if (*ls == s)
			return true;
			
	return false;
	
} /* ListContains */


/* Determines if a string contains another string */
bool Contains (const string& key, const string& container)
{
	for (int i = 0; i < container.length(); i++)
		if (Compare (key, container, i))
			return true;
			
	return false;
		
} /* Contains */

/* Replaces all instances of a string in another string */
string Replace (const string& this_str, const string& with_this, const string& in_this)
{
	
	//NOTE: Possible speed optimization oportunity
	string result = "";
	
	for (int i = 0; i < in_this.length(); i++)
	{
		if (Compare (this_str, in_this, i))
		{
			for (int x = 0; x < with_this.length(); x++)
				result += with_this.at(x);
			
			i += this_str.length () - 1;
		} /* if */
		else
			result += in_this.at(i);
		
	} /* for */
	
	return result;
	
} /* Replace */


/*
	Determines if an input is a recognized value identifier
	i.e. `Resistance (R 1)' or `Capacitance (C 2)' 
	*/
bool IsValueIdentifier (const string& expr) 
{
	string fname = GetFunctionName (expr);
	
	/*
		TODO: check if str contains '('
		TODO: maybe use funcname[FN_...] but this isn't really necessary
		*/
	if (fname == "Current" 
	     || fname == "Voltage"
	     || fname == "Impedance"
	     || fname == "Resistance"
	     || fname == "Capacitance"
	     || fname == "Inductance")
	     return true;
	     
	return false;
	
} /* IsValueIdentifier */




/* from http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c */
 bool file_exists (const std::string& name) 
{
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}


list<string>::iterator  next (list<string>::iterator  a)
{
	list<string>::iterator b = a;
	++b;
	return b;
} /* next */

list<wavepoint_t>::const_iterator  next (list<wavepoint_t>::const_iterator a)
{
	list<wavepoint_t>::const_iterator b = a;
	++b;
	return b;
} /* next */

/*
	Returns a word following the one to which delimieter points to
	example: NextWord ("hello world of c++", 8) -> "of"
	*/
string NextWord (const string & context, location l, unsigned int& line_number)
{
	string result = "";
	
	// Skip this word
	while (l < context.length() && !IsWhitespace(context, l))
		l++;

	// Skip whitespace between first and second word
	l = Next (context, l, line_number);

	location l0 = l;
	
	// Read next word	 
	while (l < context.length() && !IsWhitespace(context, l))
	{
		if (context.at(l) == '(')
			l= SkipParens (context, l);
		else
			l++;
	} // while
	
	result = StrFromTo (context, l0, l);
			
	return result; 
	
} /* NextWord */


/*
	skips two words and returns location of the first whitespace character
	after those two words.
	*/
location SkipTwoWords (const string & context, location l)
{
	/* Skip first word */
	while (l < context.length() && !IsWhitespace(context, l))
	{
		if (context.at(l) == '(')
			l= SkipParens (context, l);
		else
			l++;

	} // while
	
	// Skip whitespace between first and second word
	l = Next (context, l);
	
	
	// Skip second word
	while (l < context.length() && !IsWhitespace(context, l))
	{
		if (context.at(l) == '(')
			l= SkipParens (context, l);
		else
			l++;
					
	} //while
	
	// Skip whitespace between after second word
	l = Next (context, l);		
		
	return l;	
	
} // SkipTwoWords 

/*
	Throws an error if block_identifier is illegal, previously declared or is a reserved keyword.
	*/
void CheckLegalIdentifier (string block_identifier )
{
	
	bool illegal_name = false;
	
	if (Contains ("(", block_identifier)
		|| Contains ("[", block_identifier)
		|| Contains ("{", block_identifier)
		|| Contains ("-", block_identifier)
		|| Contains ("/", block_identifier)
		|| Contains ("?", block_identifier))
	{
		illegal_name = true;
    } // if
    
	if (IsNumber (StrFromTo (block_identifier, 0, 1)))
	{
		illegal_name = true;
    } // if
		
	if (CmpOperator (block_identifier) != OP_INVAL)
	{
		illegal_name = true;
		int opcode = (int) CmpOperator (block_identifier);
		
		
		
    } // if
		    	
	if (illegal_name)
		error ("`" + block_identifier + "' is an illegal identifier");
	
						
	if (OperationType (block_identifier) & TYPE_RESERVED)
		error ("`" + block_identifier + "' is a reserved keyword");
		
		
	else if (OperationType (block_identifier) != TYPE_INVAL)
		error ("`" + block_identifier + "' was previously defined");
	
	// name is okay	
	return;
}  // CheckLegalIdentifier


// Remove quotes from a string literal
/* string StripQuotes (const string& str)
{
	string result = StripB ("\"", str);
	result = StripE ("\"", result);
	
	return result;
} */ // StripQuotes


// Based on example at http://www.cplusplus.com/reference/string/string/find_last_of/
string GetFileName (const string& str)
{
  size_t found;
  found=str.find_last_of("/\\");  
  return str.substr(found+1);
} // GetFileName 


// Based on example at http://www.cplusplus.com/reference/string/string/find_last_of/
string GetFilePath (const string& str)
{
  
  if (!Contains ("\\", str) && !Contains ("/", str))
    return "";
     
  size_t found;
  found=str.find_last_of("/\\");
  return str.substr(0,found);
} // GetFilePath 



