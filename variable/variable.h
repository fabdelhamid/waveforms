/* 
	variable related classes and functions 
*/

#define VARIABLE_H

class variable_t
{
    public:
	       	
        variable_t (/* const string& waveform_name, const string& block_code */);
        string Name () const;                // accessor for name
        
        string BlockCode () const;           // accessor for block code
		void   SetBlockCode (const string&);

        string Value () const;               // accessor for value
		void   SetValue (const string&);
		type_t   ValueType () const;		

    private:  
	    string name;
	    string value;
	    string block_code;
		bool is_array;
		
		// Determines if current block was evaluated or not 
		bool code_evaluated;
		
}; /* waveform_t */

extern vector <variable_t> variables;

//  Retrieve variable
variable_t* GetVariable (const string& name);

//  Add new variable
void AddVariable (const string& name);

