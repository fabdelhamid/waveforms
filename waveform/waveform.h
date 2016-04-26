/*
    Waveform point specification type
    */

#define WAVEPPONT_NOT_FOUND  0
#define WAVEPOINT_BEFORE     1
#define WAVEPOINT_AT         2
#define WAVEPOINT_AFTER      3
#define WAVEPPONT_DELETED    4


/*
    interpolation methods 
    */
typedef struct {
    string method; // "linear", "trig", "exp", etc.
	location_t w_location;
} interpolation_data_t;


typedef struct {
    unsigned short type;
	location_t w_location;
	amplitude_t value;
} wavepoint_t;


/*
    class waveform_t
        waveform objects hold data such as timestamps and waveform data
        */
        
class waveform_t
{
    public:
        
        unsigned int Samples () const;
        void SetSamples (const unsigned int val);
        
        /*
        	Adding and removing wavepoints 
        	*/	
        void AddWavepoint (const short type, const location_t wvpnt_location, const amplitude_t value);
        // void RemoveWavepoint (const location_t wvpnt_location, const amplitude_t value);
     	// void MoveWavepoint   (const location_t wvpnt_location, const amplitude_t initial, const amplitude_t final, const timepoint_t time)    

		/*
			"Rendering" waveform
			*/
		amplitude_t GetAmplitudeAtlocation (const location_t wvpnt_location) const;
        waveform_t (const string& waveform_name, const string& block_code);
        
        string Name () const; // accessor for name
        string BlockCode () const; // accessor for block code
        
        // TODO: use vector instead of list if redeclaration will not be allowed
        list <wavepoint_t> wavepoints;    

		// Assigns a specific interpolation method to a specific region of a waveform.        
        string     InterpolationMethod (location_t) const;
        void    SetInterpolationMethod (const location_t, const string&);
        

        
    private:
        
        vector <interpolation_data_t> interpolation_data;            
        unsigned int num_samples;
	    string       name;
	    string       block_code;
		    
}; /* waveform_t */

/*
	Get a pointer to a waveform object 
	*/
waveform_t* GetWaveform (const string& identifier);

/*
     Final wrapper to get a waveform table given a specific frequency from cached list
     */
waveform_table_t* GetWaveformTable (const string& identifier, const frequency_t);


list<wavepoint_t>::const_iterator  next (list<wavepoint_t>::const_iterator a);


// To hold frequency-specific waveform tables
extern vector <waveform_table_t> waveform_tables;

// Generates tables for all waveforms in all applicable frequencies
void GenerateAllWaveformFrequencyTables ();

// Generates a table for one waveform for one applicable frequency
waveform_table_t GenerateWaveformFrequencyTable (waveform_t& waveform, frequency_t frequency);

	
	

