#pragma once

#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;



/**
* @brief The only library class that implements the canny algorithm
*/
class Can {
public:
    /**
    * @brief This function generates a Gaussian kernel used to blur. 
    * It takes the kernel size and sigma (standard deviation)
    * as input and calculates the kernel values based on the Gaussian distribution formula.
    *
    * @param kernel_size Gaussian filter kernel size - must be an odd number, e.g. 3x3, 5x5, 7x7, etc.
    * @param sigma The sigma parameter is the standard deviation of the Gaussian distribution. It must be greater than 0.
    * The greater the sigma value, the wider the distribution and the greater the attenuation in areas that are further from the centre.
    * @param kernel it is the matrix into which the Gaussian filter kernel will be written.
    */
    void Gaussian_kernel(int kernel_size, int sigma, Mat& kernel);
    /**
    * @brief This function calculates the direction of the gradient and the value of each pixel in the image.
    * It takes the original image as input data and calculates the gradient values using finite differences.
    * It also calculates the gradient direction(theta) in degrees.
    *
    * @param imageSource Input image
    * @param imageX Matrix to store the gradient in the x direction
    * @param imageY Matrix to store the gradient in the y direction
    * @param gradXY Matrix to store the gradient magnitude
    * @param theta Matrix to store the gradient direction (in degrees)
    */
    void GradDirection(const Mat imageSource, Mat& imageX, Mat& imageY, Mat& gradXY, Mat& theta);
    /**
    * @brief This function suppresses the non-maximum gradient value in the image.
    * It compares the gradient value of each pixel to its neighbours in the gradient direction and suppresses non-maximum values, 
    * Retains only the local maxima.
    *
    * @param imageInput Input image to apply Non-Local Maximum Value suppression to.
    * @param imageOutput Output image after Non-Local Maximum Value suppression has been applied.
    * @param theta Matrix containing angle values of gradient for each pixel in the input image.
    * @param imageX Matrix containing horizontal gradient values for each pixel in the input image.
    * @param imageY Matrix containing vertical gradient values for each pixel in the input image.
    */ 
    void NonLocalMaxValue(const Mat imageInput, Mat& imageOutput, const Mat& theta, const Mat& imageX, const Mat& imageY);
    /**
    * @brief This function applies a double threshold value to the image.It takes a low threshold and a high threshold as input.
    * Pixels with values above the high threshold are considered strong edges, pixels below the low threshold are considered non-edge, 
    * and pixels between the two thresholds are weak edges.
    *
    * @param imageInput Input image.
    * @param lowThreshold Low threshold value.
    * @param highThreshold High threshold value.
    */
    void DoubleThreshold(Mat& imageInput, const double lowThreshold, const double highThreshold);
    /**
   * @brief This function performs edge linking by connecting weak edges to strong edges.
   * It takes the output image from DoubleThreshold and checks the adjacent pixels of each pixel with a weak edge.
   * If the adjacent pixel is a strong edge, it is marked as part of the edge.
   *
   * @param imageInput Input image for applying the threshold linking algorithm.
   * @param lowTh Lower threshold value.
   * @param highTh Upper threshold value.
   */
    void DoubleThresholdLink(Mat& imageInput, double lowTh, double highTh);
};