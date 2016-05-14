#include "../wavegen.h"

sprite_t::sprite_t (const string& w_name):framerate(SPRITE_DEF_FR) 
{
	name = w_name;
} // waveform_t::waveform_t


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
}	// sprite_t::MorphTo 

void sprite_t::Load (waveform_t* waveform)
{
    action_t action;
    action.action   = ACTION_LOAD;
    action.waveform = waveform;
    DoAction (action);
}	/* sprite_t::Load */

void sprite_t::Hold (const timepoint_t t)
{
    action_t action;
    action.action   = ACTION_HOLD;
    action.length   = t;
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


void sprite_t::SetFrameRate (const double fr)
{
    framerate = fr;
    frames.clear ();
    
} // sprite_t::SetFrameRate

double sprite_t::FrameRate () const
{
    return framerate;
} // sprite_t::FrameRate

waveform_table_t sprite_t::GetFrame (const timepoint_t& tp)
{
    /*
        What to do:
            - Go through actions, executing them (i.e. rendering frames), 
              until next action is after specified timepoint. Compute 
              timepoint of last action based on arguments of ecountered Morph 
              and Hold commands. Now check that last action:
              
            - If last action was a Load, result waveform(_table_t) is that
              waveform.
            
            - If last action was a Morph, then construct a waveform(_table_t) in 
              which every point is the interpolation of the initial and final
              waveforms, at current location. In other words, it's a 
              waveform_table_t y2, where,
                    
                x1 = timepoint of last action
                x2 = specified time point 
                x3 = timepoint of last action + morph duration 
                
                y1i = elementwise amplitude of initial waveform (whatever was
                      there before Morph was called)
                y3i = elementwise amplitude of final waveform (first argument
                      of Morph)
                y2i = elementwise interpolation using preceding parameters.
                
                Interpolation method could optionally be user-specified.
    */
    
    cout <<  Name() << ": Will attempt to get frame at time " << tp << endl;
    cout << "action size: " << actions.size() << endl;
    
    system ("pause");
    exit (0);
} // sprite_t::GetFrame
