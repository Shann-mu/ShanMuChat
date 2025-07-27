#include "AsioIOServicePool.h"

AsioIOServicePool::AsioIOServicePool(std::size_t size) :
	_ioServices(size), _works(size), _nextIOService(0) {
	for (int i = 0; i < size; i++) {
		_works[i] = std::make_unique<Work>(boost::asio::make_work_guard(_ioServices[i]));
	}
	for (int i = 0; i < _ioServices.size(); i++) {
		_threads.emplace_back([this, i]() {
			_ioServices[i].run();
			});
	}
}

AsioIOServicePool::~AsioIOServicePool()
{
	std::cout << "AsioIOServicePool destruct" << std::endl;
	Stop();
}

boost::asio::io_context& AsioIOServicePool::GetIOService()
{
	auto& service = _ioServices[_nextIOService++];
	if (_nextIOService == _ioServices.size()) {
		_nextIOService = 0;
	}
	return service;
}

void AsioIOServicePool::Stop() {
	//��Ϊ����ִ��work.reset��������iocontext��run��״̬�˳�
	//��iocontext�Ѿ����˶���д�ļ����¼��󣬻���Ҫ�ֶ�stop�÷���
	for (auto& io : _ioServices) {
		io.stop();
	}

	for (auto& work : _works) {
		work->reset();
	}
	
	for (auto& t : _threads) {
		t.join();
	}
}
