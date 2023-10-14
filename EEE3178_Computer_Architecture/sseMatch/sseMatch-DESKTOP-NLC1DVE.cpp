#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Timer.h"
#include <emmintrin.h>
#include <iostream>
#include <immintrin.h>

void match(int* inputPtr, int* patchPtr, int* errPtr, int xSIze, int ySize, int pxSize, int pySize);
void matchSIMD(int* inputPtr, int* patchPtr, int* errPtr, int xSIze, int ySize, int pxSize, int pySize);
int verify(int* COutput, int* SIMDOutput, int exSize, int eySize);



void CacheFlush(__m128i* src, int countVect) {
	int j;
	for (j = 0; j < countVect; j++) {
		_mm_clflush(src + j);
	}
}

int main()
{
	FILE* input_fp, * patch_fp, * output_fp, * outputSIMD_fp;
	int* inputPtr, * patchPtr, * errPtr, * outSIMDPtr;
	short* input16Ptr;

	int xSize, ySize;
	int pxSize, pySize;
	int exSize, eySize;
	int err = 0;

	int buffer_size;
	int pbuffer_size;
	int ebuffer_size;

	float dCpuTime;
	int loopCount;
	char temp3;

	CPerfCounter counter;


	xSize = 512;
	ySize = 512;
	pxSize = 15;
	pySize = 15;
	exSize = xSize - pxSize + 1;
	eySize = ySize - pySize + 1;

	buffer_size = xSize * ySize;
	pbuffer_size = pxSize * pySize;
	ebuffer_size = exSize * eySize;

	printf("buffer_size : %d \n", buffer_size);
	printf("patch size : %d \n", pbuffer_size);

	input16Ptr = new  short[buffer_size];

	inputPtr = new int[buffer_size];
	patchPtr = new int[pbuffer_size];
	errPtr = new int[ebuffer_size];
	outSIMDPtr = new int[ebuffer_size];

	/*************************************************************************************
	* Read the input image
	*************************************************************************************/
	if (fopen_s(&input_fp, "usc32.raw", "rb") != 0) {
		printf("Error: Input file can not be opened\n");
		exit(-1);
	}
	if (fread(inputPtr, xSize * 4, ySize, input_fp) == 0) {
		printf("Error: Input file can not be read\n");
		exit(-1);
	}
	fclose(input_fp);


	/*************************************************************************************
	* Read the patch
	*************************************************************************************/
	if (fopen_s(&patch_fp, "patch.raw", "rb") != 0) {
		printf("Error: Patch file can not be opened\n");
		exit(-1);
	}
	if (fread(patchPtr, pxSize * 4, pySize, patch_fp) == 0) {
		printf("Error: Patch file can not be read\n");
		exit(-1);
	}
	fclose(patch_fp);

	for (int i = 0; i < ebuffer_size; outSIMDPtr[i++] = 0);
	for (int i = 0; i < ebuffer_size; errPtr[i++] = 0);

	/*****************************************************
	* Call generic C ssd
	*****************************************************/

	dCpuTime = 0.0f;
	for (loopCount = 0; loopCount < 10; loopCount++) {
		CacheFlush((__m128i*)inputPtr, buffer_size / 16);
		CacheFlush((__m128i*)errPtr, ebuffer_size / 16);
		counter.Reset();
		counter.Start();

		match(inputPtr, patchPtr, errPtr, xSize, ySize, pxSize, pySize);

		counter.Stop();
		dCpuTime += counter.GetElapsedTime();
	}
	printf("C Performance (ms) = %f \n", dCpuTime / (double)loopCount * 1000.0);



	/*****************************************************
	* Call sse C ssd
	*****************************************************/

	dCpuTime = 0.0f;
	for (loopCount = 0; loopCount < 10; loopCount++) {
		CacheFlush((__m128i*)inputPtr, buffer_size / 16);
		CacheFlush((__m128i*)outSIMDPtr, ebuffer_size / 16);
		counter.Reset();
		counter.Start();

		matchSIMD(inputPtr, patchPtr, outSIMDPtr, xSize, ySize, pxSize, pySize);

		counter.Stop();
		dCpuTime += counter.GetElapsedTime();
	}

	printf("SIMD Performance (ms) = %f \n", dCpuTime / (double)loopCount * 1000.0);



	/*********************************************************
	* Write the outfile_SIMD.raw
	*********************************************************/

	if (fopen_s(&outputSIMD_fp, "outfile_SIMD.raw", "wb") != 0) {
		printf("Error: Output file can not be opened\n");
		exit(-1);
	}
	if (fwrite(outSIMDPtr, exSize * 4, eySize, outputSIMD_fp) == 0)
	{
		printf("file write error: outfile_SIMD.raw\n");
		exit(-1);
	}/* fi */
	fclose(outputSIMD_fp);

	/*********************************************************
	* Write the outfile_C.raw
	*********************************************************/

	if (fopen_s(&output_fp, "outfile_C.raw", "wb") != 0) {
		printf("Error: Output file can not be opened\n");
		exit(-1);
	}
	if (fwrite(errPtr, exSize * 4, eySize, output_fp) == 0)
	{
		printf("file write error: outfile_C.raw\n");
		exit(-1);
	}/* fi */
	fclose(output_fp);


	int error = verify(errPtr, outSIMDPtr, exSize, eySize);

	if (error != 0)
		printf("Verify Failed \n");
	else
		printf("Verify Successful \n");


	/* free the allocated memories */
	free(inputPtr);
	free(patchPtr);
	free(errPtr);
	free(outSIMDPtr);

	return 0;

}

int verify(int* COutput, int* SIMDOutput, int exSize, int eySize) {
	for (int i = 0; i < exSize * eySize; i++) {
		if (COutput[i] != SIMDOutput[i]) {
			printf("COutput[%d] = %d SIMDOutput[%d]=%d \n", i, COutput[i], i, SIMDOutput[i]);
			return(1);
		}
	}
	return(0);
}


/*********************************************************
* Optimize matchSIMD operation using Intel MMX/SSE/SSE2/AVX/?
*********************************************************/

void matchSIMD(int* inputPtr, int* patchPtr, int* errPtr, int xSize, int ySize, int pxSize, int pySize)
{
	/*********************************************************
	* Write your code here
	*********************************************************/

	//inputPtr : 512*512 int 배열
	//patchPtr : 15*15 int 배열
	//errPtr : 498*498 int 배열
	//xSize : 512
	//ySize : 512
	//pxSize : 15
	//pySize : 15

	int exSize, eySize = 0;
	int buffer_size = xSize * ySize; //512*512
	exSize = xSize - pxSize + 1; //498
	eySize = ySize - pySize + 1; //498
	int x, y = 0;
	int temp;

	/*
	for (x = 0; x < exSize; x++) {
		for (y = 0; y < eySize; y++) {
			for (int dx = 0; dx < pxSize; dx++) {
				for (int dy = 0; dy < pySize; dy++) {
					errPtr[eySize * x + y] += (inputPtr[(x + dx) * ySize + y + dy] - patchPtr[dy + pySize * dx]) * (inputPtr[(x + dx) * ySize + y + dy] - patchPtr[dy + pySize * dx]);
				}
			}
		}
	}
	*/

	for (x = 0; x < exSize; x++) {
		for (y = 0; y < eySize; y++) {
			for (int dx = 0; dx < pxSize; dx++) {
				for (int dy = 0; dy < pySize; dy++) {
					temp = inputPtr[(x + dx) * ySize + y + dy] - patchPtr[dy + pySize * dx];
					errPtr[eySize * x + y] += temp * temp;
				}
			}
		}
	}
}

void match(int* inputPtr, int* patchPtr, int* errPtr, int xSIze, int ySize, int pxSize, int pySize)
{
	int exSize, eySize = 0;
	int buffer_size = xSIze * ySize;
	exSize = xSIze - pxSize + 1;
	eySize = ySize - pySize + 1;
	int x, y = 0;
	

	for (x = 0; x < exSize; x++) {
		for (y = 0; y < eySize; y++) {
			for (int dx = 0; dx < pxSize; dx++) {
				for (int dy = 0; dy < pySize; dy++) {
					errPtr[eySize * (x)+y] = errPtr[eySize * x + y] + \
						abs(inputPtr[(x + dx) * ySize + y + dy] - patchPtr[dy + pySize * dx]) * abs(inputPtr[(x + dx) * ySize + y + dy] - patchPtr[dy + pySize * dx]);
				}
			}
		}
	}

}