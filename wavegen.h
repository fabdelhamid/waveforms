// Possible choices for fft functionality
// http://fftwpp.sourceforge.net/
// implement a simple euler formula type for fft

#define ReadLoop while(1)

#define constexpr const

#define _CURRENT_CIRCUIT      (current_circuit)

#define _CURRENT_NODE         CURRENT_CIRCUIT.node.back()
#define _CURRENT_BRANCH       (CURRENT_CIRCUIT.CurrentState.branch) 
#define _CURRENT_ELEMENT      CURRENT_BRANCH.element.back()

#define CURRENT_SUPERNODE_EXISTS    _CURRENT_SUPERNODE //CURRENT_CIRCUIT.supernode.size()
#define CURRENT_BRANCH_EXISTS       CURRENT_SUPERNODE_EXISTS && CURRENT_SUPERNODE.branch.size()
#define CURRENT_ELEMENT_EXISTS      CURRENT_SUPERNODE_EXISTS && CURRENT_BRANCH_EXISTS && CURRENT_BRANCH.element.size()

#define CURRENT_CIRCUIT        (*_CURRENT_CIRCUIT)
#define CURRENT_NODE           (*_CURRENT_NODE)
#define CURRENT_BRANCH         (*_CURRENT_BRANCH)

#define CURRENT_ELEMENT        (*_CURRENT_ELEMENT)
#define CURRENT_STATE          CURRENT_CIRCUIT.CurrentState

#define CURRENT_BRANCH_EMPTY   !_CURRENT_BRANCH || CURRENT_BRANCH.EMPTY_BRANCH
typedef unsigned int ident;
typedef unsigned int counter;

/*
	Types 
	*/
#define location int
#define NONE NULL


#define location_t  unsigned int
#define amplitude_t signed int


#define item_list_t   list<item_t>  
#define coupled_item_list_t list<item_list_t>

#define voltagekey_list_t list<voltagekey_t>
#define currentkey_list_t list<currentkey_t>


#define route_t       item_list_t  
#define route_list_t  list<route_t>

#define argument_list_t list<string>

#define RELEVANT_CURRENT_THRESHOLD 10000


#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <sstream>
#include <cmath>
#include <complex>
#include <algorithm>
#define _stof(x) std::atof(x.c_str())
#include <stdio.h>
#include <string.h>

using namespace std;
#define frequency_t double

#include "./math/types.h"
#include "./timepoint/timepoint.h"
#include "./an_string/an_string.h"
#include "./error/error.h"
#include "./sprite/sprite.h"
#include "./render/render.h"
#include "./waveform/waveform.h"
#include "./function/function.h"
#include "./variable/variable.h"
#include "./sound/sound.h"
#include "./math/math.h"


// Maximum amplitude used when defining waveforms.
#define SYNTAX_MAX_AMPLITUDE 50
#define MAX_AMPLITUDE SYNTAX_MAX_AMPLITUDE
void ReadFile (const string& path);

string ReadOneStatement (const string& context, location &l, unsigned int& line_number);
void EvalCode (const string& context, unsigned int& line_number);

extern int currently_in_sprite_block;
extern int currently_in_sound_block;
extern int currently_in_waveform_block;
#define currently_in_any_block currently_in_sprite_block || currently_in_sound_block || currently_in_waveform_block
// global table to store Waveforms, Sprites and Sounds
extern vector <waveform_t> waveforms;
extern vector <sprite_t>   sprites;
extern vector <sound_t>    sounds;

// global output file properties

extern unsigned short  wav_channels, wav_sps, wav_bpsample;  


#define CURRENT_SPRITE   sprites.back()
#define CURRENT_SOUND    sounds.back()
#define CURRENT_WAVEFORM waveforms.back()

// Minimum and maximum frequencies, in Hz
#define MIN_FREQ 20
#define MAX_FREQ 14000

// Main file and path stacks
extern list <string> filename;
extern list <string> filename;

// scope
extern string scope;





