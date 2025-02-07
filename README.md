﻿# sem-foro-no-raspberry

 Este código foi desenvolvido para ser executado em um Raspberry Pi Pico e controla três LEDs (verde, azul e vermelho) que acendem em sequência a cada 3 segundos. Abaixo está uma explicação detalhada de como o código funciona:

1. Inicialização e Definições
O código começa incluindo as bibliotecas necessárias para controlar o hardware do Raspberry Pi Pico, como pico/stdlib.h, hardware/timer.h, e hardware/gpio.h.

São definidos os pinos GPIO para cada LED:


const uint LED_G = 11; // LED no GPIO 11
const uint LED_B = 12; // LED no GPIO 12
const uint LED_R = 13; // LED no GPIO 13
Duas variáveis globais são declaradas:

static int state = 1; // Estado inicial (0: LED_G, 1: LED_B, 2: LED_R)
static int count = 1; // Contador para controle adicional, para inciar com o led vermelho aceso

2. Função repeating_timer_callback
Esta função é chamada a cada 3 segundos por um timer repetitivo.

Dependendo do valor da variável state, um dos LEDs é aceso enquanto os outros são apagados:

if (state == 0) {
    gpio_put(LED_G, 1); // Acende o LED Verde
    gpio_put(LED_R, 0); // Apaga o LED Vermelho
    gpio_put(LED_B, 0); // Apaga o LED Azul
} else if (state == 1) {
    gpio_put(LED_G, 0); // Apaga o LED Verde
    gpio_put(LED_R, 0); // Apaga o LED Vermelho
    gpio_put(LED_B, 1); // Acende o LED Azul
} else if (state == 2) {
    gpio_put(LED_G, 0); // Apaga o LED Verde
    gpio_put(LED_R, 1); // Acende o LED Vermelho
    gpio_put(LED_B, 0); // Apaga o LED Azul
}
Após acender o LED correspondente, o estado é atualizado para o próximo LED na sequência:

state = (state + 1) % 3; // Avança para o próximo estado (0, 1, 2)
count++; // Incrementa o contador
A função retorna true para indicar que o timer deve continuar repetindo.

3. Função main
A função main é o ponto de entrada do programa.

Inicializa a comunicação serial e os pinos GPIO como saídas:

stdio_init_all(); // Inicializa a comunicação serial
gpio_init(LED_R); // Inicializa o pino do LED Vermelho
gpio_set_dir(LED_R, GPIO_OUT); // Configura o pino como saída
gpio_init(LED_G); // Inicializa o pino do LED Verde
gpio_set_dir(LED_G, GPIO_OUT); // Configura o pino como saída
gpio_init(LED_B); // Inicializa o pino do LED Azul
gpio_set_dir(LED_B, GPIO_OUT); // Configura o pino como saída
Todos os LEDs são inicialmente apagados:

gpio_put(LED_G, 0); // Apaga o LED Verde
gpio_put(LED_B, 0); // Apaga o LED Azul
gpio_put(LED_R, 0); // Apaga o LED Vermelho
Um timer repetitivo é configurado para chamar a função repeating_timer_callback a cada 3 segundos:


struct repeating_timer timer;
add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);
O programa entra em um loop infinito (while (true)), onde:

O LED Verde é aceso inicialmente (se count == 1).

A mensagem "go" é impressa no console a cada segundo:


if(count == 1){
    gpio_put(LED_G, 1); // Acende o LED 
}
printf("go\n"); // Imprime "go" no console
sleep_ms(1000); // Espera 1 segundo
