#include "../wavegen.h"

type_t OperationType (const string& operation_c)
{
	

    
	// Temporary workaround
	string operation = operation_c;
	
	// Multiple operand operation. For now it's enough to return the type of the first operand.
	if (SeparateOperands(operation).size() > 1)
		return OperationType (SeparateOperands(operation).front()   );

		
	if ((EndsWith ("ms", operation) && IsNumericValue (StripE("ms",operation)))
	     || (EndsWith ("s", operation) && IsNumericValue (StripE("s",operation))))
		return TYPE_TIMEPOINT;


	if (GetWaveform (operation) != NONE)
		return TYPE_WAVEFORM;


	if (GetSprite (operation) != NONE)
		return TYPE_SPRITE;
			
	if (GetSound (operation) != NONE)
		return TYPE_SOUND;
		
	// TODO: Reserved keyword checking should eventually be serparated from regular type checking.
	// this is because something like toString(22.1) is both TYPE_RESERVED and TYPE_TEXT.
	
	// Reserved keywords

	if (operation == "Sprite"
		|| operation == "Sound"
		|| operation == "Waveform"
		|| operation == "Loop"
		
		|| operation == "set"
		|| operation == "seta"
		|| operation == "setb"
		|| operation == "setmethod"
		|| operation == "Morph"
		|| operation == "Time"
		|| operation == "amp"
		|| operation == "att"
		
		)
    return TYPE_RESERVED;
    
    // Conversion and manipulation functions
    // TODO: Smarter check through use of CmpX style functions
    if (IsFunctionCall (operation))
    {
        operation = GetFunctionName (operation);
        
        if (operation == "toText")
            return TYPE_TEXT;
            
        else if (operation == "toNumber" 
                 || operation == "sin"
                 || operation == "cos"
                 || operation == "asin"
                 || operation == "acos"
                 || operation == "tan"
                 || operation == "atan"
                 || operation == "sinc"
                 || operation == "square"
                 
                 )
            return TYPE_NUM;
            
        else if (operation == "shift"
                    || operation == "amp"
                    || operation == "att")
            return TYPE_WAVEFORM; 

        
        else if (operation == "Sprite"
					|| operation == "Sound"
					|| operation == "Waveform"
					|| operation == "Loop"
					
					|| operation == "set"
					|| operation == "seta"
					|| operation == "setb"
					|| operation == "setmethod"
					|| operation == "Morph"
					|| operation == "Time"
					|| operation == "amp"
					|| operation == "att"
					
					)
			    return TYPE_RESERVED;
           
    } // if - function call


    // String literals
    if (BeginsWith ("\"", operation))
        return TYPE_TEXT;

    // Numerical literals
    if (IsNumber (operation))
        return TYPE_NUM;

    
    // Variables: returns most recent data type stored in variable
    if (GetVariable (operation) != NONE)
        return GetVariable(operation)->ValueType();
    
	return TYPE_INVAL;
	
} // OperationType (string)

type_t OperationType (const list<string>& operation)
{
	// Multiple operand operation. For now it's enough to return the type of the first operand.	
	return OperationType (operation.front());
} // OperationType (list)
	
