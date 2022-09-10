#include <stdio.h>
#include <pthread.h>

#define NTHREADS 2 
#define TAMVET 10000 

float vetor[TAMVET];

//--funcao executada pelas threads
void * tarefa (void * arg){
    int pos = * ((float *) arg); // armazena a posição do vetor
    vetor[pos-1] *= 1.1; // faz a operação
    pthread_exit(NULL);
}

//funcao principal do programa
int main() {
    pthread_t tid_sistema[NTHREADS]; //identificadores das threads no sistema
    int inicio, final, intervalo, n, k; //variaveis auxiliares
    intervalo = TAMVET/NTHREADS; 
    for (n = 0; n < TAMVET; n++) 
        vetor[n] = n + 1; // preenche o vetor 
    for (n = 0 ; n < NTHREADS;n++){ 
        inicio = n * intervalo; // calcula a posição inicial do intervalo que a thread calcula
        final = (n+1) * intervalo; // calcula a posicao final do intervalo que a thread calcula
        for (k = inicio; k < final; k++){ 
            if (pthread_create(&tid_sistema[n], NULL, tarefa, (void *)&vetor[k]))  // cria as threads
                    printf ("Erro - pthread_create\n");
        }
    }
//pthread_join(garante a mensagem final somente após os cálculos)
    for(n = 0; n < NTHREADS; n++){
        if (pthread_join(tid_sistema[n], NULL))
            printf ("Erro - pthread_create\n");
    }
//verificação
    float verificacao; 
    int auxiliar = 0;
    for(n = 0; n < TAMVET; n++){ 
        verificacao = (n+1)*1.1; 
        if((vetor[n] - verificacao)>0.1){ // estabelece que um erro acima de 0.1 não é adimitido
            auxiliar = 0; 
            break;
        }
        auxiliar = 1; // se chega até aqui, calculou todos corretamente
    }
    if(auxiliar) 
        printf("Valores calculados corretamente\n"); 
    else        
        printf("Valores incorretos\n");
    return 0;
}
