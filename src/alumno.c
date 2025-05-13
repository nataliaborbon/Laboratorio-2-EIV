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

/** @file alumno.c
 ** @brief Código fuente del módulo para la gestión de alumnos
 **/

/* === Headers files inclusions ==================================================================================== */

#include "alumno.h"
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/**
 * @brief Serializa un campo de texto y su valor en formato JSON.
 *
 * Esta función escribe un par campo-valor en formato JSON dentro del buffer especificado.
 * El formato resultante es: `"campo":"valor"`.
 *
 * @param campo El nombre del campo a serializar.
 * @param valor El valor del campo.
 * @param buffer El buffer donde se escribirá la cadena serializada.
 * @param disponibles La cantidad máxima de bytes disponibles en el buffer.
 * @return int La cantidad de bytes escritos en el buffer, o un valor negativo si ocurrió un error.
 */
static int SerializarCadena(char campo[], char valor[], char buffer[], uint32_t disponibles);

/**
 * @brief Serializa un campo numérico y su valor en formato JSON.
 *
 * Esta función escribe un par campo-valor en formato JSON dentro del buffer especificado.
 * El formato resultante es: `"campo":valor`.
 *
 * @param campo El nombre del campo a serializar.
 * @param valor El valor numérico del campo.
 * @param buffer El buffer donde se escribirá la cadena serializada.
 * @param disponibles La cantidad máxima de bytes disponibles en el buffer.
 * @return int La cantidad de bytes escritos en el buffer, o un valor negativo si ocurrió un error.
 */
int SerializarEntero(char campo[], int valor, char buffer[], uint32_t disponibles);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

int SerializarCadena(char campo[], char valor[], char buffer[], uint32_t disponibles) {
    return snprintf(buffer, disponibles, "\"%s\":\"%s\"", campo, valor);
}

int SerializarEntero(char campo[], int valor, char buffer[], uint32_t disponibles) {
    return snprintf(buffer, disponibles, "\"%s\":%d", campo, valor);
}

/* === Public function implementation ============================================================================== */

int Serializar(const alumno_t alumno, char buffer[], uint32_t size) {
    int escritos = 0;
    int resultado;

    if (size < 2)
        return -1;
    buffer[0] = '{';
    buffer++;
    escritos++;

    resultado = SerializarCadena("nombre", alumno->nombre, buffer, size - escritos);
    if (resultado < 0)
        return -1;
    buffer += resultado;
    escritos += resultado;

    if (escritos + 1 >= size)
        return -1;
    *buffer++ = ',';
    escritos++;

    resultado = SerializarCadena("apellido", alumno->apellido, buffer, size - escritos);
    if (resultado < 0)
        return -1;
    buffer += resultado;
    escritos += resultado;

    if (escritos + 1 >= size)
        return -1;
    *buffer++ = ',';
    escritos++;

    resultado = SerializarEntero("documento", alumno->documento, buffer, size - escritos);
    if (resultado < 0)
        return -1;
    buffer += resultado;
    escritos += resultado;

    if (escritos + 1 >= size)
        return -1;
    *buffer++ = '}';
    escritos++;

    return escritos;
}

/* === End of documentation ======================================================================================== */
