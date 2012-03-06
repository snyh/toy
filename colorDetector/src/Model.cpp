#include "Model.hpp"
#include <iostream>

Model::Model(): minDist(100) 
{
  setTargetColor(0,0,0);
}

void Model::setTargetImage(const cv::Mat& image)
{
  if (image.data) {
	  converted.create(image.rows, image.cols, image.type());
	  result.create(image.rows, image.cols, CV_8U);
	  cv::cvtColor(image, converted, CV_BGR2Lab);
  }
}

void Model::setTargetColor(unsigned char red, unsigned char green, 
						   unsigned char blue) 
{
  cv::Mat tmp(1, 1, CV_8UC3);
  tmp.at<cv::Vec3b>(0,0)[0] = blue;
  tmp.at<cv::Vec3b>(0,0)[1] = green;
  tmp.at<cv::Vec3b>(0,0)[2] = red;
  cv::cvtColor(tmp, tmp, CV_BGR2Lab);
  target = tmp.at<cv::Vec3b>(0, 0);
}

void Model::setThreshold(int distance) 
{
  if (distance < 0)
	distance = 0;
  minDist = distance;
}

int Model::getThreshold() const {
	return minDist;
}

int Model::getDistance(const cv::Vec3b& color) const 
{
  return abs(color[0] - target[0]) + 
	abs(color[1] - target[1]) +
	abs(color[2] - target[2]);
}

void Model::process()
{
  cv::Mat_<cv::Vec3b>::const_iterator it = converted.begin<cv::Vec3b>();
  cv::Mat_<cv::Vec3b>::const_iterator itend = converted.end<cv::Vec3b>();

  cv::Mat_<uchar>::iterator itout = result.begin<uchar>();

  for (; it != itend; ++it, ++itout) {
	  if (getDistance(*it) < this->minDist) {
		  *itout = 255;
	  } else {
		  *itout = 0;
	  }
  }
}
