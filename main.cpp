#include <iostream>
#include <fstream>

using namespace std;

ifstream abrir_archivo (string file_name) {
    ifstream archivo;
    archivo.open(file_name);
    if(!archivo) {
        cout << "Error al abrir el archivo" << endl;
        EXIT_FAILURE;
    }
    return archivo;
}

int mejor_cliente(int listado[], int largo) {
    
    int max = 0;
    int pos;
    
    for(int a=0; a<largo; a++) {
        if(listado[a] > max) {
            max = listado[a];
            pos = a;
        }
    }
    return pos;
}

void ordenar_keys(float vec[], int keys[], int dim) {

    for(int b=0; b<dim; b++) {
        keys[b] = b;
    }

    float aux;

    for(int c=0; c<dim; c++) {
        for(int d=c+1; d<dim; d++) {
            if(vec[c] > vec[d]) {
                aux = keys[c];
                keys[c] = keys[d];
                keys[d] = aux;
            }
        }
    }
}


int main() {

    ifstream archivo_nombres = abrir_archivo("Nombres.txt");

    const int cant_c = 8;
    string clientes[cant_c];
    const int cant_p = 5;
    string productos[cant_p];
    int largo = cant_p + cant_c;
    int r=0;

    for (int a=0; a<largo ; a++){ //leer archivo "nombres.txt". Crear un arreglo con los nombres de clientes y otro arrglo con los nombres de productos

        if(a<cant_c) {
            archivo_nombres >> clientes[a];
        }

        else {
            archivo_nombres >> productos[r];
            r++;
        }
    }
    archivo_nombres.close();

    ifstream archivo_datos = abrir_archivo("Datos.txt");

    int codigo_cliente;
    int codigo_producto;
    float peso;
    float distancia;
    float producto_por_cliente[cant_c][cant_p] {0};
    float kilometro_por_producto [cant_c][cant_p] {0};
    int entregas_por_producto[cant_p] {0};

    while (archivo_datos >> codigo_cliente) {
        archivo_datos >> codigo_producto;
        archivo_datos >> peso;
        archivo_datos >> distancia;
        producto_por_cliente[codigo_cliente][codigo_producto] += peso;
        kilometro_por_producto[codigo_cliente][codigo_producto] += distancia;

        for(int i=0; i<cant_p; i++) {
            if(codigo_producto == i) {
                entregas_por_producto[i] ++;
            }
        }
    }
    archivo_datos.close();

    cout << "Lista de productos por cliente mayores a 13000:" << endl;
    cout << "Cliente\tProducto\tPeso" << endl;
    cout << "=======\t============\t====" << endl;
    
    int clientes_con_mas_de_13000[cant_c] {0};

    for (int b=0; b<cant_c; b++) {
        for (int c=0; c<cant_p; c++) {
            if (producto_por_cliente[b][c] > 13000) {
                cout << clientes[b] << "\t" << productos[c] << "\t" << producto_por_cliente[b][c] << endl; 
                clientes_con_mas_de_13000[b]++;
            }
        }
    }

    cout<<"--------------------------------------"<<endl;

    int pos = mejor_cliente(clientes_con_mas_de_13000, cant_c);

    int keys[cant_p];

    ordenar_keys(kilometro_por_producto[pos], keys, cant_p);
    
    cout<<"el cliente con mas productos que superaron 13000 es "<<clientes[pos]<<", y el orden ascendente de sus productos por distancia recorrida es: "<<endl;
    cout<<endl;

    for(int d=0; d<cant_p; d++) {
    cout<<productos[keys[d]]<<"\t"<<kilometro_por_producto[pos][keys[d]]<<" kms"<<endl;
    }
    
    cout<<endl;

    cout<<"entonces el producto con mas kilometros fue "<<productos[keys[cant_p - 1]]<<" y se hicieron "<<entregas_por_producto[cant_p - 1]<<" entregas"<<endl;

    return 0; 
}


    