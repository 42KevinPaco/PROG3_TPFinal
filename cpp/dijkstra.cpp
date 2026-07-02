#ifndef DIJKSTRA_CPP
#define DIJKSTRA_CPP

#include "Nodo.cpp"

class dijkstra {
private:
    static int contarBasureros(Basurero* grafo) {
        int cantidad = 0;
        Basurero* actual = grafo;
        while (actual != 0) {
            cantidad++;
            actual = actual->basurero_sig;
        }
        return cantidad;
    }

    static Basurero* extraerMenor(Basurero** cola, int& cantidad) {
        if (cantidad == 0) {
            return 0;
        }

        int posMenor = 0;
        for (int i = 1; i < cantidad; i++) {
            if (cola[i]->distancia < cola[posMenor]->distancia) {
                posMenor = i;
            }
        }

        Basurero* menor = cola[posMenor];
        for (int i = posMenor; i < cantidad - 1; i++) {
            cola[i] = cola[i + 1];
        }
        cantidad--;
        return menor;
    }

    static void insertarCola(Basurero** cola, int& cantidad, Basurero* basurero) {
        cola[cantidad] = basurero;
        cantidad++;
    }

public:
    static void calcular(Basurero* grafo, Basurero* basureroInicial) {
        if (grafo == 0 || basureroInicial == 0) {
            return;
        }

        Basurero* actual = grafo;
        while (actual != 0) {
            actual->distancia = INT_MAX;
            actual->visitado = false;
            actual->previo = 0;
            actual = actual->basurero_sig;
        }

        int cantidadBasureros = contarBasureros(grafo);
        Basurero** colaPrioridad = new Basurero*[cantidadBasureros * cantidadBasureros];
        int cantidadCola = 0;

        basureroInicial->distancia = 0;
        insertarCola(colaPrioridad, cantidadCola, basureroInicial);

        while (cantidadCola > 0) {
            Basurero* basureroActual = extraerMenor(colaPrioridad, cantidadCola);

            if (basureroActual != 0 && !basureroActual->visitado) {
                basureroActual->visitado = true;

                Ruta* ruta = basureroActual->rutas;
                while (ruta != 0) {
                    Basurero* vecino = ruta->basurero_destino;

                    if (basureroActual->distancia != INT_MAX) {
                        int distanciaTemporal = basureroActual->distancia
                                                + ruta->costo_combustible;

                        if (distanciaTemporal < vecino->distancia) {
                            vecino->distancia = distanciaTemporal;
                            vecino->previo = basureroActual;
                            insertarCola(colaPrioridad, cantidadCola, vecino);
                        }
                    }

                    ruta = ruta->ruta_sig;
                }
            }
        }

        delete[] colaPrioridad;
    }
};

#endif
