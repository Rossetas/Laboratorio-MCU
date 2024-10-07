#!/usr/bin/python
import serial  # Paquete para comunicación serial
import csv     # Paquete para manejar archivos CSV
import time    # Paquete para manejar retrasos

# Configuración
baud = 9600
filename = "DATA.csv"
samples_per_line = 5
serial_port = "/tmp/ttyS1"

# Inicialización
try:
    ser = serial.Serial(serial_port, baud, timeout=1)  # Conexión con el puerto serial
    print("Conexión serial exitosa.")
except serial.SerialException as e:
    print(f"No se pudo conectar al puerto serial: {e}")
    exit()

# Inicialización del archivo CSV con 'with' para asegurarse que se cierre correctamente
with open(filename, 'w', newline='') as csvfile:
    csv_writer = csv.writer(csvfile)
    print("Archivo CSV creado exitosamente.")

    data_row = []  # Lista para almacenar datos temporales
    while True:
        try:
            # Lee una línea de datos desde el puerto serial
            raw_data = ser.readline().decode('utf-8').strip()  
            if raw_data:  # Si se recibe un dato válido
                print(f"Dato recibido: {raw_data}")
                data_row.append(raw_data)

                # Cada 4 muestras, escribimos una nueva fila en el archivo CSV
                if len(data_row) == samples_per_line:
                    csv_writer.writerow(data_row)
                    print(f"Datos guardados en CSV: {data_row}")
                    data_row = []  # Reseteamos la lista para las próximas 4 muestras

        except serial.SerialException as e:
            print(f"Error en la comunicación serial: {e}")
            break
        except Exception as e:
            print(f"Error inesperado: {e}")
            break

# Cerrar la conexión serial al terminar
ser.close()
print("Conexión serial cerrada.")
