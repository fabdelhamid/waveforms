#include "wavegen.h"
// Global tables
vector <waveform_t> waveforms;
vector <sprite_t>   sprites;
vector <sound_t>    sounds;
vector <score_t>    scores;

int currently_in_sprite_block;
int currently_in_sound_block;
int currently_in_waveform_block;
int currently_in_score_block;

unsigned  short  wav_channels, wav_sps, wav_bpsample;  
namespace little_endian_io
{
  template <typename Word>
  std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
  {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
  } // template <typename Word>
} //  little_endian_io
using namespace little_endian_io;

int main()
{
    // Wave file properties
    wav_channels  = 2;
    wav_sps      = 44100;
    wav_bpsample = 16;  

    // Reset flags
    currently_in_sprite_block   = 0;
    currently_in_sound_block    = 0;
    currently_in_waveform_block = 0;
    currently_in_score_block    = 0;
	
    // Step 1: Read description 
    ReadFile ("C:/usbtmpstorage/cpp/wavegen/fadi-src/main.wfd");

	// Sprite Test 
    sprite_t* sts = GetSprite ("SquareToSawtooth");
    sts->SetFreq (440);
    sprite_table_t sprite_table = GenerateSpriteTable (*sts, 3);


/*
    for (unsigned int i = 0; i < sprite_table.data.size(); i++)
    {
        cout << "Testing frame " << i << "\t";
        square = sprite_table.data[i];        
        cout << "OK" << endl;

		for (int i = 0; i < square.data.size(); i++)
			cout << square.data[i] << " ";
			
		cout << endl << endl;
			        
    } // for    */
    
    
  // Final step: write WAV file 
  ofstream f ( "example.wav", ios::binary );

  // Write the file headers
  f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
  write_word( f,     16, 4 );  // no extension data
  write_word( f,      1, 2 );  // PCM - integer samples
  write_word( f, wav_channels, 2 );  // two channels (stereo file)
  write_word( f, wav_sps, 4 );  // samples per second (Hz)
  write_word( f, (wav_sps * wav_bpsample * wav_channels)/8, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
  write_word( f,      4, 2 );  // data block size (size of two integer samples, one for each channel, in bytes)
  write_word( f, wav_bpsample, 2 );  // number of bits per sample (use a multiple of 8)

  // Write the data chunk header
  size_t data_chunk_pos = f.tellp();
  f << "data----";  // (chunk size to be filled in later)
  
  // Write the audio samples
  // (We'll generate a single C4 note with a sine wave, fading from left to right)
  constexpr double two_pi = 6.283185307179586476925286766559;
  constexpr double max_amplitude = 32760;  // "volume"

  double hz          = 44100;   // samples per second
  double frequency_1 = 880;    //261.626;  // middle C
  double frequency_2 = 1000;
  double seconds     = 2.5;     // time

  for (int i = 0; i < sprite_table.data.size(); i++)
  {
	  int N =  sprite_table.data[i].data.size(); //  hz * seconds;  // total number of samples
	  for (int n = 0; n < N; n++)
	  {
	    double amplitude = /*  (double)n / N * */ (double) max_amplitude / SYNTAX_MAX_AMPLITUDE;
	
	    double value   = sprite_table.data[i].data[n]; //sin( (two_pi * n * frequency_1) / hz ) ;//+ sin( (two_pi * n * frequency_2) / hz );
	    //double value_1 = sin( (two_pi * n * frequency_1) / hz );
	    //double value_2 = sin( (two_pi * n * frequency_2) / hz );
	
	
	    write_word( f, (int)( amplitude  * value), 2 );
	    write_word( f, (int)((amplitude) * value), 2 );
	  }
 } // for
 
  // (We'll need the final file size to fix the chunk sizes above)
  size_t file_length = f.tellp();

  // Fix the data chunk header to contain the data size
  f.seekp( data_chunk_pos + 4 );
  write_word( f, file_length - data_chunk_pos + 8 );

  // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
  f.seekp( 0 + 4 );
  write_word( f, file_length - 8, 4 ); 
  
  f.close();
  
  //system ("c:\\Program\ Files\ (x86)\\Audacity\\audacity.exe example.wav");
  system ("pause");
} /* main */





