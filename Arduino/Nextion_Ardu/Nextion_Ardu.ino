
// --- Biblioteca Auxiliar ---
#include  "Nextion.h"   //biblioteca Nextion de ITEADLIB_Arduino_Nextion

// --- Mapeamento de Hardware ---
#define    pot    A0
#define    led    LED_BUILTIN
#define    buz    9
#define    bot    7

// --- Declaração de Objetos ---
                     //page id:0, id componente:1, nome do componente: "bt0"
NexDSButton bt_led = NexDSButton(1, 2, "bt_led");

NexProgressBar bar_pot = NexProgressBar(4, 2, "bar_pot"); 
NexNumber val_pot = NexNumber(4, 4, "val_pot");
NexWaveform graf_pot = NexWaveform(4, 5, "graf_pot");

NexPicture img_luz = NexPicture(2, 3, "img_luz");

NexNumber num_ana = NexNumber(3, 4, "num_ana");

// --- Variáveis Globais ---
int     pot_valor = 0,    //valor ad do potenciômetro
        bar_valor = 0,    //valor da barra de progresso
        ana_valor = 0,    //valor analógico para aplicar no buzzer
        lei_botao = 0,    //leitura do botão físico
        graf_valor = 0;

char    txt1[4];         //texto para conversão e exibição

uint32_t ds_var,          //armazena o estado do botão nextion
         num_var;         //armazena o valor analógico do slider no nextion

// --- Configurações Iniciais ---
void setup()
{
    nexInit();  //inicializa o tft

    pinMode(led, OUTPUT);
    pinMode(buz, OUTPUT);
    pinMode(bot, INPUT_PULLUP);

    digitalWrite(led, LOW);
    digitalWrite(buz, LOW);
}

// --- Loop Infinito ---
void loop()
{

    // Leitura de um potenciômetro, exibido em n° e barra
    pot_valor = analogRead(pot);
    //Normaliza a barra animada de acordo com o valor do pot
    bar_valor = map(pot_valor, 0, 1023, 0, 100);
    // seta os valores para o número e barra no nextion
    bar_pot.setValue(bar_valor);
    delay(2);

    val_pot.setValue(pot_valor);
    delay(2); // tempo para não bugar

    graf_valor = map(pot_valor, 0, 1023, 0, 255);
    graf_pot.addValue(0, graf_valor); //n° do canal de comunicação, valor
    delay(2);

    // LED BUILTIN controlado pelo touch
    bt_led.getValue(&ds_var); // conseguir valor do botão nextion
    if(ds_var == 1) { // comparar para a lógica no arduino
        digitalWrite(led, HIGH);
    } else {
        digitalWrite(led, LOW);
    }
    delay(2);

    // Botões de seleção de valor analógico
    num_ana.getValue(&num_var); // conseguir valor do número analógico
    ana_valor = map(num_var, 0, 100, 0, 1023); // converter e aplicar
    analogWrite(buz, ana_valor);
    delay(2);

    // Verificação do estado do botão
    if (pot_valor > 800) {
    lei_botao = 1;
    } else {
    lei_botao = 0;
    }
    //lei_botao = !digitalRead(bot); //leitura do botão arduino
    if(lei_botao == HIGH){ // comparar para a lógica no nextion
        img_luz.setPic(3); // aplicar uma imagem ou outra
    } else {
        img_luz.setPic(4);
    }
    delay(2);
  
}
