#include "../wavegen.h"

sprite_t::sprite_t (const string& w_name):framerate(SPRITE_DEF_FR),duration_computed(false)
{
	name = w_name;
} // sprite_t::sprite_t


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
    RecordAction (action);
}	// sprite_t::MorphTo 

void sprite_t::Load (waveform_t* waveform)
{
    action_t action;
    action.action   = ACTION_LOAD;
    action.waveform = waveform;
    action.length   = 0;
    RecordAction (action);
}	/* sprite_t::Load */

void sprite_t::Hold (const timepoint_t t)
{
    action_t action;
    action.action   = ACTION_HOLD;
    action.length   = t;
    RecordAction (action);
}	/* sprite_t::Load */

//accessor for name
string sprite_t::Name() const // accessor for name
{
    return name;
} // sprite_t::Name 

void sprite_t::RecordAction (action_t& action)
{
    actions.push_back (action);
} // sprite_t::RecordAction


// Accessors for frame rate
void sprite_t::SetFrameRate (const double fr)
{
    framerate = fr;
    frames.clear ();    
} // sprite_t::SetFrameRate

double sprite_t::FrameRate () const
{
    return framerate;
} // sprite_t::FrameRate

// Accessors for frequency
void sprite_t::SetFreq (const frequency_t f)
{
    freq = f;
    frames.clear ();    
} // sprite_t::SetFreq

frequency_t sprite_t::Freq () const
{
    return freq;
} // sprite_t::Freq


waveform_table_t sprite_t::GetFrame (const timepoint_t& tp)
{
    
    waveform_table_t result;
    //   What to do:
    
    /*
              Go through actions, executing them (i.e. rendering frames), 
              until next action is after specified timepoint. Compute 
              timepoint of last action based on arguments of ecountered Morph 
              and Hold commands. Now check that last action.
                    
              Obviously an exception is when tp = 0, in which case the action
              to take is to load the waveform (normally a load action)
              
              
    */
  
    // First frame  
    if (tp == 0 || actions.size() == 1)
    {
        // Make sure first action is a load
        if(actions[0].action != ACTION_LOAD)
            error ("first acion in sprite must be a load");

        return GenerateWaveformFrequencyTable (*actions[0].waveform, this->freq);
    } // if
    
    // Frame number > 0
    else
    {
        timepoint_t timepoint_at_i = 0;
        int i;
        // skip through the two points interested
        for (i = 0; i < actions.size()  /* - 1*/ ; timepoint_at_i += actions[i].length, i++)
        {            
            actions[i].timepoint = timepoint_at_i;
            timepoint_t next_tp = timepoint_at_i + actions[i].length;
            
            bool condition = (next_tp - tp) > DBL_PRECISION_THOLD;
              
            // target timepoint is between timepoints of two actions
            if ((tp >= (timepoint_at_i - DBL_PRECISION_THOLD)) && condition)
                return GetActionWaveformTable (i, tp);
            
        } // for -- through actions
        
        if (i >= actions.size())
        {
            error ("sprite_t::GetFrame: requested index exceeds action size"); 
        } // if 
        
        /*
        cout << "Relevant i: " << i << " out of " << actions.size() << endl;        
        error ("sprite @ tp>0 not supported yet."); 
        */
        
    } // else
        
    timepoint_t timepoint_of_last_action;        
      

} // sprite_t::GetFrame

// Compute waveform table for a given action
waveform_table_t sprite_t::GetActionWaveformTable (const unsigned int i, const timepoint_t tp_of_interest)
{
	
	freq = this->Freq();
	
    waveform_table_t result;
    unsigned int last_relevant_i ;

    // For interpolation
    waveform_t* last_rel_wf;
    waveform_t* next_wf; 
    
    switch (actions[i].action)
    {
        case ACTION_LOAD:
            return GenerateWaveformFrequencyTable (*actions[i].waveform, freq);
                
        case ACTION_HOLD:
            
            // TODO: support for successive Holds
            if (i == 0 || (actions[i-1].action != ACTION_LOAD &&
                                actions[i-1].action != ACTION_MORPH)) 
                error ("invalid mode for Hold command");
           
            return GenerateWaveformFrequencyTable (*actions[i-1].waveform, freq);

    /*            
              If last action was a Morph, then construct a waveform(_table_t) in 
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

            
        case ACTION_MORPH:
            
            timepoint_t x1,x2,x3;
            amplitude_t y1,y2,y3;
            
            last_relevant_i =  i-1;
        
            // skip `Hold' commands
            while (last_relevant_i && actions[last_relevant_i].action == ACTION_HOLD)
                last_relevant_i--;
            
            x1 = 0; //actions[last_relevant_i].timepoint;
            x2 = tp_of_interest - actions[i].timepoint;
            x3 = actions[i].length;
          
            last_rel_wf = actions[last_relevant_i].waveform;
            next_wf = actions[i].waveform;
            
            return LinearWaveformInterpolation (x1,x2,x3, last_rel_wf, next_wf, freq);
                
        default:
            error ("unsupported action");
    } // switch
    
    return result;
} // GetActionWaveformTable


// Computes entire duraction of sprite
timepoint_t sprite_t::Duration ()
{
    
    // Can read duration from cache.
    if (duration_computed)
    	return duration;
    	
    // Duration was not computed, recompute duration
    
    duration = 0;
    for (int i = 0; i < actions.size(); i++)
    	duration += actions[i].length;


	duration_computed = true;
	return duration;
	
} // sprite_t::Duration 



