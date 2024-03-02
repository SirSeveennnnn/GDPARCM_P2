#pragma once
#include <vector>
#include "opencv2/core.hpp"

class RTImage
{

public:
	RTImage(const int imageWidth, const int imageHeight);
	void setPixel(int x, int y, float r, float g, float b, int samplePerPixel);
	void setRow(int y, std::vector<cv::Vec3b>& rowPixels, int samplePerPixel);
	void saveImage(cv::String& fileName) const;

	std::unique_ptr<cv::Mat> pixels;
private:
	
	int imageWidth;
	int imageHeight;

};

