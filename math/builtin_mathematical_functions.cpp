// Some built in mathematical functions
// included from run_function.cpp

// TODO: type checks
#define SimpleFunction(fsyntax, finter) else if (function_name == fsyntax) \
	{ \
        ASSERT_ARGCOUNT (1); \
        return NumberToString (floor (finter (_stof (Eval (arguments.front())))));        \
    } // else if

SimpleFunction ("cos", cos)
SimpleFunction ("acos", acos)

SimpleFunction ("sin", sin)
SimpleFunction ("asin", asin)

SimpleFunction ("tan", tan)
SimpleFunction ("atan", atan)

SimpleFunction ("floor", floor)
SimpleFunction ("ceiling", ceil)

SimpleFunction ("sqrt", sqrt)

/*
	else if (function_name == "cos")
	{
        ASSERT_ARGCOUNT (1);
        return NumberToString (cos(_stof (Eval (arguments.front()))));        
    } // else if
*/
