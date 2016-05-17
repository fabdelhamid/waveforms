#include "../wavegen.h"

// Generate  table for a given waveform with a prespecified number of samples (to produce a certain frequency)
waveform_table_t GenerateWaveformTable (const waveform_t& input, const unsigned int req_samples)
{
    waveform_table_t output;

    location_t this_location = 0;
    location_t next_location;

    bool initial_wavepoint_set = false, 
         final_wavepoint_set   = false;

    // For use with calls to InterploateWavepoints
    location_t   loc_from, loc_to;
    amplitude_t  amp_from, amp_to;

    location_t   loc_last, loc_next;
    amplitude_t  amp_last, amp_next;

    if (input.wavepoints.front().w_location != 0)
    {
        // Make sure amplitude of initial location is known whether 
        // from definition of initial amplitude or 
        // TODO: move inside inner for loop
        if (!initial_wavepoint_set
              && (input.wavepoints.front().type == WAVEPOINT_AT || input.wavepoints.front().type == WAVEPOINT_BEFORE))
        {
                          
           // Determine locations and amplitudes from interpolation
           loc_from = 0;
           loc_to   = input.wavepoints.front().type;
           amp_from = input.wavepoints.front().value;
           amp_to   = input.wavepoints.front().value;
           
           // Get initial value from           
         //  InterploateWavepoints (loc_from, loc_to, amp_from, amp_to);
           
           // Push resulting data to the waveform table
           
           initial_wavepoint_set = true;
           
        } // if
        else if (!initial_wavepoint_set)
            error ("cannot determine value of initial wavepoint.");
    } // if
    
    /*
          Waveform.
      	*/
    output.num_samples = req_samples; //input.SamplesPerSecond();
    
    // Go through all wavepoint data 
    for (list<wavepoint_t>::const_iterator w = input.wavepoints.begin();
            next(w) != input.wavepoints.end(); w++)
    {
    	
    	// Go through all locations in final data file
    	// We now know that first location is defined as WAVEPOINT_AT
  		
        // Wavepoint is defined at this location, 
        const wavepoint_t *next_wavepoint = &*next (w);
                
        // Special case, same point has a setb and a seta
        if ((*w).w_location == next_wavepoint->w_location)
        {
            // record average
          // 	output.data.push_back ( ((*w).value + next_wavepoint->value)/2  );   
           // continue;
        } // if  
         
        
		vector <amplitude_t> values = GetInterpolationVector (input, (*w).w_location, (*w).value,
                                                               next_wavepoint->w_location, next_wavepoint->value,
                                                                req_samples);
		   		
       	output.data.insert (output.data.end(), values.begin(), values.end());   
		
        ////////////////////////////////////////
    
    } // for - through waveform wavepoints
    
    // Set identifier in this waveform table -- used when looking up global table
    output.name = input.Name();
    
    return output;
    
} // GenerateWaveformTable (const waveform_t&)

// Interpolates all space between two wavepoints according to a prespecified 
vector <amplitude_t> InterploateWavepoints (const location_t from, const location_t loc_to, const amplitude_t amp_from, const amplitude_t amp_to)
{
       vector <amplitude_t> result;
       // do something...
       return result;       
} // InterploateWavepoints

// Generate a linear interpolation of two waveforms, using the linear method
waveform_table_t LinearWaveformInterpolation (const timepoint_t x1,
                                                const timepoint_t x2,
                                                  const timepoint_t x3,
                                                    waveform_t* wf1, waveform_t*  wf2, const frequency_t freq)
                                                    
{
    
    waveform_table_t wvt1 = GenerateWaveformFrequencyTable (*wf1, freq);
    waveform_table_t wvt2 = GenerateWaveformFrequencyTable (*wf2, freq);
    
    // TODO: support interpolating two waveforms of different sizes
    if (wvt1.data.size() != wvt2.data.size())
        error ("cannot interpolate two waveforms of different sizes");
    
    cout << "will process morph" << endl;
    system ("pause");
    exit (0);
} // LinearWaveformInterpolation
