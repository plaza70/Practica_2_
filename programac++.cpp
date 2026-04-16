#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() {

    ifstream archivo("datos_pinza.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    const int MAX = 100000;

    int ids[MAX];
    float galga[MAX], izq[MAX], der[MAX];
    string estado[MAX];

    int n = 0;

    // Leer datos
    while (archivo >> ids[n] >> galga[n] >> izq[n] >> der[n]) {
        if (n >= MAX) break;
        n++;
    }

    archivo.close();

    if (n == 0) {
        cout << "No hay datos" << endl;
        return 1;
    }

    // Calcular medias
    float suma_g = 0, suma_i = 0, suma_d = 0;

    for (int i = 0; i < n; i++) {
        suma_g += galga[i];
        suma_i += izq[i];
        suma_d += der[i];
    }

    float media_g = suma_g / n;
    float media_i = suma_i / n;
    float media_d = suma_d / n;

    // Evaluar estabilidad
    for (int i = 0; i < n; i++) {
        if (fabs(izq[i] - der[i]) > 0.15)
            estado[i] = "INESTABLE";
        else
            estado[i] = "ESTABLE";
    }

    // Salida a .txt

    cout << "ID: " << ids[0]
         << " Galga: " << galga[0]
         << " Izq: " << izq[0]
         << " Der: " << der[0] << endl;

    cout << endl;

    cout << "Media galga: " << media_g << endl;
    cout << "Media fuerza izquierda: " << media_i << endl;
    cout << "Media fuerza derecha: " << media_d << endl;

    cout << endl;

    cout << "Estado muestra " << ids[0] << ": " << estado[0] << endl;

    ofstream salida("resultado_pinza.txt");

    salida << "RESULTADOS DEL SISTEMA DE PINZA ROBOTICA\n\n";

    salida << "Datos:\n\n";
    salida << ids[0] << " "
           << galga[0] << " "
           << izq[0] << " "
           << der[0] << "\n\n";

    salida << "Medias:\n\n";
    salida << "Galga = " << media_g << "\n";
    salida << "Fuerza izquierda = " << media_i << "\n";
    salida << "Fuerza derecha = " << media_d << "\n\n";

    salida << "Clasificacion:\n\n";
    salida << ids[0] << " " << estado[0] << "\n";

    salida.close();
    return 0;
}
