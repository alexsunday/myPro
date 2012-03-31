#include <iostream>
#include <boost/asio.hpp>

int asio_client_main(int argc , char** argv)
{
	using namespace boost::asio;
	io_service ioserv;

	ip::tcp::socket socket(ioserv);
	ip::tcp::endpoint ep(ip::address_v4::from_string("127.0.0.1"), 50021);

	boost::system::error_code ec;
	socket.connect(ep , ec);

	if (ec)
	{
		std::cout << "Error of connect!" << std::endl;
		return 1;
	}

	char buf[100] = { 0 };
	size_t len = socket.read_some(buffer(buf) , ec);
	std::cout << buf << std::endl;

	return 0;
}