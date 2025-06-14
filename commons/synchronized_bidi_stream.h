#ifndef VVK_COMMONS_SYNCHRONIZED_BIDI_STREAM_H
#define VVK_COMMONS_SYNCHRONIZED_BIDI_STREAM_H

#include <mutex>

#include "vvk_server.grpc.pb.h"

namespace vvk {

template <typename RequestType, typename ResponseType>
class SynchronizedClientBidiStream {
 public:
  SynchronizedClientBidiStream(std::unique_ptr<grpc::ClientReaderWriter<RequestType, ResponseType>> reader_writer)
      : reader_writer_(std::move(reader_writer)) {}

  bool Write(const RequestType& request) {
    std::lock_guard lock(mutex_);
    return reader_writer_->Write(request);
  }

  bool Read(ResponseType* response) {
    std::lock_guard lock(mutex_);
    return reader_writer_->Read(response);
  }

  ~SynchronizedClientBidiStream() {
    std::lock_guard lock(mutex_);
    reader_writer_->WritesDone();
    reader_writer_->Finish();
  }

 private:
  std::unique_ptr<grpc::ClientReaderWriter<RequestType, ResponseType>> reader_writer_;
  std::mutex mutex_;
};

using VvkCommandClientBidiStream = SynchronizedClientBidiStream<vvk::server::VvkRequest, vvk::server::VvkResponse>;

}  // namespace vvk

#endif  // VVK_COMMONS_SYNCHRONIZED_BIDI_STREAM_H
