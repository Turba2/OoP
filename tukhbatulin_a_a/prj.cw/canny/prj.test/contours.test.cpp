#include <iostream>  
#include <opencv2/opencv.hpp>  
#include <canny/canny.hpp> 
#include <ctikz/ctikz.hpp>


using namespace std;
using namespace cv;

//constexpr int VISUALISATION_SIZE = 30;
//
//void draw_pixels(const Mat& picture) {
//    CTikz latex;
//    latex.start_picture();
//
//    if (picture.cols < VISUALISATION_SIZE || picture.rows < VISUALISATION_SIZE) {
//        return;
//    }
//    // int rows = picture.rows;
//    // int cols = picture.cols;
//    for (int i = 0; i < VISUALISATION_SIZE; i++)
//    {
//        for (int j = 0; j < VISUALISATION_SIZE; j++)
//        {
//            return;
//        }
//    }
//}

int main() {
    
    int test_case = 1;
    int max_test_number = 3;
    std::cout << ("Enter the test number from 1 to " + std::to_string(max_test_number) + ":\n");
    std::cin >> test_case;
    std::cout << "\n";

    if (test_case<1 || test_case>max_test_number) {
        printf("The number entered is not from the specified range!");
        return -1;
    }

    std::string test_path = "../tests/test_" + std::to_string(test_case) + "/";

    cv::Mat image = cv::imread(test_path + "image.jpeg");
    
    imshow("origin image", image);

    Mat grayImage;
    cvtColor(image, grayImage, CV_RGB2GRAY);
    imshow("gray image", grayImage);

    Mat gausKernel;
    int kernel_size = 1;
    double sigma = 1;
    Can qwe;
    qwe.Gaussian_kernel(kernel_size, sigma, gausKernel);
    Mat gausImage;
    filter2D(grayImage, gausImage, grayImage.depth(), gausKernel);
    imshow("gaus image", gausImage);

    Mat imageX, imageY, imageXY;
    Mat theta;
    qwe.GradDirection(grayImage, imageX, imageY, imageXY, theta);
    imshow("XY grad", imageXY);

    Mat localImage;
    qwe.NonLocalMaxValue(imageXY, localImage, theta, imageX, imageY);;
    imshow("Non local maxinum image", localImage);

    qwe.DoubleThreshold(localImage, 60, 100);
    qwe.DoubleThresholdLink(localImage, 60, 100);
    imshow("canny image", localImage);

    Mat temMat;
    Canny(image, temMat, 60, 100);
    imshow("opencv canny image", temMat);
    imwrite("saved_image.jpg", temMat);
    waitKey(0);

    return 0;
}