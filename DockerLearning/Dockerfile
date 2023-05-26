# Usa uma imagem base do Ubuntu
FROM ubuntu:latest

# Atualiza os repositórios do sistema e instala os pacotes necessarios, adicionei g++ e psmics para o comando "g++, killall e etc" funcionarem
RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    vim \
    openssl 

# Cria o diretório "jojowam"
RUN mkdir /jojowam

# Copia apenas os arquivos dentro da pasta "jojowam" para o diretorio "jojowam" do conteiner
COPY jojowam /jojowam/

# Define o diretorio de trabalho padrao como "/"
WORKDIR /

# Executa um comando ou um shell padrao quando o container for iniciado
CMD ["bash"]
