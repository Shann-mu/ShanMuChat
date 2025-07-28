#pragma once
#include "const.h"

class RedisConPool {
public:
	RedisConPool(size_t poolSize, const char* host, int port, const char* pwd);
	~RedisConPool();
	redisContext* getConnection();
	void returnConnection(redisContext* context);
	void Close();

private:
	std::atomic<bool> b_stop;
	size_t poolSize_;
	const char* host_;
	int port_;
	std::queue<redisContext*> connections_;
	std::mutex mutex_;
	std::condition_variable cond_;

};




class RedisMgr:public Singleton<RedisMgr>
{
	friend class Singleton<RedisMgr>;
public:
	~RedisMgr();
	//��ȡkey��Ӧ��value
	bool Get(const std::string& key, std::string& value);
	//����key��value
	bool Set(const std::string& key, const std::string& value);
	//������֤
	bool Auth(const std::string& password);
	//���push
	bool LPush(const std::string& key, const std::string& value);
	//���pop
	bool LPop(const std::string& key, std::string& value);
	//�Ҳ�push
	bool RPush(const std::string& key, std::string& value);
	//�Ҳ�pop
	bool RPop(const std::string& key, std::string& value);
	//hset����
	bool HSet(const std::string& key, const std::string& hkey,const std::string &value);
	bool HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen);
	//hget����
	std::string HGet(const std::string& key, const std::string& hkey);
	//del����
	bool Del(const std::string& key);
	//�жϼ�ֵ�Ƿ����
	bool ExistsKey(const std::string& key);
	void Close();
private:
	RedisMgr();

	std::unique_ptr<RedisConPool> _con_pool;
};

