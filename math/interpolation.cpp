#include "../wavegen.h"
#define LinearInterpolation(x1,x2,x3,y1,y3) y1 + (x2 - x1) * (double) (y3 - y1) / (double) (x3 - x1)


vector <amplitude_t> GetInterpolationVector (const waveform_t& waveform, location_t from, const amplitude_t amp_from,
										     location_t to,  const amplitude_t amp_to, const unsigned int req_samples)
{
	
	vector <amplitude_t> output;
	
	// We first scale the number of samples to match the required 
	// number of samples
		
	double scale = (double) req_samples / waveform.Samples ();
	
	from *= scale;
	from = round (from);
	
    to *= scale;
	to = round (to);
    
    // Go through all location and interpolate.	
    
	for (location_t l = from ; l < to; l++)
	{
		location_t x1 = from;
		location_t x2 = l;
		location_t x3 = to;
	
		amplitude_t y1 = amp_from;
		amplitude_t y3 = amp_to;
		
		// Action depending on interpolation method 
		const string interpolation_method = waveform.InterpolationMethod (l);
		
		if (interpolation_method == "line")
		{
    		amplitude_t y2 = LinearInterpolation (x1,x2,x3,y1,y3);
    		
			output.push_back (y2);    		
		} // if -- linear

        // if trig. interpolation does not work piece-wise,
        // then something like: 
        //     amplitude_t y2 = TrignometricInterpolationVector (x2, waveform); 
        //     l = next non-trig known location (or end)
        // might do the job

    	
      /*  else if (interpolation_method == "trig")         		
		{
    		amplitude_t y2 = TrignometricInterpolation (x2,waveform);
			output.push_back (y2);    		
		} // else if -- trig */

        else if (interpolation_method == "cos")         		
		{
    		amplitude_t y2 = CosineInterpolation (x1,x2,x3,y1,y3);
			output.push_back (y2);    		
		} // else if -- cos

       else if (interpolation_method == "sinc")         		
		{
    		amplitude_t y2 = CosineInterpolation (x1,x2,x3,y1,y3); 
    		double frac =  y2/(double) (x2+1);
            cout << endl;   		
			output.push_back (frac);    		
		} // else if -- sinc

		
        else if (interpolation_method == "invalid")
            error ("waveform `" + waveform.Name() + "': unsupported interpolation method.");
            
        else
            error ("`" + interpolation_method + "' is an unsupported interpolation method.");
        

	} // while 	 
	
	return output;
} // GetInterpolationVector 
						
// Perform a sinusoidal interpolation between two points

/*
    This works by multiplying & shifting x1 and x3.
    
    See: "Interpolation Methods" by Paul Burke
         http://paulbourke.net/miscellaneous/interpolation/
         Accessed 4/23 2016
    
    Let:
        Xmax,Xmin   := x1,x3 for y1 > y3
                       x3,x1 for y1 < y3    
        Ymax := max (y1,y3)
        Ymin := min (y1,y3)
    
    Step 1. 
        We scale the range x3-x1 by a factor Ksc, and shift it by 
        a shifting factor Ksh, such that        
           cos (Ksc * Xmax  + Ksh) = Ymax/Amax, and,
           cos (Ksc * Xmin  + Ksh) = Ymin/Amax

        Solving, we get
            ksc = (acos (Ymax/Amax) - acos (Ymin/Amax)) / (Xmax- Xmin)
            ksh = acos(Ymin

    Step 2.
        For any input x2, function is given by
            MAX_AMPLITUDE * cos (ksc * x2 + ksh)
            // Problem: if ksc = 0, output does not depend on x2
    
           
    So for y1=50 and y3=-20
    cos max(y1,y3) = 1 and cos min(y1,y3) = -0.4
    and then performing horizontal 
    */				  	
amplitude_t CosineInterpolation (location_t x1, location_t x2, location_t x3, amplitude_t y1, amplitude_t y3)
{
    // To avoid division by zero
    x1 += 1;
    x2 += 1;
    x3 += 1;
    
    
    location_t    xmax, xmin;
    
    double   ymax, ymin;
    const amplitude_t amax = MAX_AMPLITUDE;
    
    if (y1 > y3)
    {
    	xmax = x1;
    	xmin = x3;
	} // if
    else if (y1 < y3)
    {
    	xmax = x3;
    	xmin = x1;    	
	} // else if
	else  // y1 == y3
        return y1;
                    	
	ymax = max (y1, y3) / (double) amax;
	ymin = min (y1, y3) / (double) amax;
	
	
	double ksc, ksh, ktst;  // Scaling and shifting factors
	ksc  = ((acos(ymax)/(double) xmax) - (acos(ymin)/(double) xmax)) /(double) (1 - xmin/(double) xmax);
	ksh  = (acos(ymin) - ksc* (double)  xmin);
			
    amplitude_t y2 = (double) ((double) amax * (double) cos (ksc * x2 + ksh));
	/*
    		cout << "x1 = " << x1 << endl;
    		cout << "y1 = " << y1 << endl << endl;
    		
    		cout << "x3 = " << x3 << endl;
    		cout << "y3 = " << y3 << endl << endl;

    		cout << "x2 = " << x2 << endl;
    		cout << "y2 = " << y2 << endl << endl;
    		
    		 system ("pause"); 
    */
    return y2;   
    
} // CosineInterpolation
