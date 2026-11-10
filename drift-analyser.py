import matplotlib.pyplot as plt
import numpy as np
import pandas as pd 

path = r"C:\Users\Tanav\Downloads\Robo_self\NOV to y27\mpu6050-readings\readings-flat.txt"

readings = np.loadtxt(path, delimiter=",")
readings[:,:3] /= 16384
readings[:,3:] /= 131

detail = ["Acc X", "Acc Y", "Acc Z", "Gyro X", "Gyro Y", "Gyro Z"]
unit = ["g", "g", "g", "deg/s", "deg/s", "deg/s"]

# 1. Create a list to store row data
summary_data = []

for i in range(readings.shape[1]):
    plt.subplot(3, 2, i + 1)
    plt.grid()
    plt.tight_layout(pad=.2, w_pad=.3, h_pad=1)
    plt.plot(range(readings.shape[0]), readings[:, i], label=detail[i])
    plt.xlabel("readings")
    plt.ylabel(unit[i])
    plt.legend()
    
    # 2. Append a dictionary for each sensor metric
    summary_data.append({
        "Metric": detail[i],
        "Mean": np.mean(readings[:, i]),
        "Std Dev": np.std(readings[:, i])
    })

end_table = pd.DataFrame(summary_data).set_index("Metric")

print(end_table)
plt.show()

