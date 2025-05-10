FROM ubuntu:25.04

ENV NVIDIA_DRIVER_CAPABILITIES=all

RUN apt-get update && \
  apt-get install -y \
  # generic dependencies
  git cmake g++ pkg-config \
  # dependencies for Vulkan-Loader
  build-essential libx11-xcb-dev libxkbcommon-dev libwayland-dev libxrandr-dev \
  # dependencies for VirtualVulkan
  protobuf-compiler-grpc libgrpc++-dev libspdlog-dev libvulkan-memory-allocator-dev \
  # misc
  vulkan-tools mesa-utils vulkan-validationlayers

COPY Vulkan-Headers /src/Vulkan-Headers
WORKDIR /src/Vulkan-Headers
RUN cmake -S . -B build/
RUN cmake --install build --prefix /usr
WORKDIR /

COPY Vulkan-Loader /src/Vulkan-Loader
WORKDIR /src/Vulkan-Loader
RUN cmake -S . -B build/ -DCMAKE_INSTALL_PREFIX=/usr
RUN cmake --build build/ --target install
WORKDIR /

COPY CMakeLists.txt /src/CMakeLists.txt
COPY tests /src/tests
COPY server /src/server
COPY proto /src/proto
COPY commons /src/commons
WORKDIR /src
RUN cmake -S . -B build/
RUN cmake --build build/

EXPOSE 50051
CMD [ "/src/build/server/VirtualVulkanServer" ]