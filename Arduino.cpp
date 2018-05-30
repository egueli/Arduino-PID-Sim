#include <Arduino.h>
#include <random>
#include <chrono>

double random(const double lower_bound, const double upper_bound) {
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
   	return unif(re);
}

_Serial Serial;
bool end_please;



using namespace std::chrono;


unsigned long millis_absolute() {
	milliseconds ms = duration_cast< milliseconds >(
	    system_clock::now().time_since_epoch()
	);
	return ms.count();
}

unsigned long millis_start = millis_absolute();

unsigned long millis() {
	return millis_absolute() - millis_start;
}


int main(int argc, char* argv[]) {
	setup();
	while(!end_please) {
		loop();
	}
	return 0;
}

void end() {
	end_please = true;
}
