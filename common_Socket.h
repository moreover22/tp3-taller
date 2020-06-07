#ifndef COMMON_H
#define COMMON_H

#include "common_IInterchangeable.h"
#include "common_SocketConf.h"
#include <cstddef>
#include <sys/socket.h>
#include <sys/types.h>

#define INVALID_FD -1

typedef ssize_t (*interchanger_t)(int sockfd, char *buf, size_t len);
typedef struct addrinfo addrinfo_t;

class Socket: public IInterchangeable {
protected:
    SocketConf* configuration;
    int file_descriptor;

private:
    interchanger_t interchanger;
    /**
     * @brief Se intercambiarán datos. La función de intercambio se configura antes
     * de llamar a la función.
     * @param buf buffer a emplear.
     * @param longitud tamaño del buffer.
     * @throw ConnectionError en caso de error.
     * @return Cantidad de bytes intercambiados.
     */

    int interchange_data(char *buf, size_t length);
    /**
     * @brief Dado un host y un servicio, se resuelve la información de direcciones
     * IPv 4 asociada a ese host. 
     * @param host nombre de dominio o ip en forma de cadena.
     * @param service nombre de servicio o puerto.
     * @param result la información sera entrega mediante una lista enlazada
     *              alojada en esta variable.
     * @throw ConnectionError en caso de error.
    */
    void resolve_addrinfo(const char *host, const char *service, 
                                                        addrinfo_t **result);

    /**
     * @brief Dada información de un host particular se intentará establecer una conexión.
     * @param host_info información del host al que se quiere conectar.
     * @throw ConnectionError en caso de error.
     * @post En caso de éxito se asocia el file_descriptor del socket.
     */
    int engage_host(addrinfo_t *host_info);
    /**
     * @brief Se intentará asociar el servicio y host con el socket.
     * @param host nombre de dominio o ip en forma de cadena.
     * @param service nombre de servicio o puerto.
     * @throw ConnectionError en caso de error.
     */
    void engage_service(const char *host, const char *service);
    bool multiple_engage(addrinfo_t *hosts);

public:
    /**
     * @brief Constructor socket
     */
    explicit Socket(SocketConf& conf): configuration(&conf), 
                                                file_descriptor(INVALID_FD) {}

    explicit Socket(int file_descriptor): file_descriptor(file_descriptor) {}
    Socket(): file_descriptor(INVALID_FD) {}
    
    /**
     * @brief Destructor socket
     */
    ~Socket();

    /**
     * @brief Se establece una conexión con un host mediandte un servicio.
     * @param host nombre de dominio o ip en forma de cadena.
     * @param service nombre de servicio o puerto.
     * @throw ConnectionError en caso de error.
     * Lado del cliente
     */
    void connect(const char *host, const char *service);

    /**
     * @brief Se envia un mensaje a host previamente conectado.
     * @param mensaje mensaje a ser enviado.
     * @param longitud longitud del mensaje.
     * @throw ConnectionError en caso de error.
     * @return Cantidad de bytes enviados.
     */
    int send(const char* mensaje, size_t longitud);

    /**
     * @brief Se enlaza el servicio 'service' y se activa la cola de clientes.
     * @param longitud longitud del mensaje.
     * @param service nombre de servicio o puerto.
     * @throw ConnectionError en caso de error.
     * Lado del server
     */
    void bind_and_listen(const char *service);

    /**
     * @brief Se queda a la espera de la conexión del cliente.
     * @throw ConnectionError en caso de error.
     * Lado del server
     */
    Socket accept();


    /**
     * @brief Se recibe un mensaje del peer previamente conectado.
     * @param buffer buffer donde se guardará el mensaje.
     * @param longitud tamaño del buffer.
     * @throw ConnectionError en caso de error.
     * @return Cantidad de bytes recibidos.
     */
    int receive(char *buffer, size_t longitud);

    /**
     * @brief Permite cerrar los canales del socket.
     * @param how: canal a cerrar (SHUT_RD, SHUT_WR, SHUT_RDWR)
     */
    void shutdown(int how);

    Socket(Socket&& other);
    Socket& operator=(Socket&& other);
};

#define SERVER 0
#define CLIENT 1

#endif
