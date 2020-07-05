#ifndef ESP32CAM_H
#define ESP32CAM_H

#include "internal/config.hpp"
#include "internal/frame.hpp"

#include <memory>

namespace esp32cam {

class CameraClass
{
public:
  /** \brief Enable camera.
   */
  bool begin(const Config& config);

  /** \brief Disable camera.
   */
  bool end();

  /** \brief Change camera resolution.
   *  \pre Initial resolution is higher than specified resolution.
   *  \param resolution new resolution
   *  \param sleepFor how long to wait for stabilization (millis)
   */
  bool changeResolution(const Resolution& resolution, int sleepFor = 500);

  bool setAutoGain(bool enabled, int sleepFor = 500);
  bool setAutoExposure(bool enabled, int sleepFor = 500);
  bool setGain(int gain, int sleepFor = 500);    //  (0 - 30)
  bool setExposure(int exp, int sleepFor = 500); // set exposure manually  (0-1200)
  bool setVerticalFlip(bool flip, int sleepFor = 500);
  bool setQuality(int quality, int sleepFor = 500); // (0 - 63)
  bool setGainCeiling(int ceiling,
                      int sleepFor = 500); // Image gain (x2, x4, x8, x16, x32, x64 or x128)
  bool setBrightness(int brightness, int sleepFor = 500); // (-2 to 2)
  bool setLensCorrection(bool enabled, int sleepFor = 500);
  bool setSaturation(int saturation, int sleepFor = 500); // (-2 to 2)
  bool setContrast(int contrast, int sleepFor = 500);     // (-2 to 2)
  bool setSharpness(int sharpness, int sleepFor = 500);   // (-2 to 2)
  bool setHorizontalFlip(bool enabled, int sleepFor = 500);
  bool setBlackPixelCorrection(bool enabled, int sleepFor = 500);
  bool setWhitePixelCorrection(bool enabled, int sleepFor = 500);

  /** \brief Capture a frame of picture.
   */
  std::unique_ptr<Frame> capture();

  struct StreamMjpegConfig
  {
    /// minimum interval between frame captures.
    int minInterval = 0;
    /// maximum number of frames before disconnecting.
    int maxFrames = -1;
    /// time limit of writing one frame in millis.
    int frameTimeout = 10000;
  };

  /** \brief Stream Motion JPEG.
   *  \pre The camera has been initialized to JPEG mode.
   *  \return number of frames streamed.
   */
  int streamMjpeg(Client& client, const StreamMjpegConfig& cfg);

  int streamMjpeg(Client& client)
  {
    return streamMjpeg(client, StreamMjpegConfig());
  }
};

extern CameraClass Camera;

inline std::unique_ptr<Frame>
capture()
{
  return Camera.capture();
}

} // namespace esp32cam

#endif // ESP32CAM_H
