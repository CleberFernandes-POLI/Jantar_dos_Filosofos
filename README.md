# Produtor e consumidor com Zephyr RTOS e PlatformIO

Este projeto simula uma padaria com duas threads de mesma prioridade: um padeiro
produz pães a cada segundo e um cliente consome pães a cada 1,5 segundo. O saldo
da vitrine é compartilhado pelas threads e a capacidade é de 10 pães.

Não são usados semáforos, mutexes ou filas. As verificações de vitrine cheia e
vazia não protegem o acesso concorrente ao contador; assim, o programa serve
para observar os riscos de compartilhar estado sem sincronização.

## Preparar o PlatformIO

1. Instale o Visual Studio Code e a extensão **PlatformIO IDE** (ou instale o
   PlatformIO Core).
2. Abra esta pasta como projeto no PlatformIO. A configuração seleciona
   `freescalekinetis`, Zephyr e `frdm_kl25z`; na primeira compilação, o
   PlatformIO baixará as ferramentas e os pacotes necessários.
3. Conecte a FRDM-KL25Z via USB e instale os drivers da interface de depuração
   CMSIS-DAP, se solicitado pelo sistema operacional.

## Compilar, gravar e visualizar

No terminal integrado, na raiz do projeto:

```sh
pio run
pio run -t upload
pio device monitor
```

Também é possível usar os comandos **Build**, **Upload** e **Monitor** da barra
de ferramentas do PlatformIO no VS Code. O monitor serial está configurado para
115200 baud. As mensagens `PADEIRO` e `CLIENTE` mostram o saldo da vitrine; ao
chegar a 10 pães, o padeiro aguarda espaço, e o cliente não consome quando a
vitrine está vazia.
