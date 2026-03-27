#define E 2.71828

// dacay func macros
#define EXP_DECAY(x, c, a) (a*E**(-x*c))
#define LINEAR_DECAY(x, c, a) (a*(1-(x*c)))
#define QUADRATIC_DECAY(x, c, a) (a*(1-((c*x)**2)))

// easier to work with
enum decay_functions{
	NOFUNC,
	LINEAR,
	QUADRATIC,
	EXPONENTIAL
};


// STRUCTS


// structure of sample which we expect to decay and end with an inherent length
// think drums, plucks etc
//
// for now it will all be explicitly defined on the user side4
// but common effects as well and presets can be used in the future.
struct transient_sample{

	unsigned int base_freq;
	unsigned int amp;
	int amp_decay_func = NOFUNC;
	int amp_decay_coef = 0;
	int freq_decay_func = NOFUNC;
	int freq_decay_coef = 0;

};



// USER CALLED FUNCTIONS

struct transient_sample * init_transient_sample(unsigned int base_freq, unsigned int amp, int amp_decay_func,int amp_decay_coef, int freq_decay_func, int freq_decay_coef);
