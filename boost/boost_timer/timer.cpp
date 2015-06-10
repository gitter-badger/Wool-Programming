#include <iostream>
#include <boost\date_time\posix_time\posix_time.hpp>
#include <boost\thread\thread.hpp>


class Timer{
public:
	Timer(){}
	
	void start(){
		now = boost::posix_time::microsec_clock::local_time();
	}

	void stop(){
		timer = boost::posix_time::microsec_clock::local_time() - now;
		std::cout << timer.total_milliseconds() << std::endl;
	}

private:
	boost::posix_time::ptime now;
	boost::posix_time::time_duration timer;
};

#if 1

int main(){
	Timer timer;
	timer.start();
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	timer.stop();
}

#endif