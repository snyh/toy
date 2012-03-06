#ifndef __Model_HPP__
#define __Model_HPP__

#include <opencv2/opencv.hpp>
class Model {
public:
  Model();
  void process();

  void setTargetColor(unsigned char red, unsigned char green, 
					  unsigned char blue);
  void setTargetImage(const cv::Mat& image);

  cv::Mat& getResult() { return result; }

  void setThreshold(int distance);
  int getThreshold() const;

private:
  int getDistance(const cv::Vec3b& color) const;

  cv::Vec3b target;
  int minDist;
  cv::Mat result;
  cv::Mat converted;
};

#endif
