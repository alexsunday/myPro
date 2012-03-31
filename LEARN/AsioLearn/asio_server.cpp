#include <iostream>
#include <boost/asio.hpp>

int asio_server_main(int argc, char* argv[])
{
	using namespace boost::asio;
	// ����asio�඼��Ҫio_service����
	io_service iosev;
	ip::tcp::acceptor acceptor(iosev,
		ip::tcp::endpoint(ip::tcp::v4(), 1000));
	for(;;)
	{
		// socket����
		ip::tcp::socket socket(iosev);
		// �ȴ�ֱ���ͻ������ӽ���
		acceptor.accept(socket);
		// ��ʾ���ӽ����Ŀͻ���
		std::cout << socket.remote_endpoint().address() << std::endl;
		// ��ͻ��˷���hello world!
		boost::system::error_code ec;
		socket.write_some(buffer("hello world!"), ec);

		// ���������ӡ������Ϣ
		if(ec)
		{
			std::cout <<
				boost::system::system_error(ec).what() << std::endl;
			break;
		}
		acceptor.close();
		// �뵱ǰ�ͻ�������ɺ�ѭ�������ȴ���һ�ͻ�����
	}
	return 0;
} 

/*
 *socketͨ��
 *1����ʱ���첽������
 *2��
 */