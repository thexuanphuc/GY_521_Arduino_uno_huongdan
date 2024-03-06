
# Làm quen với MPU6050(GY521) và Arduino Uno

## Description
Tìm hiểu cách hiệu chỉnh và so sánh hoạt động của các filter khác nhau. 

## Ví dụ

- **GY521_readCalibration_2**  Tìm giá trị offset
- **GY521_test_main** So sánh hiệu quả Kalman filter và complementary filter

## Giải thích pin trên MPU6050

|  pin  |  Tên pin  |  Ý ngnghĩa        | 
|:-----:|:---------:|:------------------|
|   0   |    VCC    |  +5V              |
|   1   |    GND    |  ground           |
|   2   |    SCL    |  I2C clock        |
|   3   |    SDA    |  I2C data         |
|   4   |    XDA    |  auxiliary data   | 
|   5   |    XCL    |  auxiliary clock  |
|   6   |    AD0    |  address          | 
|   7   |    INT    |  interrupt        |

## Cách hiệu chỉnh

Sketch file readCalibration2.ino trong examples để lấy giá trị offset axe aye aze gxe gye gze và lưu lại. Lưu ý không di chuyển cảm biến trong quá trình hiệu chỉnh

## Thao tác với thư viện

```cpp
#include "GY521.h"
```
### Khởi tạo

- **GY521(uint8_t address = 0x69, , TwoWire*wire = &Wire)** Constructor cho MPU với địa chỉ mặc định. 
- **bool begin()** Returns true nếu phát hiện thiết bị trên I2C bus
  
Note cần gọi **Wire.begin()** trước **begin()**.
- **bool isConnected()** returns true nếu có thiết bị đang sử dụng I2C bus

### Đọc giá trị

#### Cài đặt thông số trước khi đọc giá trị

- **bool setAccelSensitivity(uint8_t as)** as = 0, 1, 2, 3 ==> 2g 4g 8g 16g
- **uint8_t getAccelSensitivity()** returns 0, 1, 2, 3
- **bool setGyroSensitivity(uint8_t gs)** gs = 0,1,2,3  ==>  250, 500, 1000, 2000 degrees/second
- **uint8_t getGyroSensitivity()** returns 0, 1, 2, 3  
= **void setNormalize(bool normalize = true)** góc trả về trong khoảng(-180,180).
= **bool getNormalize()** returns flag.


#### Đọc giá trị từ cảm biến

- **int16_t read()** đọc tất cả giá trị đo từ MPU6050.
returns status = GY521_OK nếu thành công, giá trị góc đã qua bộ lọc complementary filter
- **int16_t read_with_KF()** đọc tất cả giá trị đo từ MPU6050.
returns status = GY521_OK nếu thành công, giá trị góc đã qua bộ lọc Kalman filter

#### Xử lý dữ liệu đầu ra

Trước tiên phải gọi read() hoặc read_with_KF().

- **float getAccelX()** Gia tốc trên phương X
- **float getAccelY()** Gia tốc trên phương Y
- **float getAccelZ()** Gia tốc trên phương Z
- **float getAngleX()** Giá trị góc row nếu chỉ sử dụng accelerator
- **float getAngleY()** Giá trị góc pitch nếu chỉ sử dụng accelerator
- **float getAngleZ()** Giá trị góc yaw nếu chỉ sử dụng accelerator
- **float getGyroX()** Giá trị Rate X nếu chỉ sử dụng gyroscope
- **float getGyroY()** Giá trị rate Y nếu chỉ sử dụng gyroscope
- **float getGyroZ()** Giá trị Rate Z nếu chỉ sử dụng gyroscope
- **float getPitch()** Trả về góc pitch(-180,180) sử dụng complementary filter
- **float getRoll()** Trả về góc roll(-180,180) sử dụng complementary filter
- **float getYaw()** Trả về góc yaw(-180,180) 
- **float get_pitch_kalman()** Trả về góc pitch(-180,180) sử dụng Kalman filter
- **float get_roll_kalman()** Trả về góc roll(-180,180) sử dụng Kalman filter


### Truy cập vào Register

- **uint8_t setRegister(uint8_t reg, uint8_t value)**
- **uint8_t getRegister(uint8_t reg)**

#### Điều chỉnh độ nhạy của cảm biếm

unit g = gravity == 9.81

| Acceleration  |  value  |  notes  |
|:--------------|:-------:|:-------:|
|      2 g      |    0    |  default
|      4 g      |    1    |
|      8 g      |    2    |
|     16 g      |    3    |

unit dps = degrees per second.

|  Gyroscope    |  value  |  notes  |
|:--------------|:-------:|:-------:|
|   250 dps     |    0    |  default
|   500 dps     |    1    |
|  1000 dps     |    2    |
|  2000 dps     |    3    |

## Nguồn liên quan
  + https://github.com/RobTillaart/GY521
  + https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
  + https://cdn.sparkfun.com/datasheets/Sensors/Accelerometers/RM-MPU-6000A.pdf.
  + https://github.com/RobTillaart/Angle
  + https://github.com/RobTillaart/AngleConverter
