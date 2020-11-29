#include <iostream>
#include <conio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/face.hpp>
#include <math.h>
#include "drawLandmarks.hpp"

using namespace std;
using namespace cv;
using namespace cv::face;

int main(int argc, char** argv)
{
	
	CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");
	Ptr<Facemark> facemark = FacemarkLBF::create();
	facemark->loadModel("lbfmodel.yaml");
	VideoCapture cam(0);
	Mat frame, gray;

	int x1 = 10;
	int x2 = 13;
	int x3 = 300;
	int x4 = 640;
	int x5 = 640;
	int r = 27;
	bool flag1 = false;
	bool flag2 = false;
	bool flag3 = false;
	bool flag4 = false;
	bool flag5 = true;
	bool go_game = true;
	int k = 6;


	while (cam.read(frame))
	{
		vector<Rect> faces;
		cvtColor(frame, gray, COLOR_BGR2GRAY);

		faceDetector.detectMultiScale(gray, faces);

		vector< vector<Point2f> > landmarks;
		bool success = facemark->fit(frame, faces, landmarks);
		if (go_game)
		{
			if (success)
			{
				for (size_t i = 0; i < faces.size(); i++)
				{
					/////
					if (landmarks[i][0].x < 2 * x1 + 35 and landmarks[i][16].x > 2 * x1 + 35 and
						landmarks[i][27].y < x1 and landmarks[i][8].y > x1 and
						flag1 == false)
					{
						cv::circle(frame, Point(2 * x1 + 35, x1++), r, Scalar(0, 0, 255), -1);
						flag1 = true;
						k += 1;
					}
					else if (flag1 == true)
					{
						cv::circle(frame, Point(2 * x1 + 35, x1++), r, Scalar(0, 0, 255), -1);
					}
					else
					{
						cv::circle(frame, Point(2 * x1 + 35, x1++), r, Scalar(0, 100, 200), -1);
					}
					x1 += 3;

					///
					if (landmarks[i][0].x < -x2 + 640 and landmarks[i][16].x > -x2 + 640 and
						landmarks[i][27].y < x2 and landmarks[i][8].y > x2 and
						flag2 == false)
					{
						cv::circle(frame, Point(-x2 + 640, x2++), r, Scalar(0, 0, 255), -1);
						flag2 = true;
						k += 1;
					}
					else if (flag2 == true)
					{
						cv::circle(frame, Point(-x2 + 640, x2++), r, Scalar(0, 0, 255), -1);
					}
					else
					{
						cv::circle(frame, Point(-x2 + 640, x2++), r, Scalar(123, 223, 123), -1);
					}
					x2 += 8;
					/// 

					if (landmarks[i][0].x < 150 and landmarks[i][16].x > 150 and
						landmarks[i][27].y < x3 and landmarks[i][8].y > x3 and
						flag3 == false)
					{
						cv::circle(frame, Point(150, x3--), r, Scalar(0, 0, 255), -1);
						flag3 = true;
						k += 1;
					}
					else if (flag3 == true)
					{
						cv::circle(frame, Point(150, x3--), r, Scalar(0, 0, 255), -1);
					}
					else
					{
						cv::circle(frame, Point(150, x3--), r, Scalar(167, 23, 133), -1);
					}
					x3 += 5;

					///
					if (landmarks[i][0].x < x4 and landmarks[i][16].x > x4 and
						landmarks[i][27].y < 400 and landmarks[i][8].y > 400 and
						flag4 == false)
					{
						cv::circle(frame, Point(x4--, 400), r, Scalar(0, 0, 255), -1);
						flag4 = true;
						k += 1;
					}
					else if (flag4 == true)
					{
						cv::circle(frame, Point(x4--, 400), r, Scalar(0, 0, 255), -1);
					}
					else
					{
						cv::circle(frame, Point(x4--, 400), r, Scalar(255, 255, 0), -1);
					}
					x4 -= 10;

					if (landmarks[i][0].x < x5 and landmarks[i][16].x > x5 and
						landmarks[i][27].y < 0.2 * x5 + 170 and landmarks[i][8].y > 0.2 * x5 + 170 and
						flag5)
					{
						rectangle(frame, Rect(x5--, 0.2 * x5 + 170, 50, 50), Scalar(0, 0, 0), -1);
						flag5 = false;
						k -= 6;
					}
					else if (flag5 == false)
					{
						rectangle(frame, Rect(x5--, 0.2 * x5 + 170, 50, 50), Scalar(0, 0, 0), -1);
					}
					else
					{
						rectangle(frame, Rect(x5--, 0.2 * x5 + 170, 50, 50), Scalar(0, 0, 255), -1);
					}
					x5 -= 5;
					/// 
					if (k == 4 or k == 10) break;
				}

			}
			else {
				if (flag1 == true)
				{
					cv::circle(frame, Point(2 * x1 + 35, x1++), r, Scalar(0, 0, 255), -1);
				}
				else
				{
					cv::circle(frame, Point(2 * x1 + 35, x1++), r, Scalar(0, 100, 200), -1);
				}
				///
				if (flag2 == true)
				{
					cv::circle(frame, Point(-x2 + 640, x2++), r, Scalar(0, 0, 255), -1);
				}
				else
				{
					cv::circle(frame, Point(-x2 + 640, x2++), r, Scalar(123, 223, 123), -1);
				}
				/// 
				if (flag3 == true)
				{
					cv::circle(frame, Point(150, x3++), r, Scalar(0, 0, 255), -1);
				}
				else
				{
					cv::circle(frame, Point(150, x3++), r, Scalar(167, 23, 133), -1);
				}
				///
				if (flag4 == true)
				{
					cv::circle(frame, Point(x4--, 400), r, Scalar(0, 0, 255), -1);
				}
				else
				{
					cv::circle(frame, Point(x4--, 400), r, Scalar(255, 255, 0), -1);
				}
				///
				if (flag5 == true)
				{
					rectangle(frame, Rect(x5--, 0.2 * x5 + 170, 50, 50), Scalar(0, 0, 255), -1);
				}
				else
				{
					rectangle(frame, Rect(x5--, 0.2 * x5 + 170, 50, 50), Scalar(0, 0, 0), -1);
				}

				x1 -= 3;
				x2 -= 8;
				x3 -= 5;
				x4 += 10;
				x5 += 5;

			}
			if (k == 4 or k == 10)
			{
				go_game = false;

			}

		}
		else {
			if (k == 4)
			{
				cv::putText(frame, "Good! But the result can be better!", cv::Point(10, 320), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(198, 185, 190), 2);
			}
			else if (k == 10)
			{
				cv::putText(frame, "Great!You won!", cv::Point(10, 320), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(118, 185, 200), 2);
			}
		}
		imshow("Frame", frame);
		if (waitKey(1) == 27) break;
	}
	return 0;
}