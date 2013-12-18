#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

typedef Vec<uchar, 1> Vec1b;
typedef Vec<uchar, 3> Vec3b;

#define WHITE Vec3b(255, 255, 255)

/**
 * Initially, output is the same as the original input.
 * It will be modified: watermark pixels will be set to white.
 */
void removeWatermark(Mat output, uchar threshold) {
  Mat grayScale;
  cvtColor(output, grayScale, CV_RGB2GRAY);

  int rows = output.rows;
  int cols = output.cols;

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      uchar testPixel = grayScale.at<Vec1b>(r, c)[0];
      if (testPixel > threshold) {
        output.at<Vec3b>(r, c) = WHITE;
      }
    }
  }
}

int main(int argc, const char* argv[]) {
  if (argc != 3 && argc != 4) {
    cout << "Usage: remove_watermark <input image> <threshold> [output image]" << endl;
    return -1;
  }

  const char* inputFileName = argv[1];
  uchar       threshold     = (uchar) atoi(argv[2]);
  bool        writeOutput   = argc == 4;

  Mat input;
  input = imread(argv[1], CV_LOAD_IMAGE_COLOR);

  if (!input.data) {
    cout <<  "Could not open or find the image" << endl;
    return -1;
  }

  Mat output(input);
  removeWatermark(output, threshold);

  if (writeOutput) {
    const char* outputFileName = argv[3];
    imwrite(outputFileName, output);
  } else {
    namedWindow("Display window", CV_WINDOW_AUTOSIZE);
    //imshow("Display window", input);
    imshow("Display window", output);
    waitKey(0);
  }

  return 0;
}
