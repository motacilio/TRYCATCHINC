#include <stdio.h>
#include <setjmp.h>
#include <stdbool.h>

jmp_buf save_point;

enum ErrorCodes {
    ERROR_READ_DIVIDEND = 100,
    ERROR_READ_DIVISOR = 101,
    ERROR_EMPTY_INPUT = 102,
    ERROR_INVALID_INPUT = 103,
    ERROR_DIVISION_BY_ZERO = 104
};


double dividir(){

        double resultado, divisor, dividendo;
        char bufferdivisor[100];
        char bufferdividendo[100];


        printf("Bem vindo a calculadora de divisao!\n");
        printf("Digite o dividendo:\n");
        printf("> ");


        /*
        as chamadas de longjmp representam o throw, caso o if seja verdadeiro, ele chama o longjmp
        "jogando" (throw) um codigo de erro para o ponto do programa especificado na variavel save_point
        
        */
        if(fgets(bufferdividendo, sizeof(bufferdividendo), stdin) == NULL){
            longjmp(save_point, ERROR_READ_DIVIDEND);
        }

        printf("> ");
        printf("Digite o divisor:\n");

        if(fgets(bufferdivisor, sizeof(bufferdivisor), stdin) == NULL){
            longjmp(save_point, ERROR_READ_DIVISOR);

        }

        if(bufferdivisor[0] == '\n' || bufferdividendo[0] == '\n'){
            longjmp(save_point, ERROR_EMPTY_INPUT);
        }

        int resultado_extrair_divisor = sscanf(bufferdivisor, "%lf", &divisor);
        int resultado_extrair_dividendo = sscanf(bufferdividendo, "%lf", &dividendo);

        if(resultado_extrair_dividendo != 1|| resultado_extrair_divisor != 1){
            longjmp(save_point, ERROR_INVALID_INPUT);
        }

        if(divisor == 0){
            longjmp(save_point, ERROR_DIVISION_BY_ZERO);
        }

        return dividendo / divisor;

}


int main() {
    while(1){
        
        /*
        Esta parte representa o try-catch
        na primeira chamado da funcao setjmp ele retorna 0, no if codigo == 0 é onde seria o try pois
        sempre será executado na primeira vez
        caso ocorra alguma exceção na funcao dividir, o longjmp vai jogar o erro pra fora e retornar na linha
        de declaração do setjmp, que dessa vez vai retornar o código de retorno do erro ao invés de 0 e vai
        executar o else if correspondente ao codigo emitido
        */
        int codigo_retorno = setjmp(save_point);

        if(codigo_retorno == 0){
            double resultado;
            resultado = dividir();
            printf("Resultado da divisão: %.2lf\n", resultado); 
            

        } else {
            if(codigo_retorno == ERROR_READ_DIVIDEND) {
                printf("Erro ao ler dividendo\n");
            } else if(codigo_retorno == ERROR_READ_DIVISOR){
                printf("Erro ao ler divisor!\n");
            } else if(codigo_retorno == ERROR_EMPTY_INPUT){
                printf("Divisor ou dividendo não informados!\n");
            } else if(codigo_retorno == ERROR_INVALID_INPUT){
                printf("Dividendo ou divisor inválidos!\n");
            } else if(codigo_retorno == ERROR_DIVISION_BY_ZERO){
                printf("Divisor igual a 0! Operacao invalida...\n");
            } else  {
                printf("Codigo invalido...");
            }
        } 

        /*
        Essa linha representa o finally, ela sempre será executada
        */
        
        printf("Continuando...\n");
        printf("-------------------------------------------------\n\n");

    }

    


    return 0;
}