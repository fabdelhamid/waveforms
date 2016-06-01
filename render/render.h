//  some functions to aid with constructing waveforms
#define RENDER_H
 class waveform_t;
 class sprite_t;
 
// table for rendering waveforms
typedef struct {
    unsigned int num_samples; // optional?
    timepoint_t time;         // for sprite-generated waveform table
    string name;
    frequency_t  frequency;
    vector <amplitude_t> data;
} waveform_table_t;


waveform_table_t GenerateWaveformTable (const waveform_t& input, const unsigned int samples);
waveform_table_t GenerateWaveformTable (const   sprite_t& input, const timepoint_t time);
//waveform_table_t GenerateMorphWaveformTable (const waveform_t& wv1, const waveform_t& wv2, double ratio);

// Generate a linear interpolation of two waveforms, using the linear method
waveform_table_t LinearWaveformInterpolation (const timepoint_t x1,
                                                const timepoint_t x2,
                                                  const timepoint_t x3,
                                                     waveform_t* last_rel_wf,  waveform_t*  next_wf, const frequency_t freq);

// table for rendering sprites
typedef struct {
    unsigned int waveform_render_multiplier ;    // how many times to repeat each waveform
    vector <waveform_table_t> data; 
} sprite_table_t;

// Generate a table of all waveforms constituting a sprite
sprite_table_t   GenerateSpriteTable   ( sprite_t&   input,  const unsigned int waveform_render_multiplier ) ;


