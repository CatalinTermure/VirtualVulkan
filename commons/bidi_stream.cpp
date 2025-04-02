#include "bidi_stream.h"

namespace vvk {
bool ClientBidiStream::Write(const vvk::server::VvkRequest& request) {
  std::lock_guard lock(mutex_);
  return reader_writer_->Write(request);
}

bool ClientBidiStream::Read(vvk::server::VvkResponse* response) {
  std::lock_guard lock(mutex_);
  return reader_writer_->Read(response);
}

ClientBidiStream::~ClientBidiStream() {
  std::lock_guard lock(mutex_);
  reader_writer_->WritesDone();
  reader_writer_->Finish();
}

}  // namespace vvk