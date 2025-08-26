# Nome do compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -g3

# Diretório de saída
OUTDIR = output
OUT = $(OUTDIR)/main.exe

# Lista de arquivos fonte
SRC = main.c arquivos.c clientes.c funcionarios.c automoveis.c

# Regra padrão: compilar tudo
all: $(OUT)

# Como gerar o executável
$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

# Limpar arquivos compilados
clean:
	del /Q $(OUT) 2>nul