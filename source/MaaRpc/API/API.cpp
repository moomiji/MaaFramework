#include "../implement/Context.h"
#include "MaaRpc/MaaRpc.h"
#include <grpcpp/server_builder.h>

static std::unique_ptr<grpc::Server> server;

void MaaRpcStart(MaaStringView address)
{
    if (server) {
        server->Shutdown();
    }

    std::string server_address(address);

    Context context;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    context.regService(builder);

    server = builder.BuildAndStart();
}

void MaaRpcStop()
{
    if (server) {
        server->Shutdown();
    }
}

void MaaRpcWait()
{
    if (server) {
        server->Wait();
    }
}
