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

#define MATH_H

/* IMPORTANT: if two operators overlap (e.g. && and &) , the longer must be defined first. */
enum operator_t
{
   OP_INVAL, 
   OP_PLUS_ASSIGN, 
   OP_PLUS,    
   OP_MINUS_ASSIGN,    
   OP_MINUS,
   OP_MUL_ASSIGN,        
   OP_MUL, 
   OP_DIV_ASSIGN,           
   OP_DIV,
   OP_TOPOWER, 
   OP_NOTEQUAL,
   OP_ROT_LEFT,
   OP_SH_LEFT,
   OP_ROT_RIGHT,
   OP_SH_RIGHT,
   OP_SMALLER_EQ, 
   OP_SMALLER,
   OP_GREATER_EQ, 
   OP_GREATER, 
   OP_FACTORIAL, 
   OP_EQUALS, 
   OP_ASSIGN, 
   OP_AND,
   OP_BITW_AND,
   OP_OR,
   OP_BITW_OR,
   OP_INVAL_END, 
   OPERATORS
}; /* Operator */


/* Declarations */
operator_t CmpOperator (const string&, location=0);
bool IsOperator (const string&);

const string opsign   [OPERATORS] =  {
	"INV", 
	"+=", 
	"+", 
	"-=", 
	"-",
	"*=",
	"*", 
	"/", 
	"^", 
	"<>", 
	"<<<", 
	"<<", 
	">>>",
	">>",
	"<=", 
	"<", 
	">=", 
	">", 
	"!",
	"==", 
	"=",
	"&&",
	"&",
	"||"
	"|",
	"INVE", 

	};
// Operator handler identifiers (used when converting operators 
// to function calls 
// These are then handled similar to internal 
const string ophandler   [OPERATORS] =  {
	"INV", 
	"_OP_ADD_ASSIGN",      // "+=", 
	"_OP_ADD",             // "+", 
	"_OP_SUBTRACT_ASSIGN", // "-=", 
	"_OP_SUBTRACT",        // "-",
	"_OP_MULTIPLY_ASSIGN", // "*=",
	"_OP_MULTIPLY",        // "*", 
	"_OP_DIVIDE",          // "/", 
	"_OP_RAISE",           // "^", 
	"_OP_NOT_EQUAL",       // "<>", 
	"_OP_ROTATE_LEFT",     // "<<<", 
	"_OP_SHIFT_LEFT",      // "<<", 
	"_OP_ROTATE_RIGHT",    // ">>>",
	"_OP_SHIFT_RIGHT",           // ">>",
	"_OP_LESS_THAN_OR_EQUAL",    // "<=", 
	"_OP_LESS_THAN",             // "<", 
	"_OP_GREATER_THAN_OR_EQUAL", // ">=", 
	"_OP_GREATER_THAN",          // ">", 
	"_OP_FACTORIAL",             // "!",
	"_OP_EQUALS",                // "==", 
	"_OP_ASSIGN",                // "=",
	"_OP_LOGICAL_AND",           // "&&",
	"_OP_BITWISE_AND",           // "&",
	"_OP_LOGICAL_OR",   // "||"
	"_OP_BITWISE_OR",   // "|",
	"INVE",             // "INVE", 
	};
	
enum function_t
{
   FN_INVAL,
   FN_CURRENT,
   FN_VOLTAGE,
   FN_VALUE,
   FN_RESISTANCE,
   FN_INDUCTANCE,
   FN_CAPACITANCE,
   FN_IMPEDANCE,   
   FN_ADD,
   FN_SUBTRACT,
   FN_MULTIPLY,
   FN_DIVIDE,
   FN_RAISE,
   FN_EXP,
   FN_D1DT,
   FN_D2DT,
   FUNCTIONS
}; // function_t 

const string funcname [FUNCTIONS] =  {"INV", "Current", "Voltage", "Value", "Resistance", "Inductance", "Capacitance", "Impedance", "add", "subtract", "multiply", "divide", "raise", "exp", "d1dt" , "d2dt"  };
function_t CmpFunction (const string &, location=0);

enum block_t
{
   BLOCK_INVAL,
   BLOCK_WAVEFORM,
   BLOCK_SPRITE,
   BLOCK_SCORE,
   BLOCK_LOOP,
   BLOCK_IF,
   BLOCKS
}; // block_t 

const string blockname [BLOCKS] =  {"INV", "Waveform", "Sprite", "Score", "Loop", "If"};
block_t CmpBlock (const string &context, location l);


#define symbol string

	void  SetSymbol (string&);
	float GetSymbol (const string& symbol_name);
	bool  IsSymbol (const string&);

    //////////////////////////////////////////////   

/*
   We dont have to emulate all math functions because we will be sending them to OCTAVE! 
   */
   
   
string send_job_to_octave (const string& job);
string run_job_locally    (const string& job);

bool IsNumericValue   (const string& formula);
bool IsNumericValue   (const list<string>& arguments);


string RemoveUnnecessaryNegatives (const string& formula);

/* Determines the left hand side of a zero-equation is redundant or not
   for example: I1 - I1 is redundant. */
bool RedundantEquation (const string& lhs);


string GetBestForm (const string& formula);

float NumEval  (const string& operation);
string Eval    (const string& operation);

// known literals
int int_run_function (const function_t fcode, const argument_list_t& arguments);

//unknown value or known symbols
string run_function (const string function_name, const list<string>& arguments);

// Interpolates all space between two wavepoints according to a prespecified 
vector <amplitude_t> GetInterpolationVector (const waveform_t& waveform, location_t from, const amplitude_t amp_from,
											 location_t to, const amplitude_t amp_to, const unsigned int req_samples);
											  
											  
// Asserting an argument type											  
void AssertArgtype (const string& argument, const type_t type);



////////////////////////////////////////////////////
// Waveform Interpolation & Morphing
////////////////////////////////////////////////////

// Trignometric interpolation
amplitude_t TrignometricInterpolation (location_t x2, const waveform_t& waveform); 
amplitude_t CosineInterpolation (location_t x1, location_t x2, location_t x3, amplitude_t y1, amplitude_t y3); 

///////////////////////////////////////////////////////
// DSP section
////////////////////////////////////////////////////////
vector < complex <double> > dft (const vector<amplitude_t>&);


#define LinearInterpolation(x1,x2,x3,y1,y3) y1 + (x2 - x1) * (double) (y3 - y1) / (double) (x3 - x1)

