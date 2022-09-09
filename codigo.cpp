#include <iostream>
#include <fstream>

using namespace std;

// Punto 2 Funcion para ordenar el vector de manera ascendente
void ordenarvector(float distancia[][5], int numclientemax, int canttipoprod, string tipoprod2[5]){
    float valor;
    int j;
    string valor2;
 
    for (int i = 1; i < canttipoprod; i++)
    {
        valor2 = tipoprod2[i];
        valor = distancia[numclientemax][i];
        j = i;
        while (j > 0 && valor < distancia[numclientemax][j-1])
        {
            distancia[numclientemax][j] = distancia[numclientemax][j-1];
            tipoprod2[j] = tipoprod2[j-1];
            j--;
        }
        distancia[numclientemax][j] = valor;
        tipoprod2[j] = valor2; //para que quede el numero de km recorridos con su respectivo producto aunque hayamos ordenado el vector de manera ascendente
    };
};

int main(){
    
    const int cantclie{8};
    const int canttipoprod{5};
    string cliente[cantclie]{"Bat", "Bi", "Hiru", "Lau", "Bost", "Sei", "Zazpi" , "Zortzi"};
    string tipoprod[canttipoprod]{"Alimenticios", "Electrónicos", "Metálicos", "Textiles", "Químicos"};
    string tipoprod2[canttipoprod]{"Alimenticios", "Electrónicos", "Metálicos", "Textiles", "Químicos"}; //para no modificar ni alterar el vector "tipoprod" original

    
    float distancia[cantclie][canttipoprod]{}; //acumulado de distancia por clientes y tipo de producto
    int entrega[canttipoprod]{}; //acumulado de entregas por tipo de producto sin importar cliente
    float peso_clie_tipoprod[cantclie][canttipoprod]{}; //acumulado de pesos en kg por clientes y tipo de producto

    //Leo los datos del archivo y los vuelco en los vectores correspondientes que usare posteriormente
    ifstream adatos;
    adatos.open("Datos.txt");
    if (!adatos) {
        cout << "No se puedo abrir el archivo de datos" << endl;
        return 1;
    }

    int iclie, iprod;
    float peso2 = 0;
    float dist = 0;
   
   
    while (adatos >> iclie >> iprod >> peso2 >> dist) {
        peso_clie_tipoprod[iclie][iprod] += peso2;
        distancia[iclie][iprod] += dist;
        entrega[iprod]++;
    }
    adatos.close();
    

    // Punto 1 
    // Funcion listado peso > 13000 kg acumulados

    int clientecontador[cantclie]{};
    cout << "Listado por clientes de los tipos de productos que superen los 13000 ks acumulados: " << endl;
    for(int i = 0; i < cantclie; i++){
        for (int j = 0; j < canttipoprod; j++){
            if (peso_clie_tipoprod[i][j] > 13000){
                cout<< " El cliente " << cliente[i] << "  con el producto " << tipoprod[j] << endl;
                clientecontador[i] += 1;
            };
        };
    };

    // Funcion para probar que ande bien el clientecontador
    //for (int i = 0; i < cantclie; i++){
    //    cout << "cliente: " << cliente[i] << " tiene " << clientecontador[i] << " productos con mas de 13000 kg acumulados" << endl;
    //};


    cout<< "--------------------------------------------------------"<< endl;

    // Punto 2 
    // Cliente con mayor cantidad tipos de producto que haya superado 13000kg
    
    int max = 0;
    int numclientemax = 0;
    for (int i = 0; i < cantclie ; i++){
        if(clientecontador[i] > max){
			max = clientecontador[i];
			numclientemax = i;
		};
    };
    
    // Funcion para probar que devuelva bien el cliente mayor
    // cout<< " El cliente " << cliente[numclientemax] << " es el mayor" << endl;

    cout << "Listado de Km recorridos por tipo de producto (ascendente): " << endl;

    // Ordeno al vector de manera ascendente
    ordenarvector(distancia, numclientemax, canttipoprod, tipoprod2);

    // Hago el listado con el vector ordenado
    for (int j = 0; j < canttipoprod; j++){
        cout<< " El cliente " << cliente[numclientemax] << "  con el producto " << tipoprod2[j] << " tiene un total de km de :  " << distancia[numclientemax][j] << endl;
    };

    cout<< "--------------------------------------------------------"<< endl;
    
    // Punto 3 
    // en la ultima posicion del vector "tipoprod2" siempre va a estar el producto con mayor cantidad de kilometros recorridos porque esta ordenado de manera ascendente, por lo tanto lo que me queda hacer es saber que tipo de producto es y compararlo con el vector original "tipoprod" para saber su real valor (en numeros) y encontrar cuantas entregas hizo con el vector "entrega"

    string var_prod_entrega = tipoprod2[4];
    for (int i = 0; i < canttipoprod ; i++){
        if (tipoprod[i] == var_prod_entrega){
            cout << "Cantidad de entregas para el tipo de producto " << tipoprod[i] << ": " << entrega[i]<< endl;
        };
    };
    
    return 0;
}
