#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;
using namespace boost::asio;


int asio_deadline_timer_main(int argc, char** argv)
{
	io_service ios;
	deadline_timer t(ios , boost::posix_time::minutes(2)    );

	cout << t.expires_at() << endl;
	t.wait();
	cout << "Hello, Asio" << endl;

	return 0;
}
void print(const boost::system::error_code &ex)
{
	cout << "time out!" << endl;
}

int asio_deadline_timer_async_main(int argc, char** argv)
{
	io_service ios;
	deadline_timer t(ios , boost::posix_time::seconds(10));
	cout << t.expires_at() << endl;

	t.async_wait(print);

	cout << "Hello, Asio!" << endl;

	return 0;
}