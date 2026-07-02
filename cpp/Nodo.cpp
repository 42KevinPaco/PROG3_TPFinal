#ifndef NODO_CPP
#define NODO_CPP

#include <climits>
#include <cstring>
#include "Arista.cpp"

struct Basurero {
    int id;
    char calle[30];
    int tiempo_servicio;
    double longitud;
    double latitud;
    Basurero* basurero_sig;
    Ruta* rutas;

    int distancia;
    bool visitado;
    Basurero* previo;

    Basurero(int idBasurero, const char nombreCalle[30],
             int tiempoServicio, double lon, double lat) {
        id = idBasurero;
        strncpy(calle, nombreCalle, 29);
        calle[29] = '\0';
        tiempo_servicio = tiempoServicio;
        longitud = lon;
        latitud = lat;
        basurero_sig = 0;
        rutas = 0;
        distancia = INT_MAX;
        visitado = false;
        previo = 0;
    }

    void agregarRuta(Basurero* destino, int distanciaRuta, int tiempoViaje,
                     int cruces, int costoCombustible, bool sentidoUnico) {
        Ruta* nuevaRuta = new Ruta(destino, distanciaRuta, tiempoViaje,
                                   cruces, costoCombustible, sentidoUnico);

        if (rutas == 0) {
            rutas = nuevaRuta;
            return;
        }

        Ruta* actual = rutas;
        while (actual->ruta_sig != 0) {
            actual = actual->ruta_sig;
        }
        actual->ruta_sig = nuevaRuta;
    }
};

#endif
