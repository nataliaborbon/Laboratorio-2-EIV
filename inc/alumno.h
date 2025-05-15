/*********************************************************************************************************************
Copyright (c) 2025, Natalia Carolina Borbón <nataliacborbon@gmail.com>
Copyright (c) 2025, Laboratorio de Microprocesadores, Universidad Nacional de Tucumán, Argentina

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

#ifndef ALUMNO_H_
#define ALUMNO_H_

/** @file alumno.h
 ** @brief Declaraciones del módulo para la gestión de alumnos
 **/

/* === Headers files inclusions ==================================================================================== */

#include <stdint.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/**
 * @brief Estructura que representa un alumno.
 */
typedef struct alumno_s * alumno_t; /**< Tipo de puntero a alumno_s. */

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Función para crear un nuevo alumno
 *
 * Esta función asigna memoria para un nuevo alumno y copia los datos
 * proporcionados para el nombre, apellido y documento de identidad.
 *
 * @param nombre    Nombre del alumno
 * @param apellido  Apellido del alumno
 * @param dni       Documento del alumno
 * @return alumno_t Referencia al nuevo alumno creado
 */
alumno_t CrearAlumno(char * nombre, char * apellido, uint32_t dni);

/**
 * @brief Función para serializar los datos de un alumno en formato JSON.
 *
 * Esta función toma los datos de un alumno (nombre, apellido y documento) y los convierte
 * en una cadena de caracteres con formato JSON, incluyendo llaves y separadores entre campos.
 * El formato resultante es: `{"nombre":"Juan","apellido":"Perez","documento":12345678}`.
 *
 * @param alumno    Referencia al alumno a serializar.
 * @param buffer    El buffer donde se escribirá la cadena serializada.
 * @param size      La cantidad máxima de bytes disponibles en el buffer.
 * @return int      La cantidad de bytes escritos en el buffer, o -1 si ocurrió un error (espacio insuficiente).
 */
int Serializar(const alumno_t alumno, char buffer[], uint32_t size);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ALUMNOS_H_ */
