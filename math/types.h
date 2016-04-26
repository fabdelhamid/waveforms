/*
	This file defines several operation and variable types,
	as well as the functions to guess the type of an operation
	Useful when detecting errors
	*/
	
#define TYPES_H

#define type_t unsigned int
#define TYPE_INVAL        0b0
#define TYPE_WAVEFORM     0b1
#define TYPE_SPRITE       0b10
#define TYPE_SOUND        0b100
#define TYPE_TIMEPOINT    0b1000
#define TYPE_RESERVED     0b10000
#define TYPE_NUM          0b100000
#define TYPE_TEXT         0b1000000

/* enum type_t
{
   TYPE_INVAL ,
   TYPE_WAVEFORM ,
   TYPE_SPRITE,
   TYPE_TIMEPOINT,	
   TYPE_RESERVED,
   // TODO: TO BE IMPLEMENTED 
   TYPE_NUMERICAL,
   TYPE_TEXT,
   TYPES
}; // type_t  */


// Guesses what type a given variable or an operation is.

type_t OperationType (const string& operation);
type_t OperationType (const list<string>& operation);
