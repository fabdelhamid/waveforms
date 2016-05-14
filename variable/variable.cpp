#include "../wavegen.h"

vector <variable_t> variables;

//  Retrieve variable
variable_t* GetVariable (const string& identifier)
{
	for (int i = 0; i < variables.size(); i++)
	{
		if (variables[i].Name() == identifier)
			return &(variables[i]);
	} // for
	
	// All checks failed.
	return NONE;		
} // GetVariable


// Determine a variable's Value Type
type_t variable_t::ValueType() const
{
	return OperationType (Value());
} // variable_t::ValueType


variable_t::variable_t ()
{
	this->code_evaluated = false;
} // variable_t::variable_t 


string variable_t::Name () const
{
	return name;
} // variable_t::variable_t 


// Set a value of a variable_t object
void variable_t::SetValue (const string& code)
{
	block_code = code;
	
	
	value = Eval (block_code);
	code_evaluated = true;
} // variable_t::SetValue 

// Set name of a variable_t object
void variable_t::SetName (const string& g_name)
{
	name = g_name;
} // variable_t::SetName 


// Returns current value (and not operation) of a variable
string variable_t::Value() const
{
	return value;
} // variable_t::Value

//  Add new variable
//void AddVariable (const string& name);

// GetOrCreateVariable
// Returns either a pointer to an existing variable or creates a new one 
// if specified variable does not exist
variable_t* GetOrCreateVariable (const string& name)
{
    variable_t* result = GetVariable (name);
    
    // Variable exists
    if (result != NONE)
        return result;
        
    // Variable does not exist; create new variable and push it.
    variable_t new_variable;
    new_variable.SetName (name);
    variables.push_back (new_variable);
        
    return &(variables.back());
} // GetOrCreateVariable
