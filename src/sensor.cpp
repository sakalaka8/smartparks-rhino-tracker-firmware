#include "sensor.h"

//#define debug
//#define serial_debug  Serial

TimerMillis sensor_timer;

sensorPacket_t sensor_packet;
boolean sensor_send_flag = false;

boolean gps_periodic = false;
boolean gps_triggered = false;
boolean gps_hot_fix = false;
boolean accelerometer_enabled = false;
boolean light_enabled = false;
boolean temperature_enabled = false;
boolean humidity_enabled = false;
boolean pressure_enabled = false;

/**
 * @brief called with a timer to perform sensor readign periodically
 * 
 */
void sensor_timer_callback(void)
{
  #ifdef debug
    serial_debug.println("sensor_timer_callback()");
  #endif
  sensor_send_flag = true;
}

/**
 * @brief load system functions form settings to variables
 * 
 */
void sensor_system_functions_load(void){
  // Initialize sensors to low-power mode
  /* system_functions - enable/disable certain features
  *    bit 0 - gps periodic enabled
  *    bit 1 - gps triggered enabled
  *    bit 2 - gps cold fix = 0 / hot fix = 1
  *    bit 3 - accelerometer enabled
  *    bit 4 - light sensor enabled
  *    bit 5 - temperature sensor enabled
  *    bit 6 - humidity sensor enabled
  *    bit 7 - pressure sensor enabled
  */
  uint8_t system_functions = settings_packet.data.system_functions;
  gps_periodic=bitRead(system_functions,0);
  gps_triggered=bitRead(system_functions,1);
  gps_hot_fix=bitRead(system_functions,2);
  accelerometer_enabled=bitRead(system_functions,3);
  light_enabled=bitRead(system_functions,4);
  temperature_enabled=bitRead(system_functions,5);
  humidity_enabled=bitRead(system_functions,6);
  pressure_enabled=bitRead(system_functions,7);
}

void sensor_gps_init(){
  // GPS
  // Check if GPS is enabled, then set it up accordingly
  if((gps_periodic==true)|(gps_triggered==true)){
    //initialize gps
    if(true){
      // GPS periodic error
      bitSet(status_packet.data.system_functions_errors,0);
      // GPS triggered error
      bitSet(status_packet.data.system_functions_errors,1);
      return;
    }
    if(gps_hot_fix==true){
      // enable backup power pin
    }
  }
  else{
    // disable GPS completely
    // disable power
    // disable backup
  }
}
/**
 * @brief initialize sensors upon boot or new settings
 * 
 * @details Make sure each sensors is firstlu properly reset and put into sleep and then if enabled in settings, initialize it
 * 
 */
void sensor_init(void){
  sensor_timer.stop();
  sensor_timer.start(sensor_timer_callback, 0, settings_packet.data.sensor_interval*60*1000);

  #ifdef debug
    serial_debug.print("sensor_init - sensor_timer_callback( ");
    serial_debug.print("interval: ");
    serial_debug.print(settings_packet.data.sensor_interval);
    serial_debug.println(" )");
  #endif

  sensor_system_functions_load();



  // Accelerometer
  if(accelerometer_enabled==true){
    // check if present
    // configure 
  }
  else{
    // put into low power
  }

  // Light sensor
  if(light_enabled==true){
    // check if present
    // configure 
  }
  else{
    // put into low power
  }

  // Temperature sensor
  if(temperature_enabled==true){
    // check if present
    // configure 
  }
  else{
    // put into low power
  }

  // Humidity sensor
  if(humidity_enabled==true){
    // check if present
    // configure 
  }
  else{
    // put into low power
  }

  // Pressure sensor
  if(pressure_enabled==true){
    // check if present
    // configure 
  }
  else{
    // put into low power
  }


  // If enabled then initialize them to operation mode
    
}

/**
 * @brief acquire and send sensor data. 
 * 
 * @details Make sure to do this only for features enabled in the settings
 * 
 */
void sensor_send(void){
    //assemble information
    lorawan_send(sensor_packet_port, &sensor_packet.bytes[0], sizeof(sensorData_t));
}