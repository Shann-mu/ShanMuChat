#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;




class VarifyGrpcClient:public Singleton<VarifyGrpcClient>
{
	friend class Singleton<VarifyGrpcClient>;
public:
	GetVarifyRsp GetVarifyCode(std::string email) {
		ClientContext context;
		GetVarifyRsp reply;
		GetVarifyReq request;
		request.set_email(email);

		Status status = _stub->GetVarifyCode(&context, request, &reply);
		if (status.ok()) {
			return reply;
		}
		else {
			reply.set_error(ErrorCode::RPCFailed);
			return reply;
		}
	}
private:
	VarifyGrpcClient() {
		std::shared_ptr<Channel> channel = grpc::CreateChannel("127.0.0.1:50051",
			grpc::InsecureChannelCredentials());
		_stub = VarifyService::NewStub(channel);
	}
	std::unique_ptr<VarifyService::Stub> _stub;

};

