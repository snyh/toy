#include "Control.hpp"
#include "Model.hpp"

#include <opencv2/opencv.hpp>
#include <wx/wx.h>

Control* Control::singleton_ = 0;

Control* Control::getInstance()
{
  if (singleton_ == NULL)
	singleton_ = new Control();
  return singleton_;
}

void Control::setTargetColor(unsigned char red, unsigned char green,
						   unsigned char blue)
{
  this->model_->setTargetColor(red, green, blue);
}

void Control::setTargetPath(const char* filepath)
{

  const cv::Mat& im = cv::imread(filepath);
  this->model_->setTargetImage(im);
  this->Loaded = true;
}

void Control::process()
{
  this->model_->process();
}

wxBitmap Control::getResult()
{
  const cv::Mat& mat = this->model_->getResult();

  unsigned char* wxData = new unsigned char[mat.rows*mat.cols*3];
  cv::Mat cvRGBImg = cv::Mat(mat.rows, mat.cols, CV_8UC3, wxData);

  cvtColor(mat, cvRGBImg, CV_GRAY2RGB);

  // On copy construct the this->result
  // will deconstruct and free the wxData which used new operator on above.
  result = wxImage(mat.cols, mat.rows, wxData);

  return wxBitmap(result);
}

void Control::setThreshold(int distance)
{
  model_->setThreshold(distance);
}
int Control::getThreshold()
{
  return model_->getThreshold();
}
