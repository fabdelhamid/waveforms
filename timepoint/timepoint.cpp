#include "../wavegen.h"


// return a proper timepoint (in milliseconds) from a string
timepoint_t GetTimepoint (const string& identifier)
{
	timepoint_t result;

	// ms format	
	if (EndsWith ("ms", identifier) && IsNumericValue (StripE("ms",identifier)))
	{
		result = _stof (StripE("ms",identifier));
		return result;
				
	} // if 


	//s format
	if (EndsWith ("s", identifier) && IsNumericValue (StripE("ms",identifier)))
	{
		result = _stof (StripE("ms",identifier)) * 1000;
		return result;
				
	} // if 


	//s format
	if (IsNumericValue (StripE("ms",identifier)))
	{
		result = _stof (identifier);
		return result;
				
	} // if 

	
} // GetTimepoint
