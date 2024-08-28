# Clone and compile gRPC and Protobuf from source
git clone --branch v1.60.0 https://github.com/grpc/grpc grpc && \
cd grpc && \
git submodule update --init && \
mkdir -p cmake/build && \
cd cmake/build && \
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=/usr/local \
      ../.. && \
make -j$(nproc) && \
sudo make install && \
cd ../../ && \
rm -rf grpc
