#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
using namespace cv;
using namespace std;

#include <stdlib.h>
#include <stdio.h>

#include <iostream>

Mat frame;
Mat frame_copy;

void captureFromCamera() {
    VideoCapture cap(0); 

    if (!cap.isOpened()) 
    {
        cout << "Cannot open the video cam" << endl;
        return;
    }

    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); 

    cout << "Frame size : " << dWidth << " x " << dHeight << endl;

    namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); 

    while (1)
    {

        bool bSuccess = cap.read(frame); 

        if (!bSuccess) 
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        frame.copyTo(frame_copy);
        
        Mat hsv = Mat(frame_copy.cols, frame_copy.rows, 8, 3); 
        vector<Mat> splitedHsv = vector<Mat>();
        cvtColor(frame_copy, hsv, CV_BGR2HSV);
        split(hsv, splitedHsv);

        const int GREEN_MIN = 47; 
        const int GREEN_MAX = 95;
        for (int y = 0; y < hsv.cols; y++) {
            for (int x = 0; x < hsv.rows; x++) {
                // получаем HSV-компоненты пикселя
                int H = static_cast<int>(splitedHsv[0].at<uchar>(x, y)); // Тон
                int S = static_cast<int>(splitedHsv[1].at<uchar>(x, y)); // Интенсивность
                int V = static_cast<int>(splitedHsv[2].at<uchar>(x, y)); // Яркость

                //Если яркость слишком низкая либо Тон не попадает у заданный диапазон, то закрашиваем белым
                if ((V < 20) || (H < GREEN_MIN) || (H > GREEN_MAX)) {
                    frame_copy.at<Vec3b>(x, y)[0] = 255;
                    frame_copy.at<Vec3b>(x, y)[1] = 255;
                    frame_copy.at<Vec3b>(x, y)[2] = 255;
                }
            }
        }
          
        int an = 7;
        //Морфологическое замыкание для удаления остаточных шумов.
        Mat element = getStructuringElement(MORPH_ELLIPSE, Size(an * 2 + 1, an * 2 + 1), Point(an, an));
        dilate(frame_copy, frame_copy, element);
        erode(frame_copy, frame_copy, element);

        Mat grayscaleMat;
        cvtColor(frame_copy, grayscaleMat, CV_BGR2GRAY);

        //Делаем бинарную маску
        Mat mask(grayscaleMat.size(), grayscaleMat.type());
        Mat out(frame_copy.size(), frame_copy.type());
        threshold(grayscaleMat, mask, 200, 255, THRESH_BINARY_INV);

        const int minRectDim = 20;
        const int maxRectDim= 400;
        for (int y = 0; y < mask.rows; y++)
        {
            for (int x = 0; x < mask.cols; x++)
            {
                int value = mask.at<uchar>(y, x);
                if (value == 255)
                {
                    Rect rect;
                    int count = floodFill(mask, Point(x, y), Scalar(200), &rect);
                    if(rect.width >= minRectDim && rect.width <= maxRectDim
                        && rect.height >= minRectDim && rect.height <= maxRectDim) 
                    { int x = rect.x+ rect.width/ 2;
                    int y = rect.y+ rect.height/ 2;
                    int rad = ( rect.width+ rect.height) / 3;
                    circle(frame, Point( x, y ), rad, Scalar( 255, 0, 255 ), 2 );
                    circle(mask, Point(x, y), rad, Scalar(255, 255, 255),1);
                    }
                }
            }
        }

        imshow("Video", frame);
        imshow("Mask", mask);

        if (waitKey(30) == 27) 
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
    }
}


int main(int argc, char* argv[])
{
    captureFromCamera();
    return 0;
}

