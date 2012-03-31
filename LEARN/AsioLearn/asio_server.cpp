#include <iostream>
#include <boost/asio.hpp>

int asio_server_main(int argc, char* argv[])
{
	using namespace boost::asio;
	// 所有asio类都需要io_service对象
	io_service iosev;
	ip::tcp::acceptor acceptor(iosev,
		ip::tcp::endpoint(ip::tcp::v4(), 1000));
	for(;;)
	{
		// socket对象
		ip::tcp::socket socket(iosev);
		// 等待直到客户端连接进来
		acceptor.accept(socket);
		// 显示连接进来的客户端
		std::cout << socket.remote_endpoint().address() << std::endl;
		// 向客户端发送hello world!
		boost::system::error_code ec;
		socket.write_some(buffer("hello world!"), ec);

		// 如果出错，打印出错信息
		if(ec)
		{
			std::cout <<
				boost::system::system_error(ec).what() << std::endl;
			break;
		}
		acceptor.close();
		// 与当前客户交互完成后循环继续等待下一客户连接
	}
	return 0;
} 

/*
 *socket通信
 *1、超时、异步、阻塞
 *2、
 */