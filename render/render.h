//  some functions to aid with constructing waveforms
#define RENDER_H
 
// table for rendering waveforms
typedef struct {
    unsigned int num_samples; // optional?
    string name;
    frequency_t  frequency;
    vector <amplitude_t> data;
} waveform_table_t;


waveform_table_t GenerateWaveformTable (const waveform_t& input, const unsigned int samples);
waveform_table_t GenerateWaveformTable (const   sprite_t& input, const timepoint_t time);
waveform_table_t GenerateMorphWaveformTable (const waveform_t& wv1, const waveform_t& wv2, double ratio);

// table for rendering sprites
typedef struct {
    timepoint_t wfps;    //waveforms per second
    vector <waveform_table_t> data; 
} sprite_table_t;

sprite_table_t   GenerateSpriteTable   (const sprite_t&   input);


