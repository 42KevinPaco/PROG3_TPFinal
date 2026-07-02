#include <iostream>
#include <climits>
#include "dijkstra.cpp"

using namespace std;

Basurero* agregarBasurero(Basurero*& inicio, Basurero*& fin, int id,
                          const char calle[30], int tiempoServicio,
                          double longitud, double latitud) {
    Basurero* nuevoBasurero = new Basurero(id, calle, tiempoServicio,
                                           longitud, latitud);

    if (inicio == 0) {
        inicio = nuevoBasurero;
        fin = nuevoBasurero;
    } else {
        fin->basurero_sig = nuevoBasurero;
        fin = nuevoBasurero;
    }

    return nuevoBasurero;
}

void liberarGrafo(Basurero* grafo) {
    Basurero* basureroActual = grafo;

    while (basureroActual != 0) {
        Ruta* rutaActual = basureroActual->rutas;
        while (rutaActual != 0) {
            Ruta* rutaEliminar = rutaActual;
            rutaActual = rutaActual->ruta_sig;
            delete rutaEliminar;
        }

        Basurero* basureroEliminar = basureroActual;
        basureroActual = basureroActual->basurero_sig;
        delete basureroEliminar;
    }
}

void imprimirCamino(Basurero* basurero) {
    if (basurero == 0) {
        return;
    }

    if (basurero->previo != 0) {
        imprimirCamino(basurero->previo);
        cout << " -> ";
    }

    cout << basurero->calle;
}

int main() {
    const int cantidadBasureros = 9;

    int matrizAdyacencia[cantidadBasureros][cantidadBasureros] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    char calles[cantidadBasureros][30] = {
        "Base central",
        "San Martin",
        "Belgrano",
        "Rivadavia",
        "Mitre",
        "Sarmiento",
        "Moreno",
        "Italia",
        "Lavalle"
    };

    int tiemposServicio[cantidadBasureros] = {0, 5, 4, 6, 7, 5, 3, 4, 6};
    double longitudes[cantidadBasureros] = {
        -58.3816, -58.3822, -58.3830, -58.3841, -58.3854,
        -58.3860, -58.3873, -58.3881, -58.3890
    };
    double latitudes[cantidadBasureros] = {
        -34.6037, -34.6040, -34.6046, -34.6051, -34.6058,
        -34.6064, -34.6069, -34.6075, -34.6080
    };

    Basurero* grafo = 0;
    Basurero* ultimo = 0;
    Basurero* basureros[cantidadBasureros];

    for (int i = 0; i < cantidadBasureros; i++) {
        basureros[i] = agregarBasurero(grafo, ultimo, i, calles[i],
                                       tiemposServicio[i],
                                       longitudes[i], latitudes[i]);
    }

    for (int i = 0; i < cantidadBasureros; i++) {
        for (int j = 0; j < cantidadBasureros; j++) {
            int costo = matrizAdyacencia[i][j];
            if (costo > 0) {
                int distancia = costo * 100;
                int tiempoViaje = costo * 2;
                int intersecciones = costo / 2;
                bool sentidoUnico = matrizAdyacencia[j][i] == 0;

                basureros[i]->agregarRuta(basureros[j], distancia,
                                          tiempoViaje, intersecciones,
                                          costo, sentidoUnico);
            }
        }
    }

    dijkstra::calcular(grafo, basureros[0]);

    cout << "Optimizacion de rutas de recoleccion de residuos" << endl;
    cout << "Origen: " << basureros[0]->calle << endl << endl;

    Basurero* actual = grafo;
    while (actual != 0) {
        cout << "Basurero: " << actual->id
             << " | Calle: " << actual->calle
             << " | Costo combustible: ";

        if (actual->distancia == INT_MAX) {
            cout << "sin conexion";
        } else {
            cout << actual->distancia;
        }

        cout << " | Camino: ";
        imprimirCamino(actual);
        cout << endl;

        actual = actual->basurero_sig;
    }

    liberarGrafo(grafo);
    return 0;
}
