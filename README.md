# Campo Lógico-Minado
Projeto de Campo Lógico-Minado formado por Matriz 4x4 de LEDs
Projeto de entretenimento com raciocínio lógico.

##Objetivo:
Acertar o local onde a "mina" se encontra no campo.

##Modo de jogo:
Campo Minado formado por Matriz 4x4 com LEDs, onde é controlada a seleção do LED (um por vez) com controle remoto por smartphone.
Seleção do LED ao colocar a mão em cima do sensor de presença. O LED RGB fornece dicas de onde está a mina, baseada no LED que você selecionou:

- Azul: não está nem na linha, nem na coluna;
- Verde: está na mesma linha ou na mesma coluna;
- Amarelo: está na próxima linha ou na anterior;
- Roxo: está na próxima coluna ou na anterior;
- Vermelho e Branco Piscando: Parabéns! Você acertou a bomba!

Você tem quatro tentativas de seleção, após isso o jogo reinicia.

##Materiais
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


##Conceitos envolvidos:

- LED RGB controlado por PWM
- Comunicação sem fio  - USART
- Timers para funções de comunicação
- Multiplexação da Matriz
- Detecção de estado lógico de pinos

Link para vídeo no Youtube:
https://www.youtube.com/watch?v=IM6cZgWwwik


Projeto originalmente desenvolvido para a disciplina EEL7013 - Laboratório de Transdutores

do curso de Engenharia Eletrônica da Universidade Federal de Santa Catarina (UFSC)

Campus Reitor João David Ferreira Lima, Florianópolis

