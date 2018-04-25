/*
 * Implementation of CDK Matrix
 *
 * File:   cdk.cc
 * Author: David Lanius
 * Email:  djl150230@utdallas.edu
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include "cdk.h"
#include <stdint.h>
#include <sstream>
#include <string>
#include <cstring>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader
{
public:
  uint32_t magicNumber; /*0xFEEDFACE*/
  uint32_t versionNumber;
  uint64_t numRecords;
};

/*
 * Records in the file have a fixed length buffer
 * that will hold a C-Style string. This is the
 * size of the fixed length buffer.
 */
const int maxRecordStringLength = 25;
class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main()
{
  stringstream ss;
  BinaryFileHeader *header = new BinaryFileHeader();
  ifstream binInFile ("cs3377.bin", ios::in | ios::binary);
  
  /*BinaryFileRecord *myRecord = new BinaryFileRecord();

  ifstream binInfile ("binaryfile.bin", ios::in | ios::binary);

  binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));
  cout << "Value was: " << setprecision(10) << myRecord->myVal << endl;
  binInfile.close();
  */

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"0", "a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  binInFile.read((char*) header, sizeof(BinaryFileHeader));
  ss << hex << uppercase << header->magicNumber;
  string magNum(ss.str());
  setCDKMatrixCell(myMatrix, 1, 1, ("Magic: 0x" + magNum).c_str());
  drawCDKMatrix(myMatrix, true);
  ss.str("");
  ss << header->versionNumber;
  string verNum(ss.str());
  setCDKMatrixCell(myMatrix, 1, 2, ("Version: " + verNum).c_str());
  drawCDKMatrix(myMatrix, true);
  ss.str("");
  ss << header->numRecords;
  string numRec(ss.str());
  setCDKMatrixCell(myMatrix, 1, 3, ("NumRecords: " + numRec).c_str());
  drawCDKMatrix(myMatrix, true);
  ss.str("");
      /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
