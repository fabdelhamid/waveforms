#include "../wavegen.h"

sound_t::sound_t (const string& w_name)
{
	name = w_name;
} // waveform_t::waveform_t

void sound_t::SetTime (const timepoint_t t)
{
	time = t;
} // sound_t::SetTime

timepoint_t sound_t::Time () const
{
	return time;
} // sound_t::SetTime


sound_t* GetSound (const string& identifier)
{
	for (int i = 0; i < sounds.size(); i++)
	{
		if (sounds[i].Name() == identifier)
			return &(sounds[i]);
	} // for
	
	// All checks failed.
	return NONE;
		
} //GetSound

//accessor for name
string sound_t::Name() const // accessor for name
{
    return name;
} // sound_t::Name 
