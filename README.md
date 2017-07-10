# PT_BR
# Campo Lógico-Minado

> "Quem pensa pouco, erra muito" - **Leonardo Da Vinci**


Projeto de Campo Lógico-Minado formado por Matriz 4x4 de LEDs
Projeto de entretenimento com raciocínio lógico.

## Objetivo:
Acertar o local onde a "mina" se encontra no campo.

## Modo de jogo:
Campo Minado formado por Matriz 4x4 com LEDs, onde é controlada a seleção do LED (um por vez) com controle remoto por smartphone.
Seleção do LED ao colocar a mão em cima do sensor de presença infravermelho (com o comparador LM393). O LED RGB fornece dicas de onde está a mina, baseada no LED que você selecionou:

- Azul: não está nem na linha, nem na coluna;
- Verde: está na mesma linha ou na mesma coluna;
- Amarelo: está na próxima linha ou na anterior;
- Roxo: está na próxima coluna ou na anterior;
- Vermelho e Branco Piscando: Parabéns! Você acertou a bomba!

Você tem quatro tentativas de seleção, após isso o jogo reinicia.

## Materiais
- 1x placa de desenvolvimento Arduino
- Jumpers
- 16x LEDs para formar Matriz 4x4
- 1x Sensor de presença infravermelho LM393
- 1x LED RGB
- 3x Resistores de 330R
- 8x Transitores NPN (BC547, BC548, etc.)
- 1x Módulo Bluetooth HC-06 para controle remoto
- Smartphone com Bluetooth
- App Adv BT Terminal


## Conceitos envolvidos:

- LED RGB controlado por PWM (Modulação por Largura de Pulso)
- Comunicação sem fio e Comunicação Serial - USART
- Timers para funções de comunicação
- Multiplexação da Matriz
- Detecção de estado lógico de pinos

Link para vídeo no Youtube:
https://www.youtube.com/watch?v=IM6cZgWwwik


Projeto originalmente desenvolvido para a disciplina EEL7013 - Laboratório de Transdutores do curso de Engenharia Eletrônica da Universidade Federal de Santa Catarina (UFSC) Campus Reitor João David Ferreira Lima, Florianópolis, Santa Catarina, Brasil

# EN_US
# Logic Minesweeper
Logic Minesweeper Project developed for a 4x4 LED Matrix.
Entertainment Project involving logical reasoning.

# Goal:
Identify the place where the "mine" is on the field.

# Gameplay:
Mine/Bomb Field formed by a 4x4 LED Matrix, where the LED selection is controlled (once at a time) with a remote controller, through a smartphone. The LED is selected when putting the hand above the infrared obtacle sensor (with the LM393 comparator). The RGB LED gives tips about where is the mine, based on the LED you have selected:

- Blue: the mine is neither on the line, **nor** in the column;
- Green: the mine is on the same line **or** in the same column;
- Yellow: it is on the next **or** on the previous line;
- Purple: it is on the next **or** on the previous column;
- Red and White blinking: **Congratulations!** You have hit the mine!

You have 4 attempts of selections. After that, the game reboots.

## Materials:

- 1x Arduino development board
- Jumpers
- 16x LEDs for the 4x4 Matrix
- 1x Infrared obstacle sensor (LM393)
- 1x RGB LED
- 3x 330R Resistors
- 8x NPN Transistors (BC547, BC548, etc.)
- 1x Bluetooth Module HC-06 for remote control
- 1x Smartphone with Bluetooth Connection
- App ADV BT Terminal (Play Store)

## Related Concepts:

- RBG LED controlled by PWM (Pulse Width Modulation)
- Wirelles Communication and Serial Communication - USART
- Timers with communication functions
- Matrix Multiplex
- Logic state detection

Youtube Video:
https://www.youtube.com/watch?v=IM6cZgWwwik

Project originally developed for the discipline EEL7013 - Laboratório de Transdutores (Transducers Laboratory) of the Electronic Engineering course from the Federal University of Santa Catarina (UFSC). Campus Reitor João David Ferreira Lima, Florianópolis, Santa Catarina, Brazil.
