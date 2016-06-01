#define SCORE_H

/*
    class score_t
        "animated" score objects
        */
        
        
class waveform_t;
class sprite_t;

class score_t
{
    public:
        score_t ();
        
        // Play sprite in foreground
        void Play  (sprite_t* sprite, frequency_t freq, timepoint_t length);
        
        // Play score in foreground
        void Play  (score_t*  score);
        
        // Play sprite in background
        void PlayBG  (sprite_t* sprite, frequency_t freq, timepoint_t length);
        
        // Play score in background
        void PlayBG  (score_t*  score);
   
        // Accessors for framerate
        void SetFrameRate (const double);
        double FrameRate () const;

        
        vector <waveform_table_t> Render (const double); 
        // Note: Render (const timepoint_t length)  is only available for sound_t objects
        // which are the equivalent of 'infinite' sprites
        
        // Generate frame at specific timepoint
        waveform_table_t GetFrame (const timepoint_t&);
                
        score_t (const string& sprite_name);
        string Name() const; // accessor for name
        
    private:  
        vector <waveform_table_t> frames;
        timepoint_t         time;
		list <waveform_t>   waveforms;        
        list <unsigned int> waveform_time;
        
        vector <action_t> actions;
        
        double framerate;  
        frequency_t freq;
        
        timepoint_t duration;
        bool duration_computed;
        
        
        string name;
}; /* score_t */

score_t* GetScore (const string& identifier);


