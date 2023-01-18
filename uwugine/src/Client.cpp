/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#include "Client.hpp"
#include <arpa/inet.h>
#include <ext/stdio_filebuf.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/socket.h>

bool uwugine::Client::is_connected(void) { return connected; }

bool uwugine::Client::is_host(void) { return host; }

bool uwugine::Client::connect_to(const std::string &adress)
{
    sockaddr_in addr = {0};
    __gnu_cxx::stdio_filebuf<char> filebuf;

    addr.sin_family = AF_INET;
    addr.sin_port = 4747;
    inet_aton(adress.c_str(), &addr.sin_addr);
    socket = ::socket(AF_INET, SOCK_STREAM, getprotobyname("udp")->p_proto);
    if (socket == -1 || connect(socket, (sockaddr *) &addr, sizeof(addr)) == -1)
        return false;
    return true;
}

bool uwugine::Client::listen(uwugine::package &p)
{
    __gnu_cxx::stdio_filebuf<char> buf(socket, std::ios::in);
    std::istream stream(&buf);
    fd_set fds;
    timeval t = {0, 10};

    FD_ZERO(&fds);
    FD_SET(socket, &fds);

    if (select(socket + 1, &fds, nullptr, nullptr, &t) == 0)
        return false;
    stream.getline((char *) &p, sizeof(package));
    return true;
}

void uwugine::Client::send(const package &p)
{
    __gnu_cxx::stdio_filebuf<char> buf(socket, std::ios::out);
    std::ostream stream(&buf);

    stream.write((char *) &p, sizeof(package));
}
