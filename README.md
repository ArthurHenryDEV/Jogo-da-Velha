# 🕹️ Jogo da Velha em C (3x3 e 4x4)
Este repositório contém uma implementação completa do **Jogo da Velha (Tic-Tac-Toe)** em **C**, incluindo tabuleiros **3x3** e **4x4**, modos de jogo variados e um sistema de ranking persistente.

---

## 🚀 Funcionalidades
* **👤 Jogador vs Jogador (JxJ)**
* **🤖 Jogador vs Computador (IA aleatória)**
* **🧩 Dois tamanhos de tabuleiro: 3x3 e 4x4**
* **🧠 Detecção automática de vitória:**
    * Linhas
    * Colunas
    * Diagonal principal
    * Diagonal secundária
* **🥇 Sistema de ranking com persistência em arquivo**
* **🖥️ Interface no terminal, compatível com:**
    * Windows (`cls`, `Sleep`)
    * Linux/Mac (`clear`, `sleep`)

---

## 📂 Estrutura do Projeto
```bash
JogoDaVelha/
├── main.c # Código-fonte principal
├── ranking.txt # Arquivo gerado automaticamente
└── README.md # Documentação
```
---

## 🛠️ Como Compilar

Linux/Mac
```bash
gcc main.c -o jogo
./jogo
```
Windows (PowerShell ou CMD)
```bash
gcc main.c -o jogo.exe
jogo.exe
```
## 🎮 Como Jogar
Ao iniciar o programa, o menu principal é exibido:
```
===== JOGO DA VELHA =====
1 - JOG x JOG
2 - JOG x COM
3 - RANKING
4 - CREDITOS
0 - Sair
## Inserindo jogadas
```
As jogadas são informadas usando:
```
linha coluna
```
Exemplo:
```
1 2
```
O jogo valida automaticamente se a posição existe e se está vazia.

---

## 🧠 Modo Computador (IA)
A IA utiliza um sistema simples de jogadas aleatórias válidas. Ela funciona para ambos os modos:

* Tabuleiro 3x3
* Tabuleiro 4x4

---

## 🏆 Ranking

* As vitórias dos jogadores são registradas em ranking.txt
* Jogadores com o mesmo nome têm suas vitórias somadas
* O ranking pode ser visualizado diretamente no menu

---

## 👨‍💻 Créditos

Jogo da Velha:

* Arthur Henry Dias Paiva
* Guilherme Marques Andrade Mororó
  
Sistema de Ranking:

* Abraao Henrique Franco de Araújo
* Enzo Morais Lucena
  
Menu e Documentação:

* Lucas Barbosa Holanda

---

## 📜 Licença

Este projeto é aberto e pode ser utilizado para fins acadêmicos ou pessoais.
