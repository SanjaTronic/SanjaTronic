

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:

// Simulating color sensor data with RGB values
struct Color {
    int red;
    int green;
    int blue;
};

// Simulating motor control
void moveRobotForward() 
    std::cout << "Moving Forward" << std::endl;
}

void turnRobotLeft() 
    std::cout << "Turning Left" << std::endl;
}

void turnRobotRight() 
    std::cout << "Turning Right" << std::endl;
}

// Logic to follow the line based on color
void followLine(Color sensedColor) 
    if (sensedColor.red > 200 && sensedColor.green < 100 && sensedColor.blue < 100) {
        // Turn right if the color is predominantly red
        turnRobotRight();
    } else if (sensedColor.red < 100 && sensedColor.green > 200 && sensedColor.blue < 100) {
        // Turn left if the color is predominantly green
        turnRobotLeft();
    } else {
        // Move forward if other colors are detected
        moveRobotForward();
    }
}
 int main() 
    Color sensedColor1 = {250, 50, 50};
    Color sensedColor2 = {50, 250, 50};
    Color sensedColor3 = {50, 50, 250};

    followLine(sensedColor1);
    followLine(sensedColor2);
    followLine(sensedColor3);

    return 0;
}

}
