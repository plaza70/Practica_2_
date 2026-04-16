#!/bin/bash

# Ejecutar el programa en segundo plano
./programa &

PID=$!

echo "Proceso lanzado con PID: $PID"

# Esperar a que termine
wait $PID

echo "Proceso finalizado"

# Comprobar si sigue activo
if ps -p $PID > /dev/null
then
    echo "El proceso sigue activo. Finalizando..."
    kill $PID
else
    echo "El proceso ya no está activo."
fi
