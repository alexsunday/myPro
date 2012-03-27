异步模式代码
/*
	if(ioctlsocket(fd,FIONBIO,&ul) == SOCKET_ERROR )
	{
		closesocket(fd);
		cerr << "ioctlsocket error:" << WSAGetLastError() << endl;
		return -1;
	}

	do 
	{
		connect(fd , (sockaddr*)&srAddr , sizeof(sockaddr_in)) ;
		FD_ZERO(&fs);
		FD_SET(fd , &fs);

		if(select(0,0,&fs,0,&to) == SOCKET_ERROR)
		{
			closesocket(fd);
			cerr << "select error:" << WSAGetLastError() << endl;
			return -1;
		}

		if (FD_ISSET(fd , &fs))
		{
			//可写数据了！
			//重新设置为阻塞模式
			ul = 0;
			if(ioctlsocket(fd,FIONBIO,&ul) == SOCKET_ERROR )
			{
				closesocket(fd);
				cerr << "ioctlsocket error:" << WSAGetLastError() << endl;
				return -1;
			}
			return fd;
		}
		else
		{
			//timeout!
			cerr << "Connection failed, and retry... ... " << endl;
			--i;
			if(i == 0)
			{
				cerr << "Connection to " << ip << " failed!" << endl ;
				closesocket(fd);
				return -1;
			}
		}
	} while (i);

	return -1;
*/