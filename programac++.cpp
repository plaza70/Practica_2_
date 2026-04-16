#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() {

    ifstream archivo("datos_pinza.txt");
    ofstream salida("resultado_pinza.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    const int MAX = 100000;

    int ids[MAX];
    float datos[MAX][3]; // galga, izq, der
    float galga[MAX];
    float fuerza_izq[MAX];
    float fuerza_der[MAX];
    string estado[MAX];

    int n = 0;

    // Leer datos (con protección)
    while (archivo >> ids[n] >> datos[n][0] >> datos[n][1] >> datos[n][2]) {

        if (n >= MAX) {
            cout << "Se alcanzo el limite de datos" << endl;
            break;
        }

        galga[n] = datos[n][0];
        fuerza_izq[n] = datos[n][1];
        fuerza_der[n] = datos[n][2];

        n++;
    }

    archivo.close();

    if (n == 0) {
        cout << "No se leyeron datos" << endl;
        return 1;
    }

    // Mostrar datos
    for (int i = 0; i < n; i++) {
        cout << "ID: " << ids[i]
             << " Galga: " << galga[i]
             << " Izq: " << fuerza_izq[i]
             << " Der: " << fuerza_der[i] << endl;
    }

    // Calcular medias
    float suma_galga = 0, suma_izq = 0, suma_der = 0;

    for (int i = 0; i < n; i++) {
        suma_galga += galga[i];
        suma_izq += fuerza_izq[i];
        suma_der += fuerza_der[i];
    }

    float media_galga = suma_galga / n;
    float media_izq = suma_izq / n;
    float media_der = suma_der / n;

    cout << "\nMedia galga: " << media_galga << endl;
    cout << "Media fuerza izquierda: " << media_izq << endl;
    cout << "Media fuerza derecha: " << media_der << endl;

    // Evaluar estabilidad
    for (int i = 0; i < n; i++) {
        float diferencia = fabs(fuerza_izq[i] - fuerza_der[i]);

        if (diferencia > 0.15)
            estado[i] = "INESTABLE";
        else
            estado[i] = "ESTABLE";

        cout << "Estado muestra " << ids[i] << ": " << estado[i] << endl;
    }

    // Escribir archivo de salida
    salida << "RESULTADOS DEL SISTEMA DE PINZA ROBOTICA\n\n";

    salida << "Datos:\n";
    for (int i = 0; i < n; i++) {
        salida << ids[i] << " "
               << galga[i] << " "
               << fuerza_izq[i] << " "
               << fuerza_der[i] << "\n";
    }

    salida << "\nMedias:\n";
    salida << "Galga = " << media_galga << "\n";
    salida << "Fuerza izquierda = " << media_izq << "\n";
    salida << "Fuerza derecha = " << media_der << "\n";

    salida << "\nClasificacion:\n";
    for (int i = 0; i < n; i++) {
        salida << ids[i] << " " << estado[i] << "\n";
    }

    salida.close();

    return 0;
}
