#include <cstdio>

unsigned long millis();

void setup();
void loop();

class _Serial {
public:
	void begin(int) {}

	inline void println() { printf("\n"); fflush(stdout); }
	inline void println(const char* str) { printf("%s\n", str); fflush(stdout); }
	inline void println(const double n) { printf("%.2f\n", n); fflush(stdout); }
	inline void print(const unsigned long n) { printf("%lu", n); }	
	inline void print(const double n) { printf("%.2f", n); }
	inline void print(const char* str) { printf("%s", str); }
	inline void print(const int n) { printf("%d", n); }	
};

extern _Serial Serial;

double random(const double lower_bound, const double upper_bound);

void end();