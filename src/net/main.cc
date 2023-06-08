#include "net.h"

int main() {
    Net::Socket socket = Net::Socket(Net::AddressFamily::Ipv4, Net::Protocol::TCP, 9000);
    socket.open();

    return 0;
}
