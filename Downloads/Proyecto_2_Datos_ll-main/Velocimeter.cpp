#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Velocimeter.h"
#include "Levels.h"

void Velocimeter::SocketServer() {

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Crear socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Error al crear socket" << std::endl;
        return;
    }

    // Opción de socket para reutilizar la dirección
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        std::cerr << "Error en setsockopt" << std::endl;
        return;
    }

    // Configurar dirección del socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5001);

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "Error en setsockopt" << std::endl;
        return;
    }


    // Enlazar socket a la dirección y puerto especificados
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        std::cerr << "Error en bind" << std::endl;
        return;
    }

    // Escuchar conexiones entrantes
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Error en listen" << std::endl;
        return;
    }

    std::cout << "Servidor en espera de conexiones..." << std::endl;


    // Aceptar nueva conexión
    if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
        std::cerr << "Error en accept" << std::endl;
        return;
    }

    std::cout << "Nueva conexión aceptada" << std::endl;
    char primerDato[1024] = {0};
    char segundoDato[1024] = {0};
    // Procesar mensajes entrantes
    char buffer[1024] = {0};
    int valread = read(new_socket, buffer, 1024);
    if (valread <= 0) {
        std::cout << "Cliente desconectado" << std::endl;
        close(new_socket);
        return;
    }

    const char* delimiter = "\n";

    //std::cout<< "ESTA ES LA DATA 1"<<data1;
   // std::cout<<"ESTA ES LA DATA 2"<<data2;
    // Usar strtok para separar los datos
    char* token = std::strtok(buffer, delimiter);
    if (token != nullptr) {
        std::strcpy(primerDato, token);
        token = std::strtok(nullptr, delimiter);
        if (token != nullptr) {
            std::strcpy(segundoDato, token);
        }
    }


    std::cout<<"este es el primero: "<<primerDato << std::endl;

    std::cout<<"este es el segundo: "<<segundoDato << std::endl;

  //  std::cout <<buffer<< std::endl;



    char respuestaa[] = "40,50,60";
    //std::cout<<"este es el life "<<lifes<< "este es el point "<<points<<"este es el lvl "<<level;
    //respuestaa[0] = lifes;
    //respuestaa[1] = points;
    //respuestaa[2] = level;

    send(new_socket, respuestaa, sizeof(respuestaa), 0);
    std::cout << "Respuesta: " << respuestaa << std::endl;


    //memset(buffer, 0, sizeof(buffer));
    //recv(new_socket, buffer, sizeof(buffer), 0);
    //std::cout << "Dato recibido: " << buffer << std::endl;

    if (close(server_fd) == -1) {
        std::cerr << "Error al cerrar el socket: " << std::strerror(errno) << std::endl;
        return;
    }
    if (close(new_socket) == -1) {
        std::cerr << "Error al cerrar el socket: " << std::strerror(errno) << std::endl;
        return;
    }
}
void Velocimeter::setPoints(char points){
    this->points = points;
}
void Velocimeter::setLifes(char lifes){
    this->lifes = lifes;
}
void Velocimeter::setLevel(char level){
    this->level = level;
}