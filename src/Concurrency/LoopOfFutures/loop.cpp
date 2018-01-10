#include <iostream>
#include <future>
#include <vector>
#include <chrono>
#include <thread>


using namespace std::chrono;
using namespace std::chrono_literals;


void wait_and_release(seconds sec, bool & stop)
{
	std::this_thread::sleep_for(sec);
	stop = true;
}

int twice(int m)
{
	return 2 * m;
}

void run_for(seconds sec)
{
 	bool stop = false;
	int i = 0;
	std::vector<std::future<int>> futures;

	auto result = std::async(std::launch::async, wait_and_release, sec, std::ref(stop));
	
	for( i = 0; i < 10; ++i)
	{
		futures.push_back (std::async(twice, i));
	}
	
	while(!stop)
	{	
		for(auto &e : futures) 
		{
			std::cout<< e.get() << " ";
			e = std::async(twice, i);
			++i;
		}
		std::cout<< std::endl;
		std::this_thread::sleep_for(1s);
	}
	result.get();
}

int main()
{
	run_for(seconds(10));
	return 0;
}
