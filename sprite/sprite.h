

/*
    class sprite_t
        "animated" sound objects
        */
        
        
class waveform_t;
//

enum action_type_t
{
    ACTION_LOAD,
    ACTION_MORPH,
    //ACTION_INVERT,
    ACTIONS
}; // action_type_t



typedef struct {
    unsigned short type;
	action_type_t   action;
  	   waveform_t*  waveform;
	  timepoint_t   length;
	  amplitude_t   amplitude;
} action_t;

class sprite_t
{
    public:
        void SetTime (const timepoint_t);     /* Set current timestamp */
        timepoint_t Time() const;           /* Read current timestamp */        
        
        /*
        	Adding and removing waveform
        	*/
        void AddWaveform                 (waveform_t waveform, unsigned int time);
        void AddWaveformAtCurrentTime    (waveform_t waveform);        
        void RemoveWaveform              (waveform_t waveform, unsigned int time);
        
  	    // void MoveWavepoint   (const location_t wvpnt_location, const amplitude_t initial, const amplitude_t final, const timepoint_t time)    

		/*
			"Rendering" waveform
			*/
        amplitude_t GetAmplitudeAtlocation (const location_t wvpnt_location, timepoint_t time) const;
        
        // amplitude_t GetAmplitudeAtlocation (const location_t wvpnt_location) const;       
        void MorphTo (waveform_t* final, timepoint_t length);
        void Load    (waveform_t* final);
        
        void DoAction (action_t&);
        //output_t Render() const;
        
        sprite_t (const string& sprite_name);
        string Name() const; // accessor for name
        
    private:  
        timepoint_t time;
		list <waveform_t> waveforms;        
        list <unsigned int> waveform_time;
        
        list <action_t> actions;
        
        string name;
}; /* sprite_t */

sprite_t* GetSprite (const string& identifier);


