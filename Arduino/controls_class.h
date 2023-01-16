// controls.h

#ifndef CONTROLS_H
#define CONTROLS_H

class Controls {
  private:
    // Déclaratiion des ports
    MeLineFollower lineFinder(PORT_8);
    MeUltrasonicSensor ultraSensor(PORT_7);  //Capt dist
    MeMegaPiDCMotor motorP(PORT1A); // Pince
    MeMegaPiDCMotor motorG(PORT1B); // Roue droite en regardant devant le robot
    MeMegaPiDCMotor motorD(PORT3B); // roue gauche
    MeColorSensor colorsensor_8(PORT_6);
    int sensorState = lineFinder.readSensors(); // Declarer le capteur de ligne

  private:
    
}

#endif