#include <stdio.h>
#include <setjmp.h>


jmp_buf save_point;


double dividir(){

        double resultado, divisor, dividendo;
        char bufferdivisor[100];
        char bufferdividendo[100];
        printf("Bem vindo a calculadora de divisao!\n");
        printf("Digite o dividendo:\n");
        printf("> ");

        if(fgets(bufferdividendo, sizeof(bufferdividendo), stdin) == NULL){
            longjmp(save_point, 100);
        }

        printf("> ");
        printf("Digite o divisor:\n");

        if(fgets(bufferdivisor, sizeof(bufferdivisor), stdin) == NULL){
            longjmp(save_point, 101);

        }

        if(bufferdivisor[0] == '\n' || bufferdividendo[0] == '\n'){
            longjmp(save_point, 102);
        }

        int resultado_extrair_divisor = sscanf(bufferdivisor, "%lf", &divisor);
        int resultado_extrair_dividendo = sscanf(bufferdividendo, "%lf", &dividendo);

        if(resultado_extrair_dividendo != 1|| resultado_extrair_divisor != 1){
            longjmp(save_point, 103);
        }

        if(divisor == 0){
            longjmp(save_point, 104);
        }

        return dividendo / divisor;

}


int main() {

    while(1){
        int codigo_retorno = setjmp(save_point);

        if(codigo_retorno == 0){
            double resultado;
            resultado = dividir();
            printf("Resultado da divisão: %.2lf\n", resultado); 

        }  else if(codigo_retorno == 100) {
            printf("Erro ao ler dividendo\n");
        } else if(codigo_retorno == 101){
            printf("Erro ao ler divisor!\n");
        } else if(codigo_retorno == 102){
            printf("Divisor ou dividendo não informados!\n");
        } else if(codigo_retorno == 103){
            printf("Dividendo ou divisor inválidos!\n");
        } else if(codigo_retorno == 104){
            printf("Divisor igual a 0! Operacao invalida...\n");
        } else  {
            printf("Codigo invalido...");
        }

    }

    


    return 0;
} 