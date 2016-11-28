/*
 * UNIVERSIDADE FEDERAL DE SANTA CATARINA (UFSC)
 * CAMPUS FLORIANOPOLIS
 * ENGENHARIA ELETRONICA 2016/2
 * LABORATORIO DE TRANSDUTORES
 *
 * CAMPO MINADO COM LEDS
 *
 * ProjetoTRANSDUTORES.c
 *
 * Created: 28/08/2016 17:38:17
 * Author : Gustavo Simas e Rafael Augusto
 *
 */ 

//DEFINICAO DE CLOCK
#define F_CPU 16000000UL

//INCLUSAO DE BIBLIOTECAS
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "ls_atmega328.h"
#include "ls_defines.h"
#include "ls_hd44780.h"

//DEFINICOES DE PINOS
#define RED PD3
#define GREEN PD5
#define BLUE PD6

#define COL_1 PD2
#define COL_2 PD4
#define COL_3 PD7
#define COL_4 PB0

#define LIN_1 PB1
#define LIN_2 PB2
#define LIN_3 PB3
#define LIN_4 PB4

//DEFINICAO DE FUNCOES
ISR(TIMER0_COMPA_vect);
ISR(TIMER0_COMPB_vect);
ISR(TIMER2_COMPB_vect);

void Inicio();
void Voce_ganhou();
void White_color();
void Red_color();
void Blue_color();
void Yellow_color();
void Orange_color();
void Purple_color();
void Green_color();
void Right();
void Left();
void Clear_tabela();
void Clear_All();
void Usart_Receive();
void Verifica_bombas();
void Verifica_leds();
void Psicodelia();

volatile char tabela_leds[4][4];
volatile char estado;
volatile char recebe = 'x';
volatile int i,j;
volatile int select[2];
volatile int num_bombs = 30;
volatile int bombs[2];
volatile int count = 0;
volatile int ganhou = 0;


//MAIN///////////////////////////////////////
int main(void)
{
	bombs[0] = 5;
	bombs[1] = 5;
	//CONFIGURACOES INICIAIS
	//PORT (pull-up) e DDR (endereço - entrada/saida)
    PORTC = 0x00;
	DDRC = 0b111100;
	
	PORTB = 0x00;
	DDRB = 0xFF;
	
	PORTD = 0x00;
	DDRD = 0b01111110;
	 
	//USART - MODULO BLUETOOTH
	usartEnableTransmitter();
	usartEnableReceiver();
	
	usartStdio();
	usartInit(9600);
	
	//TIMERS
	timer0ClockPrescaller1024();
	timer0FastPWMMaxMode();
	timer0OC0ANonInvertedMode();
	timer0OC0BNonInvertedMode();
	OCR0A = 200;
	OCR0B = 20;
	
	
	timer2ClockPrescaller1024();
	timer2FastPWMMaxMode();
	timer2OC2BNonInvertedMode();
	OCR2B = 10;
	
	//HABILITAR INTERRUPCOES
	sei();
	
	//FIM DE CONFIGURACOES INICIAIS
	
	//DEFINICOES DE VARIAVEIS
	i = 0;
	j = 1;
	
	
    while (1) 
    {
			
		
		if(count == 0)
		Inicio();
		
		if(count > 0){
		
		Verifica_leds();
		
		
		if(isBitClr(PINC,PC0))
		{
			_delay_ms(1);
			if(isBitSet(PINC,PC0))
			Right();
		}
		
		
		Usart_Receive();
				
		
		Verifica_bombas();
		
		Voce_ganhou();
		
		if(count == 5 && ganhou != 1)
		{
			
			printf("Voce atingiu o limite");
			printf("Linha: %d\r",bombs[0]+1);
			printf("Coluna: %d\r",bombs[1]+1);
			_delay_ms(1000);
			count = 0;
			j = 1;
			i = 0;
			
		}
		
		}
    }
	
	
}

//FIM DA MAIN ////////////////////////////////


//FUNCOES
ISR(TIMER0_COMPA_vect){

	
}

ISR(TIMER0_COMPB_vect){

	
}

ISR(TIMER2_COMPB_vect){

	
}

void Inicio(){
	
	while(isBitClr(PINC,PC0))
	{
		
		Psicodelia();
		
		do{bombs[0] = rand() % 10;}while(bombs[0] > 3);
		
		do{bombs[1] = rand() % 10;}while(bombs[1] > 3);
		
		_delay_us(10);
	}
	
	Clear_tabela();
	count = 1;
	printf("Mah oe, bem vindo ao campo minado do dr Cimass Croata.   Utiliza w,a,s,d para movimentar o cursor, o sensor para selecionar.   Azul= nao esta na mesma linha ou coluna;   Roxo: esta coluna anterior ou proxima;   Amarelo: esta na linha anterior ou proxima;   Verde: ou na mesma linha ou na mesma coluna.");
	
}

void Voce_ganhou(){
	
	
	while(ganhou == 1){
		
		Red_color();
		_delay_ms(200);
		
		White_color();
		_delay_ms(200);
		
		Usart_Receive();
		
	}
}

void White_color(){
	OCR0A = 255;
	OCR0B = 255;
	OCR2B = 255;
}

//Cor Vermelha
void Red_color(){
	OCR0A = 0;
	OCR0B = 0;
	OCR2B = 255;
}

//Cor azul
void Blue_color(){
	OCR0A = 255;
	OCR0B = 0;
	OCR2B = 0;
}

//Cor amarela
void Yellow_color(){
	OCR0A = 0;
	OCR0B = 50;
	OCR2B = 255;
}

void Green_color(){
	OCR0A = 0;
	OCR0B = 255;
	OCR2B = 0;
}

void Purple_color(){
	OCR0A = 127;
	OCR0B = 0;
	OCR2B = 255;
}

//Cor Laranja
void Orange_color(){
	OCR0A = 0;
	OCR0B = 10;
	OCR2B = 205;
}

void Left(){
	
	Clear_tabela();
		
	select[1]--;
	
	if(select[1] == -1)
	{
		select[1] = 3;
		select[0]--;
		
		if(select[0] == -1)
		select[0] = 3;
	}
	
	tabela_leds[select[0]][select[1]] = 1;
	
	
	_delay_ms(1);
}

//Selecionar proximo led
void Right(){
	
	Clear_tabela();
		
	select[1]++;
	
	if(select[1] == 4)
	{
		select[1] = 0;
		select[0]++;
		
		if(select[0] == 4)
		select[0] = 0;
	}
	
	tabela_leds[select[0]][select[1]] = 1;
	
	
	_delay_ms(1);
}

void Up(){
	
	Clear_tabela();
	
	select[0]++;
	
	if(select[0] == 4)
	{
		select[0] = 0;
	
	}
	
	tabela_leds[select[0]][select[1]] = 1;
	
	
	_delay_ms(1);
}

void Down(){
	
	Clear_tabela();
	
	select[0]--;
	
	if(select[0] == -1)
	{
		select[0] = 3;
	}
	
	tabela_leds[select[0]][select[1]] = 1;
	
	
	_delay_ms(1);
}

//Função para receber dados de Bluetooth
void Usart_Receive()
{	
	if(usartIsReceptionComplete())
	{
		recebe = usartReceive();
		
		printf("Recebido: %c", recebe);
		
	}
	
	if(ganhou == 1 && recebe == 's'){
	
	Clear_tabela();
	Clear_All();
	tabela_leds[0][0] = 1;
	Verifica_leds();
	ganhou = 0;
	count = 0;
	j = 1;
	i = 0;
	recebe = 'x';
	
	}
	
	if(recebe == 'd')
	{
		_delay_ms(1);
		Right();
		recebe ='x';
		
	}
	
	if(recebe == 'a')
	{
		_delay_ms(1);
		Left();
		recebe ='x';
		
	}
	
	if(recebe == 's')
	{
		_delay_ms(1);
		Up();
		recebe ='x';
		
	}
	
	if(recebe == 'w')
	{
		_delay_ms(1);
		Down();
		recebe ='x';
		
	}
		
}

//Limpar Tabela
void Clear_tabela(){
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			tabela_leds[i][j] = 0;
		}
	}
	
}

//Limpar todos leds
void Clear_All(){
	clrBit(PORTD, COL_1);
	clrBit(PORTD, COL_2);
	clrBit(PORTD, COL_3);
	clrBit(PORTB, COL_4);
	clrBit(PORTB, LIN_1);
	clrBit(PORTB, LIN_2);
	clrBit(PORTB, LIN_3);
	clrBit(PORTB, LIN_4);
}

void Psicodelia(){
	
	switch(j){
		
		case 1:
		tabela_leds[0][0]=1;
		tabela_leds[0][1]=1;
		tabela_leds[0][2]=1;
		tabela_leds[0][3]=1;
		tabela_leds[1][0]=1;
		tabela_leds[1][1]=1;
		tabela_leds[1][2]=1;
		tabela_leds[1][3]=1;
		tabela_leds[2][0]=1;
		tabela_leds[2][1]=1;
		tabela_leds[2][2]=1;
		tabela_leds[2][3]=1;
		tabela_leds[3][0]=1;
		tabela_leds[3][1]=1;
		tabela_leds[3][2]=1;
		tabela_leds[3][3]=1;
		j=2;
		_delay_ms(5);
		Verifica_leds();
		break;
		
		case 2:
		tabela_leds[0][0]=0;
		tabela_leds[0][1]=0;
		tabela_leds[0][2]=0;
		tabela_leds[0][3]=0;
		tabela_leds[1][0]=0;
		tabela_leds[1][1]=0;
		tabela_leds[1][2]=0;
		tabela_leds[1][3]=0;
		tabela_leds[2][0]=0;
		tabela_leds[2][1]=0;
		tabela_leds[2][2]=0;
		tabela_leds[2][3]=0;
		tabela_leds[3][0]=0;
		tabela_leds[3][1]=0;
		tabela_leds[3][2]=0;
		tabela_leds[3][3]=0;
		j=1;
		_delay_ms(5);
		Verifica_leds();
		break;
		
	}
	
	switch (i){
		
		case 0:
		Green_color();
		i = 1;
		_delay_us(10);
		break;
		
		case 1:
		Purple_color();
		i = 2;
		_delay_us(10);
		break;
		
		case 2:
		Red_color();
		i = 3;
		_delay_us(10);
		break;
		
		case 3:
		Yellow_color();
		i = 4;
		_delay_us(10);
		break;
		
		case 4:
		Blue_color();
		i = 0;
		_delay_us(10);
		break;
		
	}
}

void Verifica_bombas(){
	
	if(isBitClr(PINC, PC1))
	{
		
		_delay_ms(1);
		if(isBitSet(PINC, PC1))
		{
			
	
	//Para verificar se a bomba esta sendo selecionada
	if(bombs[0] == select[0] && bombs[1] && select[1])
	{
		
		printf("Voce acertou a bomba!");
		ganhou = 1;
		Red_color();
		printf("Mande 's' para reiniciar");
		
	}
	
	if(ganhou != 1){
	if((bombs[0] == select[0] && bombs[1] != select[1]) || (bombs[1] == select[1] && bombs[0] != select[0]))
	Green_color();
	
	else if(bombs[1] == select[1] || bombs[1] == select[1]+1)
	Purple_color();
	
	else if(bombs[0] == select[0] || bombs[0] == select[0]+1)
	Yellow_color();
	
	else if(bombs[1] != select[1] || bombs[1] != select[1]+1 || bombs[0] != select[0] || bombs[0] != select[0]+1)
	Blue_color();
	
	count++;
	printf("Tentativas restantes: %d", 5-count);
	}
		}
	}
}

void Verifica_leds(){
		
	switch (estado){
	
	
	case 0:
	Clear_All();
	if(tabela_leds[0][0] == 1)
	{
		setBit(PORTD, COL_1);
		setBit(PORTB, LIN_1);
		_delay_ms(1);
	}
	estado = 1;
	break;
	
	
	case 1:
	Clear_All();
	if(tabela_leds[0][1] == 1)
	{
		setBit(PORTD, COL_2);
		setBit(PORTB, LIN_1);
		_delay_ms(1);
	}
	estado = 2;
	break;
	
	
	case 2:
	Clear_All();
	if(tabela_leds[0][2] == 1)
	{
		setBit(PORTD, COL_3);
		setBit(PORTB, LIN_1);
		_delay_ms(1);
	}
	estado = 3;
	break;
	
	
	case 3:
	Clear_All();
	if(tabela_leds[0][3] == 1)
	{
		setBit(PORTB, COL_4);
		setBit(PORTB, LIN_1);
		_delay_ms(1);
	}
	estado = 4;
	break;
	
	
	case 4:
	Clear_All();
	if(tabela_leds[1][0] == 1)
	{
		setBit(PORTD, COL_1);
		setBit(PORTB, LIN_2);
		_delay_ms(1);
	}
	estado = 5;
	break;
	
	
	case 5:
	Clear_All();
	if(tabela_leds[1][1] == 1)
	{
		setBit(PORTD, COL_2);
		setBit(PORTB, LIN_2);
		_delay_ms(1);
	}
	estado = 6;
	break;
	
	case 6:
	Clear_All();
	if(tabela_leds[1][2] == 1)
	{
		setBit(PORTD, COL_3);
		setBit(PORTB, LIN_2);
		_delay_ms(1);
	}
	estado = 7;
	break;
	
	case 7:
	Clear_All();
	if(tabela_leds[1][3] == 1)
	{
		setBit(PORTB, COL_4);
		setBit(PORTB, LIN_2);
		_delay_ms(1);
	}
	estado = 8;
	break;
	
	case 8:
	Clear_All();
	if(tabela_leds[2][0] == 1)
	{
		setBit(PORTD, COL_1);
		setBit(PORTB, LIN_3);
		_delay_ms(1);
	}
	estado = 9;
	break;
	
	case 9:
	Clear_All();
	if(tabela_leds[2][1] == 1)
	{
		setBit(PORTD, COL_2);
		setBit(PORTB, LIN_3);
		_delay_ms(1);
	}
	estado = 10;
	break;
	
	case 10:
	Clear_All();
	if(tabela_leds[2][2] == 1)
	{
		setBit(PORTD, COL_3);
		setBit(PORTB, LIN_3);
		_delay_ms(1);
	}
	estado = 11;
	break;
	
	case 11:
	Clear_All();
	if(tabela_leds[2][3] == 1)
	{
		setBit(PORTB, COL_4);
		setBit(PORTB, LIN_3);
		_delay_ms(1);
	}
	estado = 12;
	break;
	
	case 12:
	Clear_All();
	if(tabela_leds[3][0] == 1)
	{
		setBit(PORTD, COL_1);
		setBit(PORTB, LIN_4);
		_delay_ms(1);
	}
	estado = 13;
	break;
	
	case 13:
	Clear_All();
	if(tabela_leds[3][1] == 1)
	{
		setBit(PORTD, COL_2);
		setBit(PORTB, LIN_4);
		_delay_ms(1);
	}
	estado = 14;
	break;
	
	case 14:
	Clear_All();
	if(tabela_leds[3][2] == 1)
	{
		setBit(PORTD, COL_3);
		setBit(PORTB, LIN_4);
		_delay_ms(1);
	}
	estado = 15;
	break;
	
	case 15:
	Clear_All();
	if(tabela_leds[3][3] == 1)
	{
		setBit(PORTB, COL_4);
		setBit(PORTB, LIN_4);
		_delay_ms(1);
	}
	estado = 0;
	break;
	
	}
}