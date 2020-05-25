# Bluetooth low energy sample

Este projeto é uma demonstração de firmware com capacidade BLE. Nessa demo 
um serviço similar a uma UART, isto é, com pontos de escrita e leitura de 
dados, é criado e registrado na stack BT.

Quando o host se conecta ao device, ele pode enviar bytes pela caracteristica
de TX que possui o uuid: <b>00214367-8901-ffff-ffff-ffffffffffff</b>, o device
está configurado como echo, ou seja, na presença de dados, ele os envia de 
volta ao host que os recebe na caracteristica de RX que possui o uuid:
<b>00214367-8902-ffff-ffff-ffffffffffff</b>.

## Preparando o projeto:

* Assumindo que o host esteja com os requisitos do zephyr e west ja instalados: https://docs.zephyrproject.org/latest/getting_started/index.html, prepare o projeto após clonar esse repositório com os comandos a seguir. Alternativamente o terminal do VSCode pode ser 
utilizado (já que ela sera nossa IDE alvo): 

```
cd <este repositorio onde foi clonado>
west init 
west update
west zephyr-export
```
* Os comandos acima podem levar um tempo para executar. <b>Nota</b>: Os testes foram feitos usando o zephyr default do west juntamente
numa máquina com instalação Ubuntu 20.04, pequenos ajustes podem ser necessários para outras distribuições *Nix. Adaptaçõoes dos 
comandos a seguir são necessárias caso o host seja Windows.

* Abra esse projeto no VSCode, habilite o terminal interno pressionando: <b>CTRL+SHIFT+'</b>, e ajuste o ambiente do zephyr, isso é
necessário apenas quando voce abre esse terminal, ou seja só sera necessário refazer esse passo se fechares o VSCode:

```
source setup.sh
``` 

## Para realizar o build:

Com o projeto preparado, podemos compilar a firmware, para isso. siga os passos abaixo:

* Com o terminal aberto crie o diretório build:
```
mkdir build 
cd build
```

* Dentro desse diretório, prepare o cmake do zephyr usando o comando abaixo:
```
cmake -GNinja -DBOARD=nrf52dk_nrf52832  ..
``` 

* Agora podemos configurar o projeto para habilitar o bluetooth e o console RTT:
```
ninja menuconfig
``` 

* Opcionalmente voce pode copiar os conteudos do arquivo: <b>zephyr_ble_sample_config</b>, e
colar dentro do arquivo: <b>build/zephyr/.config</b>

* Compile o firmware:
```
ninja 
```

* O arquivo estará disponível no diretório <b>build/zephyr/</b> com o o nome <b>zephyr</b> em 
três formatos: .elf, .hex, .bin .

## Conectado um debugger no VSCode

Esse repositório já contém um arquivo de configuração para o Jlink no VSCode, permitindo que o
debug no hardware alvo seja possível. Para isso basta instalar a extensao Cortex-M Debug  do
VSCode veja o link a seguir: https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug .

Além disso, sua máquina necessita ter os pacotes de ferramentas da Segger instalados, eles podem ser
encontrados aqui (Lembre-se! JLink sempre original!) : https://www.segger.com/downloads/jlink/

Com esse ferramental instalado, agora siga os passos abaixos para abrir uma seção de debug:
* Realize o processo de build descrito anteriormente, sempre que atualizar seu firmware;
* No VSCode, fora do terminal, pressione F5, uma seção de debug irá iniciar e permitir o debug.

## Suporte;

Este projeto é uma demonstração e não tem pretensão de servir como referência para produção, 
em todo caso se estiver com alguma dificuldade, deixe um star, e me mande um email:
ryukokki.felipe@gmail.com







