#ifndef ARISTA_CPP
#define ARISTA_CPP

struct Basurero;

struct Ruta {
    Basurero* basurero_destino;
    int distancia;
    int tiempo_viaje;
    int intersecciones;
    int costo_combustible;
    bool sentido_unido;
    Ruta* ruta_sig;

    Ruta(Basurero* destino, int distanciaRuta, int tiempoViaje,
         int cruces, int costoCombustible, bool sentidoUnico) {
        basurero_destino = destino;
        distancia = distanciaRuta;
        tiempo_viaje = tiempoViaje;
        intersecciones = cruces;
        costo_combustible = costoCombustible;
        sentido_unido = sentidoUnico;
        ruta_sig = 0;
    }
};

#endif
