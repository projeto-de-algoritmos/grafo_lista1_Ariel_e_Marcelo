package main

import (
    "./imageprocessing"

    "fmt"
    "gocv.io/x/gocv"
    "image"
    "io"
    "os"
)

/**
 *
 * @brief      { function_description }
 * @return     { description_of_the_return_value }
 */
func main() {

    Marshist := gocv.NewMat() //mat for histogram equalization
    //MarsEdge := gocv.NewMat() //mat for Canny edge
    Marsgray := gocv.NewMat() //mat for read
    Mars := gocv.NewMat()     //mat for paint

    Marsgray = imageprocessing.ReadImage(Marsgray, "./imageprocessing/Images/Mars.bmp", true, false, false)
    Mars = imageprocessing.ReadImage(Mars, "./imageprocessing/Images/Mars.bmp", true, false, false)

    Marshist = imageprocessing.ProcessImage(Marsgray, Marshist, "./imageprocessing/Images/MarsHistogram.bmp", true, true)

}
