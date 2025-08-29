# 🚛 Simulador CAN - FMS Truck

> **Simulador de pacotes CAN baseado em Arduino e MCP2515 para emulação de parâmetros veiculares segundo o padrão FMS Truck (SAE J1939)**

[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=flat&logo=Arduino&logoColor=white)](https://www.arduino.cc/)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![FMS Standard](https://img.shields.io/badge/Standard-SAE%20J1939-green)](https://www.sae.org/standards/content/j1939/)

## 📋 Sobre o Projeto

Este simulador foi desenvolvido para facilitar o desenvolvimento e teste de sistemas embarcados que consomem dados do barramento CAN veicular. Ele emula com precisão os parâmetros de um veículo comercial pesado, seguindo as especificações do padrão **FMS Truck (Fleet Management System)**.

### 🎯 Casos de Uso
- **Desenvolvimento de rastreadores veiculares**
- **Testes de gateways CAN-IoT** 
- **Validação de sistemas telemáticos**
- **Prototipagem de dashboards veiculares**
- **Treinamento em protocolos CAN**

## ⚡ Características Técnicas

- **Protocolo**: CAN 2.0B com identificadores de 29 bits
- **Velocidade**: 250 kbps (padrão FMS)
- **Padrão**: SAE J1939 / FMS Truck
- **Intervalo de envio**: Configurável (padrão: 1000ms)
- **Alimentação**: 5V (Arduino)

## 🔧 Parâmetros Simulados

### 📊 Motor e Transmissão
- **Velocidade do veículo** (0-120 km/h)
- **Rotação do motor** (RPM)
- **Temperatura do motor** (°C)
- **Pressão do óleo** (bar)
- **Nível de combustível** (%)
- **Marcha atual**

### 🚦 Controles e Pedais  
- **Pedal de embreagem** (acionado/liberado)
- **Pedal de freio** (acionado/liberado)
- **Freio de estacionamento**
- **Retarder** (sistema de frenagem auxiliar)
- **Marcha ré**

### 🌐 Localização e Operação
- **Coordenadas GPS** (latitude/longitude)
- **Horímetro** (horas de operação)
- **Hodômetro** (quilometragem total)

## 🛠️ Hardware Necessário

### Componentes Obrigatórios
| Componente | Especificação | Observações |
|------------|---------------|-------------|
| Microcontrolador | Arduino UNO/Nano/Pro Mini | ATmega328P ou superior |
| Módulo CAN | MCP2515 + TJA1050 | Interface SPI |
| Cabos | Jumpers macho-fêmea | Para conexões |

### Componentes Opcionais
- Fonte 12V (para alimentação externa)
- Protoboard ou PCB personalizada
- LEDs indicadores de status
- Display LCD para monitoramento local

## 🔌 Esquema de Ligação

```
Arduino UNO    ←→    MCP2515
    GND        ←→    GND
    5V         ←→    VCC  
    Pin 10     ←→    CS
    Pin 11     ←→    SI (MOSI)
    Pin 12     ←→    SO (MISO)
    Pin 13     ←→    SCK
```

### Diagrama de Conexão
```
┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│   Arduino   │────▶│   MCP2515   │────▶│ Barramento  │
│     UNO     │     │             │     │    CAN      │
└─────────────┘     └─────────────┘     └─────────────┘
```

## 📦 Instalação e Configuração

### 1️⃣ Preparação do Ambiente
```bash
# Clone o repositório
git clone https://github.com/seu-usuario/projeto-simulador-can.git
cd projeto-simulador-can
```

### 2️⃣ Instalação da Biblioteca
1. Abra o Arduino IDE
2. Vá em **Sketch** → **Include Library** → **Manage Libraries**
3. Procure por "mcp_can" e instale a biblioteca oficial
4. Ou instale via link: [MCP_CAN Library](https://github.com/coryjfowler/MCP_CAN_lib)

### 3️⃣ Configuração do Hardware
1. Monte o circuito conforme o esquema de ligação
2. Conecte o Arduino ao computador via USB
3. Selecione a placa e porta corretas no Arduino IDE

### 4️⃣ Upload do Código
1. Abra o arquivo `simulador_can.ino`
2. Ajuste os parâmetros se necessário:
   ```cpp
   #define SEND_INTERVAL 1000  // Intervalo em ms
   #define CAN_SPEED CAN_250KBPS
   ```
3. Compile e faça o upload para o Arduino

## 🖥️ Monitoramento

### Monitor Serial
Ative o monitor serial (115200 baud) para acompanhar os envios:

```
=== SIMULADOR CAN FMS TRUCK ===
Inicializando MCP2515... OK
Configurando velocidade 250kbps... OK

[12:34:56] Dados enviados:
✓ Velocidade: 65 km/h (PGN: 65265)
✓ RPM Motor: 1850 rpm (PGN: 61444)  
✓ Nível Combustível: 75% (PGN: 65276)
✓ Temperatura Motor: 87°C (PGN: 65262)
✓ Coordenadas GPS: -23.5505, -46.6333
✓ Horímetro: 1247.8 horas
✓ Hodômetro: 89,543 km
---
```

## ⚙️ Personalização

### Modificando Parâmetros
Edite as funções no código para ajustar os valores simulados:

```cpp
void sendSpeed() {
  static int speed = 60;  // Velocidade inicial
  speed += random(-5, 6); // Variação aleatória
  speed = constrain(speed, 0, 120);
  // ... código de envio
}
```

### Adicionando Novos Parâmetros
```cpp
void sendNewParameter() {
  // Implemente seu parâmetro personalizado
  // seguindo o padrão SAE J1939
}
```

## 🧪 Testes e Validação

### Verificação com CANbus Analyzer
1. Conecte um analisador CAN ao barramento
2. Configure para 250kbps
3. Verifique se as mensagens seguem o formato esperado

### Testes com Dispositivos Reais
- Conecte rastreadores ou gateways para validação
- Monitore os dados recebidos pelos dispositivos
- Compare com especificações FMS

## 🤝 Contribuições

Contribuições são bem-vindas! Por favor:

1. Faça um fork do projeto
2. Crie uma branch para sua feature (`git checkout -b feature/nova-funcionalidade`)
3. Commit suas mudanças (`git commit -m 'Adiciona nova funcionalidade'`)
4. Push para a branch (`git push origin feature/nova-funcionalidade`)
5. Abra um Pull Request

## 📚 Documentação Adicional

- [SAE J1939 Standard](https://www.sae.org/standards/content/j1939/)
- [FMS Standard Documentation](https://www.aeec.org/)
- [MCP2515 Datasheet](https://www.microchip.com/en-us/product/MCP2515)
- [Arduino CAN Tutorial](https://docs.arduino.cc/)

## 🐛 Solução de Problemas

### Erro: "MCP2515 não encontrado"
- Verifique as conexões SPI
- Confirme se a biblioteca está instalada corretamente

### Mensagens não são enviadas
- Verifique a velocidade do barramento CAN (250kbps)
- Confirme se há terminação adequada no barramento

### Dados inconsistentes
- Verifique se o formato das mensagens está correto
- Valide os PGNs (Parameter Group Numbers) utilizados

## 📄 Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.

## 👨‍💻 Autor

**Samuel Braga**
- GitHub: [@samuelbraga](https://github.com/samuelbraga)
- LinkedIn: [Samuel Braga]([https://linkedin.com/in/samuelbraga](https://www.linkedin.com/in/samuel-braga-b831941b1/))

---

⭐ Se este projeto foi útil para você, considere dar uma estrela no repositório!
