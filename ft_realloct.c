#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char    **ft_realloc_char_array(char **ptr, size_t old_size, size_t new_size) 
{
    char **new_ptr;
    size_t copy_size;
    
    new_ptr = calloc(new_size + 1, sizeof(char *));
    if (new_ptr == NULL) 
    {
        return NULL;
    }
    memcpy(new_ptr, ptr, old_size * sizeof(char *));
    free(ptr); // Liberar el array de punteros anterior
    return new_ptr;
}

int main() {
    // Ejemplo de uso de ft_realloc_char_array
    char **ptr = calloc(4, sizeof(char *)); // Asignar memoria para 3 punteros a char
    if (ptr == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    // Asignar memoria para algunas cadenas y llenar el array
    ptr[0] = strdup("Hola");
    ptr[1] = strdup("Mundo");
    ptr[2] = strdup("!");

    // Redimensionar el array para contener 5 punteros
    printf("antes Cadenas almacenadas en el array:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s\n", ptr[i]);
    }
    ptr = ft_realloc_char_array(ptr, 3, 5);
    if (ptr == NULL) {
        printf("Error al redimensionar memoria\n");
        return 1;
    }

    // // Asignar memoria para más cadenas y llenar el array
    ptr[3] = strdup("Esto");
    ptr[4] = strdup("es");
    //Se puede continuar añadiendo más cadenas según sea necesario

    // Imprimir las cadenas almacenadas en el array
    printf("Cadenas almacenadas en el array:\n");
    for (int i = 0; i < 6; i++) {
        printf("%s\n", ptr[i]);
    }

    // Liberar memoria antes de salir
    for (int i = 0; i < 5; i++) {
        free(ptr[i]); // Liberar cada cadena
    }
    free(ptr); // Liberar el array de punteros

    return 0;
}