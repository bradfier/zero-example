#include <zmq.hpp>
#include <msgpack.hpp>
#include <string>
#include <iostream>
#include <unistd.h>

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        std::cout << "Received message from client." << std::endl;

		// Get a reference to the encoded data
		msgpack::object_handle oh =
		  msgpack::unpack((const char*)request.data(), request.size());
		msgpack::object deserialized = oh.get();

		// For now, just print the whole data packet to stdout
		std::cout << deserialized << std::endl;

        //  Send reply back to the client
		msgpack::type::tuple<std::string> src("Replying!");
		std::stringstream buffer;
		msgpack::pack(buffer, src);

		std::string output = buffer.str();
		zmq::message_t reply(output.size());
        memcpy(reply.data(), output.data(), output.size());
        socket.send(reply);
    }
    return 0;
}
