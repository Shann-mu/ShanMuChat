#include "const.h"
#include "LogicSystem.h"
class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
    friend class LogicSystem;
public:
    HttpConnection(tcp::socket socket);
    void Start();

private:
    void CheckDeadline();
    //�ظ�
    void WriteResponse();
    //��������
    void HandleReq();
    //������ֵ��
    void PreParseGetParam();
    tcp::socket  _socket;
    // _buffer ������������
    beast::flat_buffer  _buffer{ 8192 };

    // _request ������������
    http::request<http::dynamic_body> _request;

    // _response ������Ӧ�ͻ���
    http::response<http::dynamic_body> _response;

    // _deadline ��������ʱ���ж������Ƿ�ʱ
    net::steady_timer deadline_{
        _socket.get_executor(), std::chrono::seconds(60) };
    
    std::string _get_url;
    std::unordered_map<std::string, std::string> _get_params;
};