#pragma once
#include<iostream>
#include<fstream>
#include<opencv2/opencv.hpp>
#include"util.h"
using namespace std;
using namespace cv;
//Syed Qasim Hussain 21i0379 Section V&E combined
unsigned char** imageread(string fil,int& rows, int& cols) {
	Mat image = imread(fil, IMREAD_GRAYSCALE);

	rows = image.rows;
	cols = image.cols;
	unsigned char** ptr = new unsigned char* [rows];
	for (int i = 0; i < rows; i++)
	{
		ptr[i] = new unsigned char[cols];
		for (int j = 0; j < cols; j++)
		{
			ptr[i][j] = image.at<unsigned char>(i, j);
		}
	}
	return ptr;
}
bool validCheck(int i, int j, int rows, int cols)
{
	if (i < 0 || i >= rows || j < 0 || j >= cols)
		return 0;
	return 1;
}
void CreateAnImage(unsigned char** obj, bool** arrflag, int i, int j,int r,int c,string label)
{
	stack<indices> st;
	st.push(indices(i, j));
	unsigned char** out = new unsigned char* [r];
	for (int i = 0; i < r; i++)
		out[i] = new unsigned char[c] {};
	while (!st.isempty())
	{
		indices temp = st.Peek();
		st.pop();
		out[temp.row][temp.col] = 255;

		if (validCheck(temp.row + 1, temp.col + 1, r, c) && obj[temp.row + 1][temp.col + 1] != 0 && arrflag[temp.row + 1][temp.col + 1] == false)
		{
			arrflag[temp.row + 1][temp.col + 1] = true;
			st.push(indices(temp.row + 1, temp.col + 1));
		}
		if (validCheck(temp.row + 1, temp.col , r, c) && obj[temp.row + 1][temp.col] != 0 && arrflag[temp.row + 1][temp.col] == false)
		{
			arrflag[temp.row + 1][temp.col] = true;

			st.push(indices(temp.row + 1, temp.col));
		}
		if (validCheck(temp.row + 1, temp.col - 1, r, c) && obj[temp.row + 1][temp.col - 1] != 0 && arrflag[temp.row + 1][temp.col - 1] == false)
		{
			arrflag[temp.row + 1][temp.col - 1] = true;
			st.push(indices(temp.row + 1, temp.col - 1));
		}
		if (validCheck(temp.row, temp.col + 1, r, c) && obj[temp.row][temp.col + 1] != 0 && arrflag[temp.row][temp.col + 1] == false)
		{
			arrflag[temp.row][temp.col + 1] = true;
			st.push(indices(temp.row, temp.col + 1));
		}
		if (validCheck(temp.row, temp.col  - 1, r, c) && obj[temp.row][temp.col  - 1] != 0 && arrflag[temp.row][temp.col  - 1] == false)
		{
			arrflag[temp.row][temp.col - 1] = true;
			st.push(indices(temp.row, temp.col  - 1));
		}
		if (validCheck(temp.row - 1, temp.col + 1, r, c) && obj[temp.row - 1][temp.col + 1] != 0 && arrflag[temp.row - 1][temp.col + 1] == false)
		{
			arrflag[temp.row - 1][temp.col + 1] = true;
			st.push(indices(temp.row - 1, temp.col + 1));
		}
		if (validCheck(temp.row - 1, temp.col , r, c) && obj[temp.row - 1][temp.col ] != 0 && arrflag[temp.row - 1][temp.col ] == false)
		{
			arrflag[temp.row - 1][temp.col ] = true;
			st.push(indices(temp.row - 1, temp.col ));
		}
		if (validCheck(temp.row - 1, temp.col- 1, r, c) && obj[temp.row - 1][temp.col- 1] != 0 && arrflag[temp.row - 1][temp.col- 1] == false)
		{
			arrflag[temp.row - 1][temp.col - 1] = true;
			st.push(indices(temp.row - 1, temp.col- 1));
		}
	}


	Mat outmat = cv::Mat(r, c, CV_8UC1);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			outmat.data[outmat.step[0] * i + outmat.step[1] * j + 0] = out[i][j];
	cv::imwrite("Output_files\\" + label + ".png", outmat);
}
int CountObject(string filename,string names="img")
{
	if (filename[0] == '\\')
		filename.erase(0, 1);
	if (filename.find("png") == string::npos)
		filename += ".png";
	int rows = 0, cols = 0;
	unsigned char** obj = imageread(filename, rows, cols);
	bool** Arr = new bool*[rows];
	for (int i = 0; i < rows; i++)
		Arr[i] = new bool[cols] {};
	int objCount = 0;
	int label = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (obj[i][j] == 0 || Arr[i][j]== true)
				continue;
			objCount++;
			CreateAnImage(obj, Arr, i, j, rows, cols,names + to_string(objCount));
		}
	}
	return objCount;
}
