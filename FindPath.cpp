#include "FindPath.hpp"
#include <opencv2/highgui.hpp>
/**
 * @brief      { PaintBlack }
 *
 * @param      Image  The image
 * @param[in]  Row    The row
 * @param[in]  Col    The col
 */
void PaintBlack(cv::Mat& Image, int Row, int Col){
	Image.at<cv::Vec3b>(Row,Col)[2] = 0;
	Image.at<cv::Vec3b>(Row,Col)[1] = 0;
	Image.at<cv::Vec3b>(Row,Col)[0] = 0;
}
/**
 * @brief      { PaintRed }
 *
 * @param      Image  The image
 * @param[in]  Row    The row
 * @param[in]  Col    The col
 */
void PaintRed(cv::Mat& Image, int Row, int Col){
	Image.at<cv::Vec3b>(Row,Col)[2] = 102;
	Image.at<cv::Vec3b>(Row,Col)[1] = 0;
	Image.at<cv::Vec3b>(Row,Col)[0] = 0;
}
/**
 * @brief      { PaintBlue }
 *
 * @param      Image  The image
 * @param[in]  Row    The row
 * @param[in]  Col    The col
 */
void PaintBlue(cv::Mat& Image, int Row, int Col){
	Image.at<cv::Vec3b>(Row,Col)[2] = 0;
	Image.at<cv::Vec3b>(Row,Col)[1] = 9;
	Image.at<cv::Vec3b>(Row,Col)[0] = 76;
}
/**
 * @brief      { PaintSquare }
 *
 * @param      Image  The image
 * @param[in]  Row    The row
 * @param[in]  Col    The col
 * @param[in]  Color  The color
 */
void PaintSquare(cv::Mat& Image, int Row, int Col,int Color){

	if (Color == Red)
	{
		PaintRed(Image,Row,Col);
	}
	else
	{
		PaintBlue(Image,Row,Col);
	}
	for (int c = (Col+4); c < (Col+12); ++c){
		for (int r = (Row-10); r < (Row+10); ++r){
			if (Color == Red){
				PaintRed(Image,r,c);
			}
			else{
				PaintBlue(Image,r,c);
			}
		}
	}
	for (int c = (Col-12); c < (Col-4); ++c){
		for (int r = (Row-10); r < (Row+10); ++r){
			if (Color == Red)
			{
				PaintRed(Image,r,c);
			}
			else
			{
				PaintBlue(Image,r,c);
			}
		}
	}


	//----------------------------------------------------
	for (int r = (Row+4); r < (Row+12); ++r){
		for (int c = (Col-10); c < (Col+10); ++c){
			if (Color == Red){
				PaintRed(Image,r,c);
			}
			else{
				PaintBlue(Image,r,c);
			}
		}
	}
	for (int r = (Row-12); r < (Row-4); ++r){
		for (int c = (Col-10); c < (Col+10); ++c){
			if (Color == Red){
				PaintRed(Image,r,c);
			}
			else{
				PaintBlue(Image,r,c);
			}
		}
	}
}

/**
 * @brief      { initialize it }
 *
 * @param      NewWalkingPoint  The new walking point
 * @param[in]  Origin           The origin
 */
void InitializeWalkingPoint(WalkingPoint& NewWalkingPoint, Point Origin){
	NewWalkingPoint.Current.Row = Origin.Row;
	NewWalkingPoint.Current.Col = Origin.Col;
	NewWalkingPoint.Neighbors = (Point*)calloc(8,sizeof(Point));
}
/**
 * @brief      { find the neighbors }
 *
 * @param      CurrentWalkingPoint  The current walking point
 */
void FindNeighBors(WalkingPoint& CurrentWalkingPoint){
	//N4----------------------------
	CurrentWalkingPoint.Neighbors[1].Row = (CurrentWalkingPoint.Current.Row)+1;
	CurrentWalkingPoint.Neighbors[1].Col = CurrentWalkingPoint.Current.Col;

	CurrentWalkingPoint.Neighbors[3].Row = CurrentWalkingPoint.Current.Row;
	CurrentWalkingPoint.Neighbors[3].Col = (CurrentWalkingPoint.Current.Col)+1;

	CurrentWalkingPoint.Neighbors[5].Row = (CurrentWalkingPoint.Current.Row)-1;
	CurrentWalkingPoint.Neighbors[5].Col =	CurrentWalkingPoint.Current.Col;

	CurrentWalkingPoint.Neighbors[7].Row = CurrentWalkingPoint.Current.Row;
	CurrentWalkingPoint.Neighbors[7].Col = (CurrentWalkingPoint.Current.Col)-1;

	//ND----------------------------------------------------------------------------
	CurrentWalkingPoint.Neighbors[0].Row = (CurrentWalkingPoint.Current.Row)+1;
	CurrentWalkingPoint.Neighbors[0].Col = (CurrentWalkingPoint.Current.Col)-1;

	CurrentWalkingPoint.Neighbors[2].Row = (CurrentWalkingPoint.Current.Row)+1;
	CurrentWalkingPoint.Neighbors[2].Col = (CurrentWalkingPoint.Current.Col)+1;

	CurrentWalkingPoint.Neighbors[4].Row = (CurrentWalkingPoint.Current.Row)-1;
	CurrentWalkingPoint.Neighbors[4].Col = (CurrentWalkingPoint.Current.Col)+1;

	CurrentWalkingPoint.Neighbors[6].Row = (CurrentWalkingPoint.Current.Row)-1;
	CurrentWalkingPoint.Neighbors[6].Col = (CurrentWalkingPoint.Current.Col)-1;
}
/**
 * @brief      { ahmmmm, calculate the euclidian distance }
 *
 * @param[in]  CurrentPoint  The current point
 * @param[in]  Destination   The destination
 *
 * @return     { description_of_the_return_value }
 */
double EuclidianDistances(Point CurrentPoint, Point Destination){
	double DeltaRow;
	double DeltaCol;
	double Distance;
	DeltaRow = (double)(Destination.Row - CurrentPoint.Row);
	DeltaCol = (double)(Destination.Col - CurrentPoint.Col);
	Distance = sqrt(pow(DeltaRow,2) + pow(DeltaCol,2));
	return Distance;
}
/**
 * @brief      { ahmmmm, sort? }
 *
 * @param      Vector  The vector
 * @param[in]  size    The size
 */
void SelectionSort(Candidate *Vector, uint16_t size){
	if ((Vector == NULL) || (size < 2))
	{
		return;
	}
	int16_t Smallest, i, j;
	Candidate temp;
	for (i = 0; i < (size-1); ++i)
	{
		Smallest = i;
		for (j = i+1; j < size; ++j)
		{
			if (Vector[Smallest].Distance > Vector[j].Distance)
			{
				Smallest = j;
			}
		}
		temp.Distance = Vector[i].Distance;
		temp.Key = Vector[i].Key;

		Vector[i].Distance = Vector[Smallest].Distance;
		Vector[i].Key = Vector[Smallest].Key;

		Vector[Smallest].Distance = temp.Distance;
		Vector[Smallest].Key = temp.Key;
	}
}
/**
 * @brief      { calculate and paint best path }
 *
 * @param      ColoredImage  The colored image
 * @param      WorkImage     The work image
 */
long int FindPath(cv::Mat& ColoredImage, cv::Mat& WorkImage,Point Base, Point destiny,bool red){
	int AuxRow;
	int AuxCol;
	int AuxGreyLevel;
	Point base;
	Point Destination;
	WalkingPoint WorkPoint;

	base.Row = Base.Row;
	base.Col = Base.Col;

	Destination.Row = destiny.Row;
	Destination.Col = destiny.Col;
	InitializeWalkingPoint(WorkPoint,base);
	long int weight = 0;
	Candidate* Candidates = (Candidate*)calloc(8,sizeof(Candidate));
	for (int i = 0;((WorkPoint.Current.Row != Destination.Row) || (WorkPoint.Current.Col != Destination.Col)); ++i)
	{
		FindNeighBors(WorkPoint);
		for (int j = 0; j < 8; ++j)
		{
			Candidates[j].Key = j; //with that , i have a nice way to access the neibors in the future
			Candidates[j].Distance = EuclidianDistances(WorkPoint.Neighbors[j],Destination);
		}
		int pato = 1;
		SelectionSort(Candidates,8);
		pato = 2;

		/*AuxRow And AuxCol, in this part, are used to access the gray level
		of the 3 neighbors with the smallests distances to the destination */
		AuxRow = WorkPoint.Neighbors[Candidates[0].Key].Row;
		AuxCol = WorkPoint.Neighbors[Candidates[0].Key].Col;
		Candidates[0].Distance = (Candidates[0].Distance) * (int)(WorkImage.at<uint8_t>(AuxRow , AuxCol));

		AuxRow = WorkPoint.Neighbors[Candidates[1].Key].Row;
		AuxCol = WorkPoint.Neighbors[Candidates[1].Key].Col;
		Candidates[1].Distance = (Candidates[1].Distance) * (int)(WorkImage.at<uint8_t>(AuxRow , AuxCol));

		AuxRow = WorkPoint.Neighbors[Candidates[2].Key].Row;
		AuxCol = WorkPoint.Neighbors[Candidates[2].Key].Col;
		Candidates[2].Distance = (Candidates[2].Distance) * (int)(WorkImage.at<uint8_t>(AuxRow , AuxCol));

		SelectionSort(Candidates,3);

		/*AuxRow And AuxCol, in this part, are used to access the row and the col of the selected neighbor*/
		AuxRow = WorkPoint.Neighbors[Candidates[0].Key].Row;
		AuxCol = WorkPoint.Neighbors[Candidates[0].Key].Col;
		weight = weight + (int)(WorkImage.at<uint8_t>(AuxRow , AuxCol));
		if( red ){
			PaintRed(ColoredImage,AuxRow,AuxCol);
			cv::imshow( "Current path", ColoredImage );
			cv::waitKey(5);
		}else{
			PaintBlack(ColoredImage,AuxRow,AuxCol);
			cv::imshow( "Current path", ColoredImage );
			cv::waitKey(1);
		}

		WorkPoint.Current.Row = AuxRow;
		WorkPoint.Current.Col = AuxCol;

	}

	// std::cout <<WorkPoint.Current.Row<<     "Last Row\n";
	// std::cout <<WorkPoint.Current.Col<<     "Last Col\n";
	return weight;
}
/**
 * @brief      { function_description }
 *
 * @param[in]  argc  The argc
 * @param      argv  The argv
 *
 * @return     { description_of_the_return_value }
 */
int main(int argc, char const *argv[]){
	if (argc == 1){
		cv::Mat ColoredImage;
		cv::Mat WorkImage;
		ColoredImage = cv::imread("./imageprocessing/Images/Mars.bmp", CV_LOAD_IMAGE_COLOR);
		WorkImage = cv::imread("./imageprocessing/Images/MarsHistogram.bmp" ,  CV_8UC1);
		std::vector<Point> suplies;
		Point Base;
		Base.Row = 235;
		Base.Col = 462;
		Point aux;
		//0
		aux.Row = 50;
		aux.Col = 1000;
		suplies.push_back(aux);
		//1
		aux.Row = 74;
		aux.Col = 233;
		suplies.push_back(aux);
		//2
		aux.Row = 444;
		aux.Col = 802;
		suplies.push_back(aux);
		//3
		aux.Row = 744;
		aux.Col = 372;
		//4
		aux.Row = 540;
		aux.Col = 444;
		suplies.push_back(aux);
		//5
		aux.Row = 688;
		aux.Col = 34;
		suplies.push_back(aux);
		//6
		aux.Row = 100;
		aux.Col = 380;
		suplies.push_back(aux);
		//7
		aux.Row = 815;
		aux.Col = 940;
		suplies.push_back(aux);
		PaintSquare(ColoredImage,Base.Row,Base.Col,Red);
		std::cout<<7<<" "<<42<<std::endl;
		for (int i = 0; i < 6; ++i){
			long int dist;
			PaintSquare(ColoredImage,suplies[i].Row,suplies[i].Col,Blue);
			dist = FindPath(ColoredImage,WorkImage,Base,suplies[i],false);
			std::cout<<1<<" "<<(i+2)<<" "<<dist<<std::endl;
			dist = FindPath(ColoredImage,WorkImage,suplies[i],Base,false);
			std::cout<<(i+2)<<" "<<1<<" "<<dist<<std::endl;
		}
		for (int i = 0; i < 6; ++i){
			for (int j = 0; j < 6; ++j){
				if((i == 6 ) && (i==j))break;
				if (j == i) j++;
				if(j == 6) break;
				long int dist;
				dist = FindPath(ColoredImage,WorkImage,suplies[i],suplies[j],false);
				std::cout<<(i+2)<<" "<<(j+2)<<" "<<dist<<std::endl;
			}
		}
		std::cout<<1<<std::endl;
		cv::imshow( "Path", ColoredImage );
		cv::imwrite("GraphAllPaths.bmp",ColoredImage);
		cv::waitKey(0);
		return 0;
	}
	else{
		if (argc == 2){
			Point Base;
			Base.Row = 235;
			Base.Col = 462;
			Point aux;
			std::vector<Point> Path;
			Path.push_back(Base);
			aux.Row = 50;
			aux.Col = 1000;
			Path.push_back(aux);
			//1
			aux.Row = 74;
			aux.Col = 233;
			Path.push_back(aux);
			//2
			aux.Row = 444;
			aux.Col = 802;
			Path.push_back(aux);
			//3
			aux.Row = 744;
			aux.Col = 372;
			//4
			aux.Row = 540;
			aux.Col = 444;
			Path.push_back(aux);
			//5
			aux.Row = 688;
			aux.Col = 34;
			Path.push_back(aux);
			//6
			aux.Row = 100;
			aux.Col = 380;
			Path.push_back(aux);
			//7
			aux.Row = 815;
			aux.Col = 940;
			Path.push_back(aux);
			//pinta imagem
			cv::Mat ColoredImage;
			cv::Mat WorkImage;
			ColoredImage = cv::imread("./imageprocessing/Images/Mars.bmp", CV_LOAD_IMAGE_COLOR);
			WorkImage = cv::imread("./imageprocessing/Images/MarsHistogram.bmp" ,  CV_8UC1);
			int size,origin,destiny,dist;
			std::cin>>size;
			for (int i = 0; i < size; ++i){
				std::cin>>origin>>destiny;
				if(i==0){
					PaintSquare(ColoredImage,Path[origin].Row,Path[origin].Col,Red);
				}
				else{
					PaintSquare(ColoredImage,Path[origin].Row,Path[origin].Col,Blue);
				}

				dist = FindPath(ColoredImage,WorkImage,Path[origin],Path[destiny],true);
			}
			cv::imshow( "Path", ColoredImage );
			cv::imwrite("BestPaths.bmp",ColoredImage);
			cv::waitKey(0);
		}
		else{
			std::cout<<"Invalid Execution"<<std::endl;
		}
	}
}
