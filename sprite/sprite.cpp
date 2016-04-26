#include "../wavegen.h"

sprite_t::sprite_t (const string& w_name)
{
	name = w_name;
} // waveform_t::waveform_t

void sprite_t::SetTime (const timepoint_t t)
{
	time = t;
} // sprite_t::SetTime

timepoint_t sprite_t::Time () const
{
	return time;
} // sprite_t::SetTime


sprite_t* GetSprite (const string& identifier)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		if (sprites[i].Name() == identifier)
			return &(sprites[i]);
	} // for
	
	// All checks failed.
	return NONE;
	
} //GetSprite

// amplitude_t GetAmplitudeAtlocation (const location_t wvpnt_location) const;       
void sprite_t::MorphTo (waveform_t* final, timepoint_t length)
{
    action_t action;
    action.action   = ACTION_MORPH;
    action.waveform = final;
    action.length   = length;
    DoAction (action);
}	/* sprite_t::MorphTo */

void sprite_t::Load (waveform_t* waveform)
{
    action_t action;
    action.action   = ACTION_LOAD;
    action.waveform = waveform;
    DoAction (action);
}	/* sprite_t::Load */


//accessor for name
string sprite_t::Name() const // accessor for name
{
    return name;
} // sprite_t::Name 

void sprite_t::DoAction (action_t& action)
{
    actions.push_back (action);
} // sprite_t::DoAction
