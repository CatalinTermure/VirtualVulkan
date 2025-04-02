#ifndef VVK_COMMONS_BIDI_STREAM_H
#define VVK_COMMONS_BIDI_STREAM_H

#include <mutex>

#include "vvk_server.grpc.pb.h"

namespace vvk {

class ClientBidiStream {
 public:
  ClientBidiStream(
      std::unique_ptr<grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>> reader_writer)
      : reader_writer_(std::move(reader_writer)), mutex_() {}

  bool Write(const vvk::server::VvkRequest& request);

  bool Read(vvk::server::VvkResponse* response);

  ~ClientBidiStream();

 private:
  std::unique_ptr<grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>> reader_writer_;
  std::mutex mutex_;
};

}  // namespace vvk

#endif  // VVK_COMMONS_BIDI_STREAM_H
