/*
    sound_t objects should consist of:
        (optional) intro sprite
        pseudo-infinite loop
        (optional) outro sprite
*/

class sound_t
{
    public:
        void SetTime(unsigned int);     /* Set waveform timestamp */
        unsigned int Time() const;      /* Read waveform timestamp */        
        
        /*
        	Adding and removing waveform
        	*/
        void AddWaveform                 (waveform_t waveform, unsigned int time);
        void AddWaveformAtCurrentTime    (waveform_t waveform);        
        void RemoveWaveform              (waveform_t waveform, unsigned int time);
        void Hold     (const timepoint_t);      

	//	void MoveWavepoint   (const location_t wvpnt_location, const amplitude_t initial, const amplitude_t final, const timepoint_t time)    

		/*
			"Rendering" waveform
			*/
        amplitude_t GetAmplitudeAtlocation (const location_t wvpnt_location) const;
       // amplitude_t GetAmplitudeAtlocation (const location_t wvpnt_location) const;
        
        sound_t (const string& sound_name);
        string Name() const; // accessor for name
        
    private:  
        unsigned int time;
		list <waveform_t> waveforms;        
        list <unsigned int> waveform_time;
        string name;
}; /* sound_t */

sound_t* GetSound (const string& identifier);


