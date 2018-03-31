#include <iostream>
#include <vector>
using namespace std ;

void mostrarLista(vector <int> lista){
 int size = lista.size();
    for(int i = 0; i < size; i++){
       printf("%d ", lista.at(i));
     }
    printf("\n");
 }

vector<int> rodar(vector<int> &lista){
    lista.push_back(lista.front()); //ADICIONA NA 1 POSICAO O ELEMENTO DA ULTIMA
    lista.erase(lista.begin());     //remover da posicao
     return lista;
}

vector<int> matar(vector<int> &lista){
    mostrarLista(lista);
    lista.push_back(lista.front()); //adicionar na primeira posicao o ultimo elemento
    lista.erase(lista.begin()); //erase: REMOVE O ELEMENTO DO VECTOR
    lista.erase(lista.begin());
    return lista;
}

int main() {
    int qtd= 0;
    int escolha = 0;
    int saltos =0;
    scanf("%d %d",&qtd,&escolha);
    vector <int> lista;
    //ENCHENDO O VETOR
    for(int i = 1;i <=qtd ; i++){
        lista.push_back(i);
    }

    while (lista.front()!= escolha) {
        rodar(lista);
    }
    //ENQUANTO NAO SOBRAR APENAS UM VIVO
    //MATA...
    while(lista.size()!= 1){
        matar(lista);
        //FAZENDO TESTES PARA FAZER OS n SALTOS
        if(saltos <= 2){                            //SÓ PODERÁ HAVER DOIS SALTOS DE n PARTICIPANTES
            if(lista.front() == 5){
                saltos++;
                printf("Agr 5 saltos...\n");
                for(int i=0;i<5;i++){                //SE O ELEMENTO QUE TA COM A ESPADA FOR NUMERO 5
                    rodar(lista);                   // A ESPADA ANDA MAIS CINCO PESSOAS
                }
            }
            if(lista.front() == 3){                 //SE O ELEMENTO QUE TA COM A ESPADA FOR 3
                saltos++;
                printf("Agr 3 saltos...\n");
                for(int i=0;i<3;i++){               // A ESPADA ANDA MAIS TRES PESSOAS
                    rodar(lista);
                }
            }
        }
    }
    mostrarLista(lista);

return 0;
}
