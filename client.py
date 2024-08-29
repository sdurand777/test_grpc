
import grpc

import sys 
import os

# Ajouter le dossier proto_files au chemin de recherche
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), 'proto_files')))

import myproto_pb2
import myproto_pb2_grpc

def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = myproto_pb2_grpc.MyServiceStub(channel)
    response = stub.SayHello(myproto_pb2.HelloRequest(name='Python Client'))
    print("Python client received: " + response.message)

if __name__ == '__main__':
    run()
