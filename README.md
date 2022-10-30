# Trabalho 1 - Redes de Computadores (SSC0641)

## Integrantes

- Felipe de Alcântara Tomé - 11800970 
- Francisco Reis Nogueira - 11954374
- Luiz Henrique Pereira - 11918539
- Maíra de Souza Canal - 11819403
- João Augusto Fernandes Barbosa - 11953348

## Sobre o Trabalho
- **Versões do sistema operacional testadas:** Ubuntu 22.04, Fedora 36
- **Compiladores:** g++ 11 e 12
- **Descrição:**<br>
	O presente trabalho baseia-se na comunicação de diversos clientes através de um server, utilizando a lógica de implementação por Socket.
	Os clientes possuem sockets que recebem identificação dentro do server. A cada envio de mensagem, o servidor é responsável por encaminhas o texto recebido à todos os clientes conectados nele naquele momento.
	A definição do socket seguiu o padrão estrutural explicitado em aula, baseado no protocolo TCP.
	
## Como Executar
### Compilação: 

Comandos do Makefile:

Compilação de todos os arquivos necessários:

```
make all
```

Limpa os arquivos:

```
make clear
```
	
### Execução:
Após o make all, no root do arquivo:

Em um terminal inicia-se o server:
```
./server
```
	
Em outro terminal inicia-se o client:
```
./client
```

### Dependências
- **Debian/Ubuntu:** 

```
sudo apt-get install libgtkmm-3.0-dev
```

- **Fedora:** 

```
sudo dnf install gtkmm30-devel
```
