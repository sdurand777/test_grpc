# generation cpp
protoc --grpc_out=. --cpp_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` myproto.proto

# generation python
python -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. myproto.proto
