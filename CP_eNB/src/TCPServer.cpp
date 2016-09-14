/* A simple server in the internet domain using TCP
   The port number is passed as an argument */

#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <Logger.hpp>
#include <lte.pb.h>
#include <future>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

void dostuff(int, int); /* function prototype */

int create_socket()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

void fill_server_addres(sockaddr_in& address, int port_number)
{
    bzero((char *) &address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_number);
}

int bind(int socket_fd, sockaddr_in& server_address)
{
    return bind(socket_fd, (struct sockaddr *) &server_address,
              sizeof(server_address));
}

void run(int port_number, int socket_capacity, int buffer_size)
{
    int socket_fd = create_socket();
    if (socket_fd < 0)
    {
        lte::err() << "Creating socket has has failed with errNo: " << socket_fd;
        return;
    }
     
    sockaddr_in server_address;
    fill_server_addres(server_address, port_number);
     
    int result_of_bindings = bind(socket_fd, server_address);
    if (result_of_bindings < 0)
    {
        lte::err() << "ERROR on binding with errNo: " << result_of_bindings;
        close(socket_fd);
        return;
    }
     
    listen(socket_fd, socket_capacity);
     
    sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    while (true)
    {
        int newsockfd = accept(socket_fd,
                (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
        {
            lte::err() << "ERROR on accept with errNo: " << newsockfd;
        }
        
        std::thread([newsockfd, buffer_size]() {
           dostuff(newsockfd, buffer_size);     
        }).detach();
    }
    
    close(socket_fd);
}

void dostuff (int sock, int buffer_size)
{
    lte::ASN1 msg;
    int received;
    char buffer[buffer_size];
      
    bzero(buffer,buffer_size);
    received = read(sock,buffer,255);
    if (received < 0) lte::err() << "ERROR reading from socket";
    
    google::protobuf::io::ArrayInputStream arrayIn(buffer, received);
    google::protobuf::io::CodedInputStream codedIn(&arrayIn);
    google::protobuf::uint32 size;
    codedIn.ReadVarint32(&size);
    google::protobuf::io::CodedInputStream::Limit msgLimit = codedIn.PushLimit(size);
    msg.ParseFromCodedStream(&codedIn);
    codedIn.PopLimit(msgLimit);
    close(sock);
}

int main()
{
    int port_number = 5555;
    int socket_capacity = 5;
    int buffer_size = 255;
    run(port_number, socket_capacity, buffer_size);
    return 0;
}
