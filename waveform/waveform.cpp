#include "../wavegen.h"

waveform_t::waveform_t (const string& w_name, const string& bcode)
{
    SetSamples(100); // Default
	name = w_name;
	block_code = bcode;
} // waveform_t::waveform_t

/*
	Get a pointer to a waveform object 
	*/
waveform_t* GetWaveform (const string& identifier)
{
	
	for (int  i = 0; i < waveforms.size(); i++)
	{
		if (waveforms[i].Name() == identifier)
		{
			
			return &waveforms[i];
		} // if
	} // for

	
	// All checks failed.
	return NONE;
	
} //GetWaveform

void waveform_t::AddWavepoint (const short type, const location_t wvpnt_location, const amplitude_t value)
{
	wavepoint_t wvp;
	wvp.type = type;
	wvp.w_location = wvpnt_location;
	wvp.value    = value;
	
	wavepoints.push_back (wvp);
	
} // waveform_t::AddWavepoint

string waveform_t::Name() const // accessor for name
{
    return name;
}    //waveform_t::Name

// Generates tables for all waveforms in all applicable frequencies
void GenerateAllWaveformFrequencyTables  ()
{
	cout << "Will generate frequency tables for all applicable waveforms " << endl;
	
	
	// TODO: maybe use a list of well known frequencies?!
	// Use http://www.phy.mtu.edu/~suits/notefreqs.html
	// For musical instruments, formula is 2^(n/12), n E {-21,...,27}
	// Courtesy of http://www.intmath.com/trigonometric-graphs/music.php
	for (int n = -21; n <=27; n++)
	{
		frequency_t freq = 440 * pow(2, (double) n/12);
        for (int w = 0; w != waveforms.size(); w++) 
    		GenerateWaveformFrequencyTable (waveforms[w], freq);
	} // for
	
	return;	
} // GenerateAllWaveformFrequencyTables


vector <waveform_table_t> waveform_tables;

// Values of interest: (samples per second (Hz))
// Generates a table for one waveform for one applicable frequency
waveform_table_t GenerateWaveformFrequencyTable (waveform_t& waveform, frequency_t frequency)
{
    // Final number of samples:
    // 1/freq * wav_sps
       
    double dreq_sps  = (1/ (double) frequency) * (double) wav_sps;
    int req_sps = round (dreq_sps);
    waveform_table_t result = GenerateWaveformTable (waveform, req_sps);
    result.frequency = frequency;
    
	return result;
	
} // GenerateWaveformFrequencyTable

// Final wrapper to get a waveform table given a specific frequency from cached list
waveform_table_t* GetWaveformTable (const string& identifier, const frequency_t frequency)
{
    
    for (int i = 0; i < waveform_tables.size(); i++)
    {
        if (waveform_tables[i].name == identifier && waveform_tables[i].frequency == frequency)
        {
           cout << "Returning from cache" << endl;
           return &waveform_tables[i];
        } // if
    } // for

    // Waveform table does not exist in cache; recompute it
    waveform_table_t result = GenerateWaveformFrequencyTable (*GetWaveform (identifier), frequency);
    
    // Errorneous waveform specified
    //if (result == NONE)
    //	return NONE;
    
    waveform_tables.push_back(result);
    return &waveform_tables.back();
    
} // GetWaveformTable


unsigned int waveform_t::Samples () const
{
    return num_samples;
} // waveform_t::Samples


void waveform_t::SetSamples (const unsigned int val)
{   
    num_samples = val;
} // waveform_t::SetSamples

// Assigns a specific interpolation method to a specific region of a waveform.
void  waveform_t::SetInterpolationMethod (const location_t loc, const string& method)
{

	interpolation_data_t idt;
	idt.method = method;
	idt.w_location = loc;

		
	interpolation_data.push_back (idt);
} // waveform_t::SetInterpolationMethod  

// Get interpolation method applicable to specified location
string waveform_t::InterpolationMethod (location_t loc) const
{
	
	// Go through all defined interpolation method declarations in waveform
	for (int i = 0; i < interpolation_data.size(); i++ )
	{
		int prev_i = i - 1;
		if (!i) prev_i = 0;		// To eliminate buffer underrun errors.
		
		location_t prev_loc = interpolation_data[prev_i].w_location;
		location_t this_loc = interpolation_data[i].w_location;
		
		if (loc == this_loc)
		{
           	return interpolation_data[i].method;
        } // if
    
        // interpolation method defined at this_loc is applicable to current location (loc)
		else if (loc > this_loc && 
            ((i == interpolation_data.size() - 1) || (interpolation_data[i+1].w_location > loc))) 
		{
			return interpolation_data[i].method;
        } // else if
        
	} // for

	// Default interpolation when no data is supplied
	if (!interpolation_data.size() || (loc == 0 && interpolation_data.front().w_location != loc))
		return "line";



	
	return "invalid";
	
} // waveform_t::InterpolationMethod



