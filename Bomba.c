#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define MIN_DOSE 1

int historicoAcucar[3];

//simula a leitura do nível de açúcar no sangue
int lerAcucar() {
    return rand() % 71 + 80; //valores entre 80 e 150
}

//calcula a dose de insulina a ser administrada
int calcularDoseInsulina(int r0, int r1, int r2) {
    if (r2 < r1) {
        return 0;
    } else if (r2 == r1) {
        return 0;
    } else if ((r2 - r1) >= (r1 - r0)) {
        int dose = round((r2 - r1) / 4.0);
        return (dose > 0) ? dose : MIN_DOSE;
    }
    return 0;
}

//executa o autoteste do sistema
bool autoteste() {
    bool sensoresFuncionando = rand() % 2;
    bool bateriaOk = rand() % 2;
    bool conexaoOk = rand() % 2;
    
    if (!sensoresFuncionando) {
        printf("Alerta:Falha nos sensores!\n");
    }
    if (!bateriaOk) {
        printf("Alerta:Bateria fraca!\n");
    }
    if (!conexaoOk) {
        printf("Alerta:Problema de conexão!\n");
    }
    
    return sensoresFuncionando && bateriaOk && conexaoOk;
}

int main() {
    srand(time(NULL));
    
    //inicializa os níveis de açúcar no sangue
    for (int i = 0; i < 3; i++) {
        historicoAcucar[i] = lerAcucar();
    }
    
    while (1) {
        if (!autoteste()) {
            printf("Erro no sistema. Verifique os alertas.\n");
            break;
        }
        
        //atualiza os valores históricos
        historicoAcucar[0] = historicoAcucar[1];
        historicoAcucar[1] = historicoAcucar[2];
        historicoAcucar[2] = lerAcucar();
        
        int dose = calcularDoseInsulina(historicoAcucar[0], historicoAcucar[1], historicoAcucar[2]);
        
        printf("Leitura do sensor: %d mg/dL\n", historicoAcucar[2]);
        printf("Dose de insulina recomendada: %d unidades\n\n", dose);
        
        sleep(600); //aguarda 10 minutos (600 segundos)
    }
    
    return 0;
}
