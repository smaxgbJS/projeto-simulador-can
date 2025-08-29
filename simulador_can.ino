#include <SPI.h>
#include <mcp2515.h>

// ===== CONFIGURAÇÕES =====
#define SEND_INTERVAL 2000  // 2 segundos entre envios

// IDs das mensagens CAN com referência aos tipos
// HOURMETER - CAN32BITR0
const uint16_t HOURMETER_ID = 0x100;
// ODOMETER - CAN_B0
const uint16_t ODOMETER_ID = 0x101;
// SPEED - CAN16BITR5
const uint16_t SPEED_ID = 0x102;
// FUEL_TEMPERATURE - CAN8BITR19
const uint16_t FUEL_TEMP_ID = 0x103;
// ENGINE_OIL_TEMPERATURE - CAN16BITR8
const uint16_t ENGINE_OIL_TEMP_ID = 0x104;
// OIL_PRESSURE - CAN8BITR20
const uint16_t OIL_PRESSURE_ID = 0x105;
// CLUTCH_PEDAL - CAN8BITR17
const uint16_t CLUTCH_PEDAL_ID = 0x106;
// BRAKE_PEDAL - CAN8BITR16
const uint16_t BRAKE_PEDAL_ID = 0x107;
// PARKING_BRAKE - CAN8BITR21
const uint16_t PARKING_BRAKE_ID = 0x108;
// BRAKE_RETARDER - CAN8BITR23
const uint16_t BRAKE_RETARDER_ID = 0x109;
// POWER_TAKEOFF - CAN8BITR1
const uint16_t POWER_TAKEOFF_ID = 0x10A;
// REVERSE_GEAR - CAN8BITR0
const uint16_t REVERSE_GEAR_ID = 0x10B;
// GPS - COORDINATES
const uint16_t GPS_ID = 0x10C;
// RPM - CAN_A1
const uint16_t RPM_ID = 0x10D;
// FUEL_LEVEL - CAN_A1
const uint16_t FUEL_LEVEL_ID = 0x10E;
// COOLING_TEMPERATURE - CAN_A1
const uint16_t COOLING_TEMP_ID = 0x10F;

// ===== VARIÁVEIS =====
MCP2515 mcp2515(10);
struct can_frame canMsg;
unsigned long previousMillis = 0;
int dataCounter = 0;

// Valores base para simulação
int baseSpeed = 60;
int baseRPM = 1800;
int baseFuelLevel = 80;
int baseCoolingTemp = 85;
int baseFuelTemp = 40;
int baseEngineOilTemp = 95;
int baseOilPressure = 45;
float baseHourmeter = 1250.5;
float baseOdometer = 125000.0;

// ===== FUNÇÃO PARA ENVIAR MENSAGEM CAN =====
void sendCANMessage(uint16_t canId, uint8_t* data, const char* description) {
    canMsg.can_id = canId;
    canMsg.can_dlc = 8;
    memcpy(canMsg.data, data, 8);
    
    MCP2515::ERROR result = mcp2515.sendMessage(&canMsg);
    
    if (result == MCP2515::ERROR_OK) {
        Serial.print("✓ ");
        Serial.println(description);
    } else {
        Serial.print("✗ Erro ao enviar: ");
        Serial.println(description);
    }
}

// ===== FUNÇÕES DE SIMULAÇÃO SIMPLES =====
void sendHourmeter() {
    uint8_t data[8] = {0};
    float hours = baseHourmeter + (dataCounter * 0.1);
    uint32_t hoursInt = (uint32_t)(hours * 10); // Multiplica por 10 para preservar decimal
    memcpy(data, &hoursInt, 4);
    
    char desc[32];
    char hoursStr[12];
    dtostrf(hours, 6, 1, hoursStr);
    sprintf(desc, "Hourmeter: %s h", hoursStr);
    sendCANMessage(HOURMETER_ID, data, desc);
}

void sendOdometer() {
    uint8_t data[8] = {0};
    uint32_t km = (uint32_t)(baseOdometer + dataCounter);
    memcpy(data, &km, 4);
    
    char desc[32];
    sprintf(desc, "Odometer: %lu km", km);
    sendCANMessage(ODOMETER_ID, data, desc);
}

void sendSpeed() {
    uint8_t data[8] = {0};
    int speed = baseSpeed + random(-5, 6); // 55-65 km/h
    data[0] = speed;
    
    char desc[32];
    sprintf(desc, "Speed: %d km/h", speed);
    sendCANMessage(SPEED_ID, data, desc);
}

void sendFuelTemperature() {
    uint8_t data[8] = {0};
    int temp = baseFuelTemp + random(-2, 3); // 38-42°C
    data[0] = temp;
    
    char desc[32];
    sprintf(desc, "Fuel Temp: %d°C", temp);
    sendCANMessage(FUEL_TEMP_ID, data, desc);
}

void sendEngineOilTemperature() {
    uint8_t data[8] = {0};
    int temp = baseEngineOilTemp + random(-3, 4); // 92-98°C
    data[0] = temp;
    
    char desc[32];
    sprintf(desc, "Oil Temp: %d°C", temp);
    sendCANMessage(ENGINE_OIL_TEMP_ID, data, desc);
}

void sendOilPressure() {
    uint8_t data[8] = {0};
    int pressure = baseOilPressure + random(-2, 3); // 43-47 bar
    data[0] = pressure;
    
    char desc[32];
    sprintf(desc, "Oil Pressure: %d bar", pressure);
    sendCANMessage(OIL_PRESSURE_ID, data, desc);
}

void sendClutchPedal() {
    uint8_t data[8] = {0};
    int position = random(0, 2) ? 0 : 100; // 0% ou 100% (pressionado ou não)
    data[0] = position;
    
    char desc[32];
    sprintf(desc, "Clutch: %d%%", position);
    sendCANMessage(CLUTCH_PEDAL_ID, data, desc);
}

void sendBrakePedal() {
    uint8_t data[8] = {0};
    int position = random(0, 5) == 0 ? random(10, 80) : 0; // Ocasionalmente frenando
    data[0] = position;
    
    char desc[32];
    sprintf(desc, "Brake: %d%%", position);
    sendCANMessage(BRAKE_PEDAL_ID, data, desc);
}

void sendParkingBrake() {
    uint8_t data[8] = {0};
    int status = random(0, 10) == 0 ? 1 : 0; // Raramente acionado
    data[0] = status;
    
    char desc[32];
    sprintf(desc, "Parking Brake: %s", status ? "ON" : "OFF");
    sendCANMessage(PARKING_BRAKE_ID, data, desc);
}

void sendBrakeRetarder() {
    uint8_t data[8] = {0};
    int level = random(0, 4); // 0-3 níveis
    data[0] = level;
    
    char desc[32];
    sprintf(desc, "Brake Retarder: Level %d", level);
    sendCANMessage(BRAKE_RETARDER_ID, data, desc);
}

void sendPowerTakeoff() {
    uint8_t data[8] = {0};
    int status = random(0, 5) == 0 ? 1 : 0; // Ocasionalmente ligado
    data[0] = status;
    
    char desc[32];
    sprintf(desc, "PTO: %s", status ? "ON" : "OFF");
    sendCANMessage(POWER_TAKEOFF_ID, data, desc);
}

void sendReverseGear() {
    uint8_t data[8] = {0};
    int status = random(0, 20) == 0 ? 1 : 0; // Raramente em ré
    data[0] = status;
    
    char desc[32];
    sprintf(desc, "Reverse: %s", status ? "ON" : "OFF");
    sendCANMessage(REVERSE_GEAR_ID, data, desc);
}

void sendGPS() {
    uint8_t data[8] = {0};
    // Coordenadas de São Paulo com pequena variação
    float lat = -23.5505 + (dataCounter * 0.0001);
    float lon = -46.6333 + (dataCounter * 0.0001);
    
    memcpy(&data[0], &lat, 4);
    memcpy(&data[4], &lon, 4);
    
    char desc[48];
    dtostrf(lat, 8, 4, desc);
    strcat(desc, ", ");
    char lonStr[12];
    dtostrf(lon, 9, 4, lonStr);
    strcat(desc, lonStr);
    
    char finalDesc[64];
    sprintf(finalDesc, "GPS: %s", desc);
    sendCANMessage(GPS_ID, data, finalDesc);
}

void sendRPM() {
    uint8_t data[8] = {0};
    int rpm = baseRPM + random(-50, 51); // 1750-1850 RPM
    uint16_t rpmData = rpm;
    memcpy(data, &rpmData, 2);
    
    char desc[32];
    sprintf(desc, "RPM: %d", rpm);
    sendCANMessage(RPM_ID, data, desc);
}

void sendFuelLevel() {
    uint8_t data[8] = {0};
    int fuel = baseFuelLevel + random(-1, 2); // 79-81%
    data[0] = fuel;
    
    char desc[32];
    sprintf(desc, "Fuel Level: %d%%", fuel);
    sendCANMessage(FUEL_LEVEL_ID, data, desc);
}

void sendCoolingTemperature() {
    uint8_t data[8] = {0};
    int temp = baseCoolingTemp + random(-2, 3); // 83-87°C
    data[0] = temp;
    
    char desc[32];
    sprintf(desc, "Cooling Temp: %d°C", temp);
    sendCANMessage(COOLING_TEMP_ID, data, desc);
}

// ===== SETUP E LOOP =====
void setup() {
    Serial.begin(9600);
    delay(1000);
    
    Serial.println("=== SIMULADOR CAN SIMPLES ===");
    
    // Inicializa MCP2515
    if (mcp2515.reset() == MCP2515::ERROR_OK) {
        Serial.println("MCP2515 resetado");
    }
    
    if (mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ) == MCP2515::ERROR_OK) {
        Serial.println("Bitrate configurado: 250kbps");
    }
    
    if (mcp2515.setNormalMode() == MCP2515::ERROR_OK) {
        Serial.println("Modo normal ativo");
        Serial.println("Iniciando transmissões...\n");
    }
}

void loop() {
    if (millis() - previousMillis >= SEND_INTERVAL) {
        previousMillis = millis();
        
        Serial.print("--- Ciclo ");
        Serial.print(dataCounter + 1);
        Serial.println(" ---");
        
        // Envia todas as mensagens
        sendHourmeter();
        delay(50);
        sendOdometer();
        delay(50);
        sendSpeed();
        delay(50);
        sendFuelTemperature();
        delay(50);
        sendEngineOilTemperature();
        delay(50);
        sendOilPressure();
        delay(50);
        sendClutchPedal();
        delay(50);
        sendBrakePedal();
        delay(50);
        sendParkingBrake();
        delay(50);
        sendBrakeRetarder();
        delay(50);
        sendPowerTakeoff();
        delay(50);
        sendReverseGear();
        delay(50);
        sendGPS();
        delay(50);
        sendRPM();
        delay(50);
        sendFuelLevel();
        delay(50);
        sendCoolingTemperature();
        
        Serial.println();
        dataCounter++;
    }
}