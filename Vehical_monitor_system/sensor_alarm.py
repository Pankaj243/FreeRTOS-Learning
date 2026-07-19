import time
import winsound

last_data = ""
while True:
    try:
        with open(r"D:\FreeRTOS\source\repos\005_Queue\005_Queue\sensor_data.txt", "r") as file:
        # with open("sensor_data.txt", "r") as file:
            lines = file.readlines()
        
        if lines:
            data = lines[-1].strip()
            # print(data)
            temp, speed, battery, pressure = map(float, data.split(","))
            
            print(f"Temperature : {temp} C")
            print(f"Speed       : {speed} km/h")
            print(f"Battery     : {battery} V")
            print(f"Pressure    : {pressure} PSI")
            print("-" * 40)

            if temp > 100:
                print("High Temperature!")
                winsound.Beep(2000, 500)

            if speed > 120:
                print("Overspeed!")
                winsound.Beep(1800, 500)

            if battery < 11.8:
                print("Low Battery!")
                winsound.Beep(1000, 500)
            elif  battery > 14.2:
                print("High Battery!")
                winsound.Beep(1000, 500)
            if pressure > 34:
                print("High Pressure!")
                winsound.Beep(1500, 500)
            elif pressure < 30:
                print("Low Pressure!")
                winsound.Beep(1500, 500)
    except Exception as e:
        print(e)

    time.sleep(1)

