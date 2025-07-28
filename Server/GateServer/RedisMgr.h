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
	//获取key对应的value
	bool Get(const std::string& key, std::string& value);
	//设置key和value
	bool Set(const std::string& key, const std::string& value);
	//密码认证
	bool Auth(const std::string& password);
	//左侧push
	bool LPush(const std::string& key, const std::string& value);
	//左侧pop
	bool LPop(const std::string& key, std::string& value);
	//右侧push
	bool RPush(const std::string& key, std::string& value);
	//右侧pop
	bool RPop(const std::string& key, std::string& value);
	//hset操作
	bool HSet(const std::string& key, const std::string& hkey,const std::string &value);
	bool HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen);
	//hget操作
	std::string HGet(const std::string& key, const std::string& hkey);
	//del操作
	bool Del(const std::string& key);
	//判断键值是否存在
	bool ExistsKey(const std::string& key);
	void Close();
private:
	RedisMgr();

	std::unique_ptr<RedisConPool> _con_pool;
};

