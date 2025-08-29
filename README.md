# 🚛 projeto-simulador-can

Simulador de pacotes CAN desenvolvido com **Arduino** e **MCP2515**, focado na emulação de parâmetros veiculares conforme o padrão **FMS Truck** (SAE J1939). Ideal para testes de rastreadores, gateways e dispositivos embarcados que consomem dados via barramento CAN.

## 🔧 Funcionalidades

- Envio periódico de mensagens CAN com dados simulados
- Suporte a múltiplos parâmetros veiculares:
  - Velocidade, RPM, nível de combustível, temperatura do motor, pressão do óleo, etc.
  - Pedais (embreagem, freio), marcha ré, freio de estacionamento, retarder
  - GPS (latitude/longitude), horímetro, hodômetro
- Mensagens com IDs e formatos compatíveis com aplicações FMS

## 🛠️ Hardware necessário

- Arduino UNO, Nano ou similar
- Módulo CAN MCP2515 com transceptor TJA1050
- Fonte de alimentação 12V (opcional)
- Cabos jumper e protoboard (para testes)

## 📦 Estrutura do código

- Cada parâmetro é enviado por uma função dedicada
- Os dados são simulados com pequenas variações para testes realistas
- Intervalo de envio configurável (`SEND_INTERVAL`)
- Comunicação CAN a 250 kbps

## ▶️ Como usar

1. Instale a biblioteca [mcp_can](https://github.comnecte o MCP2515 ao Arduino via SPI:
   - `CS` → pino 10
   - `SO` → pino 12
   - `SI` → pino 11
   - `SCK` → pino 13
3. Compile e envie o código para o Arduino
4. Abra o monitor serial para acompanhar os envios

## 📡 Exemplo de saída no monitor serial

✓ Speed: 62 km/h
✓ RPM: 1795
✓ Fuel Level: 80%
✓ GPS: -23.5504, -46.6332
✓ Hourmeter: 1251.2 h

---

Desenvolvido por Samuel Braga