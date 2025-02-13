from .layer_generator import generate_layer
from .client_generator import generate_client
from .proto_generator import generate_proto
from .server_generator import generate_server


def generate() -> None:
    generate_proto()
    generate_server()
    generate_client()
    generate_layer()
