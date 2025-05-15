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
#include "config.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/* === Macros definitions ========================================================================================== */

#ifndef ALUMNOS_MAX_INSTANCIAS
/** @brief Cantidad máxima de alumnos */
#define ALUMNOS_MAX_INSTANCIAS 2
#endif

/* === Private data type declarations ============================================================================== */

struct alumno_s {
    char nombre[20];    /**< Nombre del alumno. */
    char apellido[20];  /**< Apellido del alumno. */
    uint32_t documento; /**< Número de documento del alumno. */
#ifndef USAR_MEMORIA_DINAMICA
    bool ocupado; /**< Indica si la instancia esta ocupada. */
#endif
};

/* === Private function declarations =============================================================================== */

/**
 * @brief Crea una nueva instancia de alumno.
 *
 * Esta función busca en un arreglo interno una posición libre para reservarla
 * como una nueva instancia de alumno. Marca la instancia como ocupada y devuelve
 * un puntero a ella. Si no hay instancias libres disponibles, devuelve NULL.
 *
 * @internal
 * @return alumno_t Puntero a la nueva instancia de alumno si hay espacio disponible,
 * o NULL si se alcanzó el límite máximo de instancias.
 */
static alumno_t CrearInstancia();

/**
 * @brief Serializa un campo y su valor entero en JSON.
 *
 * Esta función escribe un par campo-valor en formato JSON dentro del buffer especificado.
 * El formato resultante es: `"campo":"valor"`.
 *
 * @internal
 * @param campo El nombre del campo a serializar.
 * @param valor El valor del campo.
 * @param buffer El buffer donde se escribirá la cadena serializada.
 * @param disponibles La cantidad máxima de bytes disponibles en el buffer.
 * @return int La cantidad de bytes escritos en el buffer, o un valor negativo si ocurrió un error.
 */
int static SerializarCadena(char campo[], char valor[], char buffer[], uint32_t disponibles);

/**
 * @brief Serializa un campo de texto y su valor en formato JSON.
 *
 * Esta función escribe un par campo-valor en formato JSON dentro del buffer especificado.
 * El formato resultante es: `"campo":valor`.
 *
 * @internal
 * @param campo El nombre del campo a serializar.
 * @param valor El valor numérico del campo.
 * @param buffer El buffer donde se escribirá la cadena serializada.
 * @param disponibles La cantidad máxima de bytes disponibles en el buffer.
 * @return int La cantidad de bytes escritos en el buffer, o un valor negativo si ocurrió un error.
 */
static int SerializarEntero(char campo[], int valor, char buffer[], uint32_t disponibles);

/* === Private variable definitions ================================================================================ */

#ifndef USAR_MEMORIA_DINAMICA
static struct alumno_s instancias[ALUMNOS_MAX_INSTANCIAS] = {0};
#endif

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

#ifndef USAR_MEMORIA_DINAMICA
static alumno_t CrearInstancia() {
    int i;
    alumno_t self = NULL;
    for (i = 0; i < ALUMNOS_MAX_INSTANCIAS; i++) {
        if (!instancias[i].ocupado) {
            instancias[i].ocupado = true;
            self = &instancias[i];
            break;
        }
    }
    return self;
}
#endif

int SerializarCadena(char campo[], char valor[], char buffer[], uint32_t disponibles) {
    return snprintf(buffer, disponibles, "\"%s\":\"%s\"", campo, valor);
}

int SerializarEntero(char campo[], int valor, char buffer[], uint32_t disponibles) {
    return snprintf(buffer, disponibles, "\"%s\":%d", campo, valor);
}

/* === Public function implementation ============================================================================== */

alumno_t CrearAlumno(char * nombre, char * apellido, uint32_t dni) {
#ifdef USAR_MEMORIA_DINAMICA
    alumno_t self = malloc(sizeof(struct alumno_s));
#else
    alumno_t self = CrearInstancia;
#endif
    if (self != NULL) {
        self->documento = dni;
        strncpy(self->nombre, nombre, sizeof(self->nombre) - 1);
        strncpy(self->apellido, apellido, sizeof(self->apellido) - 1);
    }
    return self;
}

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
