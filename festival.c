#include <stdlib.h>
#include <stdio.h>

typedef struct Asistente {
    char nombre[20], dni[20], cuenta[20], correo[20];
    int nacimiento;
} tAsistente;

typedef struct Concierto
{
    char banda[20];
    int precio, hora;
} tConcierto;

int leerFichero(tConcierto conciertos[]) {
    FILE *conciertosFile;
    conciertosFile = fopen("conciertos.txt", "r");
    tConcierto concierto;

    if (conciertosFile == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    int total = 0;
    while (!feof(conciertosFile)) {
        fscanf(conciertosFile, "%s %d %d", concierto.banda, &concierto.precio, &concierto.hora);
        conciertos[total] = concierto;
        total++;
    }

    return total;
}

tAsistente leerAsistente() {
    tAsistente asistente;
    printf("Introduzca su nombre: ");
    scanf("%s", &asistente.nombre);
    printf("Introduzca su DNI: ");
    scanf("%s", &asistente.dni);
    printf("Introduzca su año de nacimiento: ");
    scanf("%d", &asistente.nacimiento);
    if (2019 - asistente.nacimiento < 18)
    {
        printf("Prohibida la entrada a menores de edad\n");
        exit(1);
    }
    printf("Introduzca su cuenta bancaria: ");
    scanf("%s", &asistente.cuenta);
    printf("Introduzca su correo electronico: ");
    scanf("%s", &asistente.correo);
    return asistente;
}

float totalizarConciertos(tConcierto conciertos[], int cantidad) {
    float costoTotal = 0;

    int i;
    for (i = 0; i < cantidad; i++) {
        printf("%d - %s a las %d por %d\n", i, conciertos[i].banda, conciertos[i].hora, conciertos[i].precio);
        costoTotal += conciertos[i].precio;
    }
    // descuento del 25% para la entrada a todos los conciertos
    costoTotal -= costoTotal * 0.25;
    printf("%d - Todos los conciertos por %0.2f\n", cantidad, costoTotal);

    return costoTotal;
}

int seleccionarConciertos(tConcierto conciertos[], int cantidad, int conciertosElegidos[]) {
    int conciertoSeleccion;
    int repetido = 0;
    char seleccionarOtro;
    int total = 0;
    do {
        printf("Seleccione una opcion: ");
        scanf("%d", &conciertoSeleccion);

        int i;
        for (i = 0; i < total; i++) {
            if (conciertoSeleccion == conciertosElegidos[i]) {
                repetido = 1;
            }
        }

        if (repetido == 0) {
            conciertosElegidos[total] = conciertoSeleccion;
            total++;
        }
        else {
            printf("Ya selecciono este concierto\n");
        }

        printf("Desea seleccionar otro? (s/n) ");
        scanf(" %c", &seleccionarOtro);
        repetido = 0;
    } while (seleccionarOtro == 's');

    return total;
}

int seleccionarCamping() {
    int camping;
    printf("Seleccione uno de nuestros campings\n");
    printf("0 - Ninguno\n");
    printf("1 - Zona comun por 50\n");
    printf("2 - Zona VIP por 100\n");
    scanf("%d", &camping);
    return camping;
}

int seleccionarBus(int camping) {
    int bus = 0;
    if (camping == 1) {
        printf("Seleccione si desea tomar el autobus que lo acercara a la zona de conciertos\n");
        printf("0 - No\n");
        printf("1 - Si por 20\n");
        scanf("%d", &bus);
    }
    return bus;
}

void mostrarFactura(tAsistente asistente, tConcierto conciertos[], int cantidad, float costoTotal, int conciertosElegidos[], int cantidadElegidos, int camping, int bus) {
    tConcierto concierto;
    int festivalCompleto = 0;
    float totalFactura = 0;
    int i;

    printf("DNI: %s\n", asistente.dni);
    printf("Año de nacimiento: %d\n", asistente.nacimiento);
    printf("--- Compra ---\n");

    for (i = 0; i < cantidadElegidos; i++) {
        if (conciertosElegidos[i] == cantidad) {
            festivalCompleto = 1;
            printf("Summer Festival completo -- %0.2f\n", costoTotal);
            totalFactura += costoTotal;
        }
    }

    if (festivalCompleto == 0) {
        for (i = 0; i < cantidadElegidos; i++) {
            concierto = conciertos[conciertosElegidos[i]];
            printf("%s a las %d -- %d\n", concierto.banda, concierto.hora, concierto.precio);
            totalFactura += concierto.precio;
        }
    }

    if (camping == 1) {
        printf("Camping Zona comun -- 50\n");
        totalFactura += 50;
    }
    else if (camping == 2) {
        printf("Camping Zona VIP -- 100\n");
        totalFactura += 100;
    }
    if (bus == 1) {
        printf("Bus -- 20\n");
        totalFactura += 20;
    }

    char aceptar;
    printf("Total a ingresar %0.2f\n", totalFactura);
    printf("Cuenta bancaria: %s\n", asistente.cuenta);
    printf("Correo electronico: %s\n", asistente.correo);
    printf("%s confirmanos que todo esta bien\n", asistente.nombre);
    printf("Desea cogerlo? (s/n) ");
    scanf(" %c", &aceptar);

    if (aceptar == 's') {
        printf("Disfrute de su concierto!\n");
    }
    else {
        printf("Operacion cancelada\n");
    }
}

int main() {
    printf("Bienvenido al summer festival - Conciertos disponibles\n");

    tConcierto conciertos[20];
    int conciertosElegidos[20];
    int cantidad = leerFichero(conciertos);
    tAsistente asistente = leerAsistente();
    float costoTotal = totalizarConciertos(conciertos, cantidad);
    int cantidadElegidos = seleccionarConciertos(conciertos, cantidad, conciertosElegidos);
    int camping = seleccionarCamping();
    int bus = seleccionarBus(camping);

    printf("\n");

    mostrarFactura(asistente, conciertos, cantidad, costoTotal, conciertosElegidos, cantidadElegidos, camping, bus);

    return 0;
}