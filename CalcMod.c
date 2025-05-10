#include <stdio.h>

// Calcula o MDC entre dois números usando o Algoritmo de Euclides
int calcular_mdc(int num1, int num2) {
    printf("   Calculando MDC(%d, %d): ", num1, num2);
    while (num2 != 0) {
        int resto = num1 % num2;
        num1 = num2;
        num2 = resto;
        printf("MDC(%d, %d) -> ", num1, num2);
    }
    printf("%d\n", num1);
    return num1;
}

// Verifica se um número é primo
int numero_primo(int valor) {
    if (valor <= 1) return 0;
    if (valor <= 3) return 1;
    if (valor % 2 == 0 || valor % 3 == 0) return 0;

    for (int i = 5; i * i <= valor; i += 6)
        if (valor % i == 0 || valor % (i + 2) == 0)
            return 0;

    return 1;
}

// Calcula o inverso modular de num mod mod
int inverso_mod(int num, int mod) {
    int original = mod, temp, quoc, x_ant = 0, x_atual = 1;

    printf("\n2. Buscando inverso modular de %d em Zn (%d)...\n", num, mod);

    if (mod == 1) return 0;

    while (num > 1) {
        quoc = num / mod;
        temp = mod;
        mod = num % mod;
        num = temp;

        temp = x_ant;
        x_ant = x_atual - quoc * x_ant;
        x_atual = temp;

        printf("   Etapa: q = %d, mod = %d, num = %d, x0 = %d, x1 = %d\n", quoc, mod, num, x_ant, x_atual);
    }

    return (x_atual < 0) ? x_atual + original : x_atual;
}

// Calcula o totiente de Euler φ(n)
int totiente_de_euler(int n) {
    if (n == 1) return 1;
    if (numero_primo(n)) return n - 1;

    int resultado = n;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            resultado -= resultado / i;
        }
    }

    if (n > 1) resultado -= resultado / n;

    return resultado;
}

// Potenciação modular eficiente
int potenciacao_modular(int base, int expoente, int modulo) {
    int resposta = 1;
    base %= modulo;

    while (expoente > 0) {
        if (expoente % 2 == 1)
            resposta = (resposta * base) % modulo;

        expoente >>= 1;
        base = (base * base) % modulo;
    }

    return resposta;
}

int main() {
    int valorH, valorG, modulo, expoente, moduloFinal;

    printf("Avaliação 1, questão 9\n");
    printf("Disciplina: Matemática Discreta II\n");
    printf("Professor(a): Cristiane Loesch de Souza Costa\n");
    printf("Aluno: Pedro Araujo Lucena\n");
    printf("Matrícula: 222007077\n\n");

    // Entrada dos valores
    printf("Informe o valor de H: ");
    scanf("%d", &valorH);
    printf("Informe o valor de G: ");
    scanf("%d", &valorG);
    printf("Informe o valor de n: ");
    scanf("%d", &modulo);
    printf("Informe o expoente x: ");
    scanf("%d", &expoente); // Corrigido aqui!
    printf("Informe o módulo final n1: ");
    scanf("%d", &moduloFinal);

    printf("\n=== INÍCIO DA EXECUÇÃO ===\n");

    // Etapa 1
    printf("\n1. Verificando se G (%d) e n (%d) são coprimos...\n", valorG, modulo);
    int resultado_mdc1 = calcular_mdc(valorG, modulo);

    if (resultado_mdc1 != 1) {
        printf("   ERRO: G e n não são coprimos (MDC = %d). Divisão modular não permitida.\n", resultado_mdc1);
        return 1;
    } else {
        printf("   OK: G e n são coprimos. Continuando...\n");
    }

    // Etapa 2
    int inversoG = inverso_mod(valorG, modulo);
    printf("   Inverso modular: %d\n", inversoG);

    // Etapa 3
    printf("\n3. Calculando base a = H * inv(G) mod n...\n");
    int base = (valorH % modulo) * (inversoG % modulo) % modulo;
    printf("   a = (%d * %d) mod %d = %d\n", valorH, inversoG, modulo, base);

    // Etapa 4
    printf("\n4. Verificando se a (%d) e n1 (%d) são coprimos...\n", base, moduloFinal);
    int resultado_mdc2 = calcular_mdc(base, moduloFinal);

    if (resultado_mdc2 != 1) {
        printf("   ERRO: %d e %d não são coprimos (MDC = %d). Não é possível aplicar Fermat/Euler.\n", base, moduloFinal, resultado_mdc2);
        return 1;
    } else {
        printf("   OK: %d e %d são coprimos.\n", base, moduloFinal);
    }

    // Etapa 5
    printf("\n5. Verificando se %d é primo...\n", moduloFinal);
    int eh_primo = numero_primo(moduloFinal);
    int totiente = (eh_primo) ? moduloFinal - 1 : totiente_de_euler(moduloFinal);

    // Etapas 6 e 7
    if (eh_primo) {
        printf("   %d é primo. Usaremos o Pequeno Teorema de Fermat.\n", moduloFinal);
        printf("\n6. Aplicando Fermat:\n");
        printf("   Como %d é primo, %d^%d ≡ 1 mod %d\n", moduloFinal, base, totiente, moduloFinal);
    } else {
        printf("   %d não é primo. Usaremos o Teorema de Euler.\n", moduloFinal);
        printf("\n7. Aplicando Euler:\n");
        printf("   φ(%d) = %d\n", moduloFinal, totiente);
        printf("   Então, %d^%d ≡ 1 mod %d\n", base, totiente, moduloFinal);
    }

    // Etapa 8
    printf("\n8. Decompondo o expoente: x = q*φ(n1) + r\n");
    int resto = expoente % totiente;
    int quociente = expoente / totiente;
    printf("   x = %d = %d*%d + %d\n", expoente, totiente, quociente, resto);

    // Etapa 9
    printf("\n9. Reescrevendo %d^%d como ((%d^%d)^%d * %d^%d) mod %d...\n",
           base, expoente, base, totiente, quociente, base, resto, moduloFinal);

    // Etapa 10
    printf("\n10. Calculando valores intermediários...\n");
    int base_totiente = potenciacao_modular(base, totiente, moduloFinal);
    printf("   %d^%d mod %d = %d\n", base, totiente, moduloFinal, base_totiente);

    int potencia_total = potenciacao_modular(base_totiente, quociente, moduloFinal);
    printf("   (%d^%d)^%d mod %d = %d\n", base, totiente, quociente, moduloFinal, potencia_total);

    int resto_potencia = potenciacao_modular(base, resto, moduloFinal);
    printf("   %d^%d mod %d = %d\n", base, resto, moduloFinal, resto_potencia);

    // Etapa 11
    printf("\n11. Resultado final:\n");
    int resultado = (potencia_total * resto_potencia) % moduloFinal;
    printf("   Resultado: %d\n", resultado);

    return 0;
}
