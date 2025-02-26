# VirtualVulkan

A set of utilities for running Vulkan API commands remotely over the network, while presenting the results locally on the client.

This allows easily using a remote GPU for executing GPU-accelerated Vulkan programs, without sharing the program's code with the server providing GPU compute resources.

## Components

This repository contains 4 components:
* A [protobuf](https://protobuf.dev/) library containing definitions required for calling Vulkan API functions over the network using [gRPC](https://grpc.io/).
* A library for serializing the parameters of Vulkan API calls to gRPC.
* A server binary that calls requested Vulkan API functions and returns the results of the functions.
* A [Vulkan Layer](https://docs.vulkan.org/guide/latest/layers.html) that intercepts certain Vulkan API calls and sends them to the Vulkan server, while still presenting the results using the client's GPU.

## Building

The project uses CMake as a build system.

The following CMake options affect the build:
* `VVK_LAYER` specifies whether to build the VirtualVulkan Layer.

## Installation

The install directory should be configured using `CMAKE_INSTALL_PREFIX`.

For documentation on the proper install directory, consult the official [Khronos documentation](https://github.com/KhronosGroup/Vulkan-Loader/blob/main/docs/LoaderLayerInterface.md#layer-discovery) on where implicit layers should be installed.