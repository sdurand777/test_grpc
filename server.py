
from concurrent import futures
import grpc

import sys 
import os

# Ajouter le dossier proto_files au chemin de recherche
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), 'proto_files')))

# Importer les modules générés
import myproto_pb2
import myproto_pb2_grpc

# from proto_files import myproto_pb2
# from proto_files import myproto_pb2_grpc     


class MyServiceServicer(myproto_pb2_grpc.MyServiceServicer):
    def SayHello(self, request, context):
        reply = myproto_pb2.HelloReply()
        reply.message = f"Hello, {request.name} from Python server!"
        return reply

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    myproto_pb2_grpc.add_MyServiceServicer_to_server(MyServiceServicer(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("Python gRPC server started on port 50051")
    server.wait_for_termination()

if __name__ == '__main__':
    serve()
