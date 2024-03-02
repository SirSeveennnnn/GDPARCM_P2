#include "RTImage.h"
#include <opencv2/imgcodecs.hpp>



RTImage::RTImage(const int imageWidth, const int imageHeight)
{
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;

	this->pixels = std::make_unique<cv::Mat>(cv::Mat::zeros(this->imageHeight, this->imageWidth, CV_8UC3));
}

void RTImage::setPixel(int x, int y, float r, float g, float b, int samplePerPixel)
{
	
	float scale = 1.0f / samplePerPixel;

	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	int ir = static_cast<uchar>(255.999 * r);
	int ig = static_cast<uchar>(255.999 * g);
	int ib = static_cast<uchar>(255.999 * b);

	cv::Mat imgChannels[3];
	cv::split(*this->pixels, imgChannels);

	imgChannels[0].at<uchar>(y, x) = ib;
	imgChannels[1].at<uchar>(y, x) = ig;
	imgChannels[2].at<uchar>(y, x) = ir;

	cv::merge(imgChannels, 3, *this->pixels);

}

void RTImage::setRow(int y, std::vector<cv::Vec3b>& rowPixels, int samplePerPixel)
{
    // Ensure that the rowPixels vector has the same width as the image
    assert(rowPixels.size() == static_cast<size_t>(imageWidth));

    // Loop over each pixel in the row and set its value
    for (int x = 0; x < imageWidth; ++x) {
        // Get the pixel color components
        float r = rowPixels[x][2];
        float g = rowPixels[x][1];
        float b = rowPixels[x][0];

        // Scale the color components
        float scale = 1.0f / samplePerPixel;
        r = sqrt(scale * r);
        g = sqrt(scale * g);
        b = sqrt(scale * b);

        // Convert the scaled color components to integers
        int ir = static_cast<uchar>(255.999 * r);
        int ig = static_cast<uchar>(255.999 * g);
        int ib = static_cast<uchar>(255.999 * b);

        // Set the pixel value in the image matrix
        pixels->at<cv::Vec3b>(y, x) = cv::Vec3b(ib, ig, ir);
    }
}

void RTImage::saveImage(cv::String& fileName) const
{
	cv::imwrite(fileName, *this->pixels);
}
