#include "esp32cam.h"

#include <Arduino.h>
#include <esp_camera.h>

namespace esp32cam {

CameraClass Camera;

bool
CameraClass::begin(const Config& config)
{
  return esp_camera_init(reinterpret_cast<const camera_config_t*>(config.m_cfg)) == ESP_OK;
}

bool
CameraClass::end()
{
  return esp_camera_deinit() == ESP_OK;
}

bool
CameraClass::changeResolution(const Resolution& resolution, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }

  framesize_t frameSize = resolution.as<framesize_t>();
  if (sensor->status.framesize == frameSize) {
    return true;
  }

  if (sensor->set_framesize(sensor, frameSize) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}

bool
CameraClass::setAutoGain(bool enabled, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_gain_ctrl(sensor, int(enabled)) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}
bool
CameraClass::setAutoExposure(bool enabled, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_exposure_ctrl(sensor, int(enabled)) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}
bool
CameraClass::setGain(int gain, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_agc_gain(sensor, gain) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}

bool
CameraClass::setExposure(int exp, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_aec_value(sensor, exp) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}
bool
CameraClass::setVerticalFlip(bool flip, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_vflip(sensor, int(flip)) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}

bool
CameraClass::setQuality(int quality, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_quality(sensor, quality) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}
bool
CameraClass::setGainCeiling(int ceiling, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  int ceil = 0;
  switch (ceiling) {
    case 2:
      ceil = GAINCEILING_2X;
      break;
    case 4:
      ceil = GAINCEILING_4X;
      break;
    case 8:
      ceil = GAINCEILING_8X;
      break;
    case 16:
      ceil = GAINCEILING_16X;
      break;
    case 32:
      ceil = GAINCEILING_32X;
      break;
    case 64:
      ceil = GAINCEILING_64X;
      break;
    case 128:
      ceil = GAINCEILING_128X;
      break;
    default:
      return false;
  }
  if (sensor->set_gainceiling(sensor, ceil) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}

bool
CameraClass::setBrightness(int brightness, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_brightness(sensor, brightness) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}
bool
CameraClass::setLensCorrection(bool enabled, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_lenc(sensor, int(enabled)) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}

bool
CameraClass::setSaturation(int saturation, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_saturation(sensor, saturation) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}
bool
CameraClass::setContrast(int contrast, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_contrast(sensor, contrast) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}

bool
CameraClass::setSharpness(int sharpness, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_sharpness(sensor, sharpness)) {
    return false;
  }
  delay(sleepFor);
  return true;
}
bool
CameraClass::setHorizontalFlip(bool enabled, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_hmirror(sensor, int(enabled)) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}

bool
CameraClass::setBlackPixelCorrection(bool enabled, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_bpc(sensor, int(enabled)) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}
bool
CameraClass::setWhitePixelCorrection(bool enabled, int sleepFor)
{
  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor == nullptr) {
    return false;
  }
  if (sensor->set_wpc(sensor, int(enabled)) != 0) {
    return false;
  }
  delay(sleepFor);
  return true;
}

std::unique_ptr<Frame>
CameraClass::capture()
{
  camera_fb_t* fb = esp_camera_fb_get();
  if (fb == nullptr) {
    return nullptr;
  }
  return std::unique_ptr<Frame>(new Frame(fb));
}

int
CameraClass::streamMjpeg(Client& client, const StreamMjpegConfig& cfg)
{
#define BOUNDARY "e8b8c539-047d-4777-a985-fbba6edff11e"
  client.print("HTTP/1.1 200 OK\r\n"
               "Content-Type: multipart/x-mixed-replace;boundary=" BOUNDARY "\r\n"
               "\r\n");
  auto lastCapture = millis();
  int nFrames;
  for (nFrames = 0; cfg.maxFrames < 0 || nFrames < cfg.maxFrames; ++nFrames) {
    auto now = millis();
    auto sinceLastCapture = now - lastCapture;
    if (static_cast<int>(sinceLastCapture) < cfg.minInterval) {
      delay(cfg.minInterval - sinceLastCapture);
    }
    lastCapture = millis();

    auto frame = capture();
    if (frame == nullptr) {
      break;
    }

    client.printf("Content-Type: image/jpeg\r\n"
                  "Content-Length: %d\r\n"
                  "\r\n",
                  static_cast<int>(frame->size()));
    if (!frame->writeTo(client, cfg.frameTimeout)) {
      break;
    }
    client.print("\r\n--" BOUNDARY "\r\n");
  }
  return nFrames;
#undef BOUNDARY
}

} // namespace esp32cam
