#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main() {

  double scale = 2.0;

  CascadeClassifier faceCascade;

  // Train CascadeClassifier based on default data
  faceCascade.load("..\\..\\opencv\\build\\etc\\haarcascades\\haarcascade_"
                   "frontalface_default.xml");

  VideoCapture capture(0);

  if (!capture.isOpened()) {
    cout << "Error: No Camera Found" << endl;
    return -1;
  }

  Mat frame, grayscale;
  vector<Rect> faces;
  Scalar drawColor = Scalar(0, 0, 255);

  while (true) {

    capture >> frame;

    // Converts fram to grayscale
    cvtColor(frame, grayscale, COLOR_BGR2GRAY);

    resize(
        grayscale, grayscale,
        Size(grayscale.size().width / scale, grayscale.size().height / scale));

    // Detect Faces
    faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

    for (Rect area : faces) {

      rectangle(frame,
                // Top Left Point of Rectangle
                Point(cvRound(area.x * scale), cvRound(area.y * scale)),
                // Bottom Right Point of Rectangle
                Point(cvRound((area.x + area.width - 1) * scale),
                      cvRound((area.y + area.height - 1) * scale)),
                drawColor);
    }

    // Shows frame
    imshow("Webcam", frame);

    // If a key is pressed from the keyboard, then stop capture
    if (waitKey(30) >= 0) {
      break;
    }
  }

  return 0;
}