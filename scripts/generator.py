from .proto_generator import generate_proto
from .server_generator import generate_server


def generate() -> None:
    generate_proto()
    generate_server()
