#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "iostream"
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
    //load the iimage, by adding the file path
    const char* filename = argc >=2 ? argv[1] : "/home/kally/Downloads/ballTestPerspective.jpg";
    // Loads the image in colour
    Mat src = imread( samples::findFile( filename ), IMREAD_COLOR );
    // Check if image is loaded fine
    if(src.empty()){
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default %s] \n", filename);
        return EXIT_FAILURE;
    }
    //define a matrix to store the gray scale of the image
    Mat gray;
    //convert the imagee from BGR to grayscale
    cvtColor(src, gray, COLOR_BGR2GRAY);
    //Apply a median filter to reduce noise, with a medium sized kernel  5
    medianBlur(gray, gray, 5);
    //create a vec to store the circles, each circle is represented by 3 values: x,y,radius
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/16,  // change this value to detect circles with different distances to each other
                 100, 30, 10, 30 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );
    for( size_t i = 0; i < circles.size(); i++ ) //loop through the detected circles and draw them on the original image
    {
        Vec3i c = circles[i]; //get the ith  circle (x,y,r)
        Point center = Point(c[0], c[1]); // circle center
        //draw the cicrle center as a small dot
        circle( src, center, 1, Scalar(0,100,100), 3, LINE_AA); //draw a small circle in the center with colour (0,100,1)
        //draw the circle outline with the rr of the detected circle
        int radius = c[2];//get the radius of the ith circle
        circle( src, center, radius, Scalar(255,0,255), 3, LINE_AA); //draw the circles perimeter with colour (255,0,255)
        cout<< center.x << ", "<< center.y <<endl;
    }
    imshow("detected circles", src);
    waitKey();
    return EXIT_SUCCESS;
}
